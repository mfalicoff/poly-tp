#!/bin/bash

# Install dependencies
apt-get update && apt-get install -y python3 python3-pip python3-venv

# Copy and configure the required files
mkdir -p /app
echo "import queue
from threading import Lock, BoundedSemaphore, Thread
import logging
from typing import Dict

import requests
from flask import Flask, request, jsonify

URL_FORMAT = 'http://worker{0}.log8415.info:{1}/run_model'
NUM_WORKER_INSTANCES = 4
NUM_CONTAINERS_PER_WORKER = 2
num_containers = NUM_WORKER_INSTANCES * NUM_CONTAINERS_PER_WORKER
num_free_containers = BoundedSemaphore(
    value=num_containers
)  # atomic counter for the number of free containers

container_ids = list(range(num_containers))
container_locks: Dict[int, Lock] = {}  # maps each container_id to a lock. Locked means busy
for id_ in container_ids:
    container_locks[id_] = Lock()

app = Flask(__name__)
request_queue = queue.SimpleQueue()
print_lock = Lock()

# Configure logging
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

@app.route('/new_request', methods=['POST'])
def new_request():
    # First step. Enqueue request
    incoming_request_data = request.json
    request_queue.put_nowait(incoming_request_data)
    logger.debug(f'Enqueued request: {incoming_request_data}')
    return jsonify({'message': 'Request received and processing started.'})


def consume_queue():
    '''Running thread started in __main__ consumes from the request queue'''
    logger.debug('Starting queue consuming thread...')
    while True:
        # Second step. Wait for a request from the queue
        logger.debug('Waiting for a request from the queue...')
        incoming_request_data = request_queue.get(block=True)

        # Third step. Acquire/reserve (blocking) a free container (container_id unspecified)
        num_free_containers.acquire()

        # Fourth step. Acquire/lock a free container (container_id specified)
        # Guaranteed to find a free container because of third step
        for container_id, lock in container_locks.items():
            logger.debug('testing container_id: %s', container_id)
            if lock.acquire(blocking=False):
                # Fifth step. Start the request thread
                Thread(
                    target=send_request_to_container,
                    args=(container_id, incoming_request_data),
                ).start()
                break
            else:
                logger.debug('container_id %s is busy', container_id)
                pass  # Container is already in use


def send_request_to_container(container_id: int, incoming_request_data):
    # Sixth step. Send the request to the container
    with print_lock:
        print(
            f'Sending request to container{container_id} with data: {incoming_request_data}...'
        )
    worker = container_id // NUM_CONTAINERS_PER_WORKER
    port = 5000 + (container_id % NUM_CONTAINERS_PER_WORKER)
    res = requests.post(url=URL_FORMAT.format(worker, port))
    logger.debug(f'Received response from container{container_id}: {res.json()}')
    with print_lock:
        print(f'Received response from container{container_id}: {res.json()}')

    # Seventh step. Free the container
    container_locks[container_id].release()
    num_free_containers.release()


if __name__ == '__main__':
    Thread(target=consume_queue).start()  # queue consuming thread
    app.run(host='0.0.0.0', port=80)
" > /app/app.py

echo "blinker==1.7.0
gunicorn==21.2.0
certifi==2023.7.22
charset-normalizer==3.3.2
click==8.1.7
Flask==3.0.0
idna==3.4
importlib-metadata==6.8.0
itsdangerous==2.1.2
Jinja2==3.1.2
MarkupSafe==2.1.3
requests==2.31.0
urllib3==1.26.15
Werkzeug==3.0.1
zipp==3.17.0" > /app/requirements.txt

echo "#!/bin/bash

cd /app
source .venv/bin/activate
python app.py" > /app/run.sh
chmod +x /app/run.sh

# systemd
echo "[Unit]
After=network.target

[Service]
Type=simple
Restart=always
ExecStart=/app/run.sh

[Install]
WantedBy=multi-user.target" > /usr/lib/systemd/system/flask.service

# Install the python requirements
pushd /app
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
deactivate
popd

# Enable and start the flask service
systemctl enable flask.service
systemctl start flask.service
