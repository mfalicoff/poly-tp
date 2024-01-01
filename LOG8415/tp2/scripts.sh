# setup terraform
cd terraform
terraform init
terraform plan

# deploy terraform
terraform apply -auto-approve
orchestrator_public_dns=$(terraform output -raw orchestrator_public_dns | tr -d '"')
orchestrator_url="http://$orchestrator_public_dns"

 Waiting for the workers to initialize (buidl image)
echo "Sleeping 10 minutes, waiting for workers to initialize"
sleep 600 | pv -t

cd ../requests
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python3 main.py -u $orchestrator_url

echo "Sleeping 1 minute, waiting for workers to finish"
sleep 60 | pv -t

# destroy infra
cd ../terraform
terraform destroy -auto-approve