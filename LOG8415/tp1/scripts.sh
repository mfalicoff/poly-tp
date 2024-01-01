#!/usr/bin/env bash 

# Setup benchmark credentials
AWS_CREDENTIALS_FILE="$HOME/.aws/credentials"

if [ -f "$AWS_CREDENTIALS_FILE" ]; then

    AWS_DEFAULT_REGION=us-east-1
    AWS_ACCESS_KEY_ID=$(grep -i 'aws_access_key_id' "$AWS_CREDENTIALS_FILE" | awk -F '=' '{print $2}' | tr -d '[:space:]')
    AWS_SECRET_ACCESS_KEY=$(grep -i 'aws_secret_access_key' "$AWS_CREDENTIALS_FILE" | awk -F '=' '{print $2}' | tr -d '[:space:]')
    AWS_SESSION_TOKEN=$(grep -i 'aws_session_token' "$AWS_CREDENTIALS_FILE" | awk -F '=' '{print $2}' | tr -d '[:space:]')

    echo "AWS_DEFAULT_REGION=$AWS_DEFAULT_REGION" > benchmark/aws.env
    echo "AWS_ACCESS_KEY_ID=$AWS_ACCESS_KEY_ID" >> benchmark/aws.env
    echo "AWS_SECRET_ACCESS_KEY=$AWS_SECRET_ACCESS_KEY" >> benchmark/aws.env
    echo "AWS_SESSION_TOKEN=$AWS_SESSION_TOKEN" >> benchmark/aws.env

    echo "aws.env file has been created with AWS credentials."
else
    echo "AWS credentials file ($AWS_CREDENTIALS_FILE) not found."
    exit 1
fi

# setup terraform
cd terraform
terraform init
terraform plan

# deploy terraform
terraform apply -auto-approve
# we can use terraform output to get the url to pass as a env to the docker image
terraform output --json > ../benchmark/output.json

# Waiting for the load balancer to initialize (noticed some errors if not present)
echo "Sleeping 2 minutes, waiting for load balancer"
sleep 120 | pv -t

# build docker image
cd ../benchmark
docker build . -t benchmark

# run python script
docker run -it --rm --env-file aws.env -v .:/usr/src/app benchmark python src/main.py

# destroy infra
cd ../terraform
terraform destroy -auto-approve
