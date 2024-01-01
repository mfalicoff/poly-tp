#!/bin/bash

# Install dependencies
apt-get update && apt-get install -y python3 python3-pip python3-venv

# Copy and configure the required files
mkdir -p /app
echo "import os
from flask import Flask

app = Flask(__name__)

@app.route('/')
def base_route():
    return '<h1>Instance number {} is responding now!</h1>'.format(os.environ['INSTANCE_ID'])

@app.route('/cluster1')
@app.route('/cluster2')
def cluster_route():
    return '<h1>Instance number {} is responding now!</h1>'.format(os.environ['INSTANCE_ID'])

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)" > /app/app.py

echo "blinker==1.6.2
click==8.1.7
Flask==2.3.3
gunicorn==21.2.0
importlib-metadata==6.8.0
itsdangerous==2.1.2
Jinja2==3.1.2
MarkupSafe==2.1.3
Werkzeug==2.3.7
zipp==3.17.0" > /app/requirements.txt

echo "#!/bin/bash
# Retrieve the instance id from the meta-data service
TOKEN=\$(curl -X PUT \"http://169.254.169.254/latest/api/token\" -H \"X-aws-ec2-metadata-token-ttl-seconds: 21600\")
export INSTANCE_ID=\$(curl -H \"X-aws-ec2-metadata-token: \$TOKEN\" http://169.254.169.254/latest/meta-data/instance-id)

cd /app
source .venv/bin/activate
gunicorn -b 0.0.0.0:80 -w $(($(nproc) * 2)) app:app" > /app/run.sh
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
