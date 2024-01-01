# Fetch the latest Ubuntu 22.04 AMI from AWS
data "aws_ami" "ubuntu" {
  most_recent = true

  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-jammy-22.04-amd64-server-*"]
  }

  owners = ["099720109477"] # Canonical
}

# Uncomment to enable SSH access
 resource "aws_key_pair" "ssh" {
   key_name   = "ssh"
   public_key = "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAINjfhhwOtjpDypULkd6G5NXLl/Cy4Ex2W0inppwZo/uv"
 }

resource "aws_instance" "orchestrator" {
  ami                    = data.aws_ami.ubuntu.id
  instance_type          = "m4.large"
  user_data              = file("orchestrator.sh")
  vpc_security_group_ids = [aws_security_group.orchestrator.id]
  
   key_name = aws_key_pair.ssh.id

  tags = {
    is_orchestrator = "true"
    Name            = "Orchestrator"
  }
}

output "orchestrator_public_dns" {
  description = "The public DNS of the Orchestrator instance"
  value       = aws_instance.orchestrator.public_dns
}

resource "aws_instance" "worker" {
  count = 4

  ami                    = data.aws_ami.ubuntu.id
  instance_type          = "m4.large"
  user_data              = file("worker.sh")
  vpc_security_group_ids = [aws_security_group.worker.id]

   key_name = aws_key_pair.ssh.id

  root_block_device {
    volume_size = 15
  }

  tags = {
    is_worker = "true"
    Name      = "Worker ${count.index}"
  }
}
