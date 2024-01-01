# TP1

## 1. Configure AWS Credentials

1. Click `Lancer l'atelier pour étudiants de l'AWS Academy` [here](https://awsacademy.instructure.com/courses/54504/modules)
2. Click `Ouvrir Lancer l'atelier pour étudiants de l'AWS Academy dans une nouvelle fenêtre`
3. Click `Start Lab`
4. Click `AWS Details`
5. Click the `Show` button right of `AWS CLI`
5. Copy the snippet to `~/.aws/credentials`

```bash
# Ensure that your AWS Credentials are correctly configured. You can validate that everything
# is working by running the `aws sts get-caller-identity`. You should get the following output:
# {
#      "UserId": "AROAT6ZOYZXMN37BFVCSL:user1234=john.doe@polymtl.ca",
#      "Account": "272291646936",
#      "Arn": "arn:aws:sts::272291646936:assumed-role/voclabs/user1234=john.doe@polymtl.ca"
# }
aws sts get-caller-identity
```

## 2. Provision the cloud infrastructure

```bash
# The current working directory needs to be teraform
cd terraform

# Will download the required AWS provider and initialize the local state. It needs
# to be done once before running any plan/apply/destroy command
terraform init

# Will plan the required infrastructure changes to reach the defined state
terraform plan

# Will actually create the required cloud ressources
terraform apply

# Will cleanup all the deployed resources
terraform destroy
```
