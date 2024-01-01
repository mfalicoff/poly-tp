import datetime
import json
import threading
import time
from pathlib import Path

import requests
from tqdm import tqdm, trange

import describe_resources
import results
from widgets import TimeRange


def request_without_sleep(url: str):
    t = threading.current_thread().name
    for _ in trange(1000, desc=f"{t} Sequential 1000 GET {url}"):
        requests.get(url=url)


def requests_with_sleep(url: str):
    t = threading.current_thread().name
    for _ in trange(500, desc=f"{t} Sequential 500 before sleep 1min GET {url}"):
        requests.get(url=url)
    tqdm.write(f'{t} Sleeping 1min...')
    time.sleep(60)
    for _ in trange(1000, desc=f"{t} Sequential 1000 after sleep 1min GET {url}"):
        requests.get(url=url)


def main():
    describe_resources.describe_resources()
    output_file = Path("output.json")
    if not output_file.is_file():
        raise ValueError(
            "Missing output.json. Run `terraform output --json > ../benchmark/output.json`"
        )
    endpoint = json.loads(output_file.read_text())["alb_public_endpoint"]["value"]
    threads = []
    for cluster in ["/cluster1", "/cluster2"]:
        threads.append(
            threading.Thread(
                target=request_without_sleep, args=(endpoint + cluster,), daemon=True
            )
        )
        threads.append(
            threading.Thread(
                target=requests_with_sleep, args=(endpoint + cluster,), daemon=True
            )
        )
    start_time = datetime.datetime.utcnow()
    for t in threads:
        t.start()
    for t in threads:
        t.join()
    end_time = datetime.datetime.utcnow()
    for _ in trange(1200, desc="Waiting for CloudWatch metrics to be available..."):
        time.sleep(1)
    print(f'Benchmark ran from {start_time.isoformat()} to {end_time.isoformat()}')

    # add metrics before and after to see metric baseline
    start = start_time - datetime.timedelta(minutes=5)
    end = end_time + datetime.timedelta(minutes=5)
    time_range = TimeRange(start=start, end=end)

    results.get_results(time_range = time_range)


if __name__ == "__main__":
    main()
