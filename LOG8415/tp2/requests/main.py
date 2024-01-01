import datetime
import json
import threading
import time
from pathlib import Path
import argparse
import requests


def send_requests(url: str):
    # Each thread sends 10 requests
    for _ in range(10):
        print("Sending request, url: ", url)
        payload = json.dumps({})
        headers = {
            'Content-Type': 'application/json'
        }
        response = requests.request("POST", url, headers=headers, data=payload)
        print(response.text)


def main(arguments):
    print(arguments)
    endpoint = arguments.url + "/new_request"
    threads = []

    # Sending 5 requests simultaneously
    for _ in range(5):
        thread = threading.Thread(target=send_requests, args=(endpoint,), daemon=False)
        threads.append(thread)
        thread.start()


    for thread in threads:
        thread.join()


if __name__ == "__main__":
    # Initialize parser
    parser = argparse.ArgumentParser()
    parser.add_argument("-u", "--url", help="Url of the endpoint")
    args = parser.parse_args()
    print(args)
    main(args)
