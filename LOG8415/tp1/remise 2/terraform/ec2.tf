locals {
  configurations = {
    heavy = {
      count         = 5
      instance_type = "m4.large"
      endpoint      = "/cluster1"
    },
    light = {
      count         = 4
      instance_type = "t2.large"
      endpoint      = "/cluster2"
    }
  }
}

# Fetch the latest Ubuntu 22.04 AMI from AWS
data "aws_ami" "ubuntu" {
  most_recent = true

  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-jammy-22.04-amd64-server-*"]
  }

  owners = ["099720109477"] # Canonical
}

# Configures the instances that will be launched by the auto scaling group 
resource "aws_launch_template" "flask" {
  for_each = local.configurations

  name_prefix            = "flask-${each.key}-"
  image_id               = data.aws_ami.ubuntu.id
  instance_type          = each.value.instance_type
  user_data              = filebase64("user_data.sh")
  vpc_security_group_ids = [aws_security_group.ec2.id]

  # enable detailed monitoring for all instances
  monitoring {
    enabled = true
  }

  tag_specifications {
    resource_type = "instance"

    tags = {
      Name = each.key
    }
  }
}

data "aws_availability_zones" "available" {
  state = "available"
}

# Create one autoscaling group per configuration
resource "aws_autoscaling_group" "flask" {
  for_each = local.configurations

  name               = "flask-${each.key}"
  availability_zones = data.aws_availability_zones.available.names
  desired_capacity   = each.value.count
  max_size           = each.value.count
  min_size           = each.value.count

  # will register the spawned instances to the appropriate target group
  target_group_arns = [aws_lb_target_group.flask[each.key].arn]

  launch_template {
    id      = aws_launch_template.flask[each.key].id
    version = aws_launch_template.flask[each.key].latest_version
  }
}
