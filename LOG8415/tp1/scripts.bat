cd terraform
terraform init
terraform plan
terraform apply -auto-approve
terraform output --json > ../benchmark/output.json
timeout /t 120
cd ../benchmark
docker build . -t benchmark
docker run -it --rm --env-file aws.env -v .:/usr/src/app benchmark python src/main.py
