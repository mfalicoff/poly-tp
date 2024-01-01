import boto3
from mypy_boto3_elbv2 import ElasticLoadBalancingv2Client
from mypy_boto3_elbv2.type_defs import LoadBalancerTypeDef


def get_elb() -> LoadBalancerTypeDef:
    client: ElasticLoadBalancingv2Client = boto3.client("elbv2")
    return client.describe_load_balancers(Names=["flask-alb"])["LoadBalancers"][0]
