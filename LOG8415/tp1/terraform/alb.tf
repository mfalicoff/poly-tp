data "aws_subnets" "subnets" {
  filter {
    name   = "vpc-id"
    values = [data.aws_vpc.default.id]
  }
}

# Create the Application Load Balancer
resource "aws_lb" "flask" {
  name               = "flask-alb"
  internal           = false
  load_balancer_type = "application"
  security_groups    = [aws_security_group.alb.id]
  subnets            = data.aws_subnets.subnets.ids # register the ALB in all the AZs
}

output "alb_public_endpoint" {
  value = "http://${aws_lb.flask.dns_name}"
}

# Create one listener that will be shared with the two /cluster1 and /cluster2
resource "aws_lb_listener" "flask" {
  load_balancer_arn = aws_lb.flask.arn
  port              = "80"
  protocol          = "HTTP"

  default_action {
    type = "fixed-response"

    fixed_response {
      content_type = "text/plain"
      status_code  = "404"
    }
  }
}

# Register each target group within the shared listener
resource "aws_lb_listener_rule" "flask" {
  for_each = local.configurations

  listener_arn = aws_lb_listener.flask.arn

  # Each rule has a priority number (from 1 to something large). This will assign
  # a deterministic integer id for each keys of the configurations map.
  priority = index(sort(keys(local.configurations)), each.key) + 1

  action {
    type             = "forward"
    target_group_arn = aws_lb_target_group.flask[each.key].arn
  }

  condition {
    path_pattern {
      values = [each.value.endpoint]
    }
  }
}

# Create on target group per configuration (light and heavy)
resource "aws_lb_target_group" "flask" {
  for_each = local.configurations

  name     = "flask-${each.key}"
  port     = 80
  protocol = "HTTP"
  vpc_id   = data.aws_vpc.default.id
}
