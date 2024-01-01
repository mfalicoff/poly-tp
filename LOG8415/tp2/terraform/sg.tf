resource "aws_security_group" "orchestrator" {
  name        = "flask-orchestrator"
  description = "Allow inbound HTTP traffic from the broad internet"
  vpc_id      = data.aws_vpc.default.id
}

# Allow HTTP traffic from the broad internet to reach the ALB
resource "aws_security_group_rule" "orchestrator_ingress" {
  type              = "ingress"
  from_port         = 80
  to_port           = 80
  protocol          = "tcp"
  cidr_blocks       = ["0.0.0.0/0"]
  ipv6_cidr_blocks  = ["::/0"]
  security_group_id = aws_security_group.orchestrator.id
}

# Allow all egress traffic
resource "aws_security_group_rule" "orchestrator_egress" {
  type              = "egress"
  from_port         = 0
  to_port           = 0
  protocol          = "-1"
  cidr_blocks       = ["0.0.0.0/0"]
  ipv6_cidr_blocks  = ["::/0"]
  security_group_id = aws_security_group.orchestrator.id
}

# Uncomment to allow SSH traffic to the orchestrator instance
 resource "aws_security_group_rule" "orchestrator_ssh" {
   type              = "ingress"
   from_port         = 22
   to_port           = 22
   protocol          = "tcp"
   cidr_blocks       = ["0.0.0.0/0"]
   security_group_id = aws_security_group.orchestrator.id
 }

resource "aws_security_group" "worker" {
  name        = "flask-worker"
  description = "Allow inbound HTTP traffic from the orchestrator and egress"
  vpc_id      = data.aws_vpc.default.id
}

variable "ingress_rules" {
  description = "A list of ingress rules"
  type = list(object({
    from_port = number
    to_port   = number
  }))
  default = [
    {
        from_port = 80
        to_port   = 80
    },
    {
      from_port = 80
      to_port   = 5000
    },
    {
      from_port = 80
      to_port   = 5001
    }
  ]
}

# Only allow HTTP traffic from the orchestrator
resource "aws_security_group_rule" "worker_ingress" {
  for_each = { for index, rule in var.ingress_rules : index => rule }

  type                     = "ingress"
  from_port                = each.value.from_port
  to_port                  = each.value.to_port
  protocol                 = "tcp"
  source_security_group_id = aws_security_group.orchestrator.id
  security_group_id        = aws_security_group.worker.id
}

# Allow all egress traffic to the broad internet
resource "aws_security_group_rule" "worker_egress" {
  type              = "egress"
  from_port         = 0
  to_port           = 0
  protocol          = "-1"
  cidr_blocks       = ["0.0.0.0/0"]
  ipv6_cidr_blocks  = ["::/0"]
  security_group_id = aws_security_group.worker.id
}

# Uncomment to allow SSH traffic to the worker instances
 resource "aws_security_group_rule" "worker_ssh" {
   type              = "ingress"
   from_port         = 22
   to_port           = 22
   protocol          = "tcp"
   cidr_blocks       = ["0.0.0.0/0"]
   security_group_id = aws_security_group.worker.id
 }
