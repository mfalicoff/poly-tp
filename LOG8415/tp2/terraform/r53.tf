locals {
    domain_name = "log8415.info"
}

resource "aws_route53_zone" "dns" {
  name = local.domain_name

  vpc {
    vpc_id = data.aws_vpc.default.id
  }
}

# Create a predictible DNS entry for each worker (like worker0.log8415.info)
resource "aws_route53_record" "worker" {
  count = 4

  zone_id = aws_route53_zone.dns.zone_id
  name    = "worker${count.index}.${local.domain_name}"
  type    = "CNAME"
  ttl     = 5
  records = [aws_instance.worker[count.index].private_dns]
}
