#!/bin/bash

# Update the package list and install dependencies
sudo apt-get update -y
sudo apt-get install -y \
    apt-transport-https \
    ca-certificates \
    curl \
    software-properties-common \
    python3 \
    python3-pip \
    python3-venv

# Add Docker's official GPG key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

# Add the Docker repository
sudo add-apt-repository -y "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

# Update the package list again
sudo apt-get update -y

# Install Docker
sudo apt-get install -y \
    docker-ce \
    docker-compose

# Start and enable Docker
sudo systemctl start docker
sudo systemctl enable docker

mkdir -p /app
echo "import random
import string
import torch

from transformers import DistilBertTokenizer, DistilBertForSequenceClassification

from flask import Flask, jsonify

app = Flask(__name__)

# Load the pre-trained model and tokenizer
tokenizer = DistilBertTokenizer.from_pretrained('distilbert-base-uncased')
model = DistilBertForSequenceClassification.from_pretrained('distilbert-base-uncased', num_labels=2)


def generate_random_text(length=50):
    letters = string.ascii_lowercase + ' '
    return ''.join(random.choice(letters) for i in range(length))


@app.route('/run_model', methods=['POST'])
def run_model():
    # Generate random input text
    print('Generating random input text...')
    input_text = generate_random_text()

    # Tokenize the input text and run it through the model
    inputs = tokenizer(input_text, return_tensors='pt', padding=True, truncation=True)
    outputs = model(**inputs)

    # Turn logits into probabilities
    probabilities = torch.softmax(outputs.logits, dim=-1)

    # Convert the tensor to a list and return
    probabilities_list = probabilities.tolist()[0]

    return jsonify({'input_text': input_text, 'probabilities': probabilities_list})


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000) # Port for the setup
" > /app/app.py

echo "transformers==4.35.0
torch==2.1.0
flask==3.0.0" > /app/requirements.txt

echo "services:
  ml_app_1:
    build: .
    restart: unless-stopped
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
    ports:
      - 5000:5000
  ml_app_2:
    build: .
    restart: unless-stopped
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
    ports:
      - 5001:5000
      " > /app/docker-compose.yml

echo "FROM python:3.11-slim

ENV FLASK_APP=app.py
ENV FLASK_RUN_HOST=0.0.0.0

WORKDIR /code

COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt

EXPOSE 5000
COPY . .

CMD [\"flask\", \"run\"]" > /app/Dockerfile

echo "[Unit]
Requires=docker.service
After=docker.service

[Service]
Type=simple
ExecStart=/usr/bin/docker-compose -f /app/docker-compose.yml up
ExecStop=/usr/bin/docker-compose -f /app/docker-compose.yml down
Restart=always

[Install]
WantedBy=multi-user.target" > /usr/lib/systemd/system/flask.service

systemctl enable flask.service
systemctl start flask.service