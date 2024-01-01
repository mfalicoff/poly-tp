from mypy_boto3_ec2.type_defs import InstanceTypeDef

from ec2 import get_ec2_instances
from elb import get_elb


def _describe_ec2(instance: InstanceTypeDef) -> str:
    return f"\tInstanceId={instance['InstanceId']}, InstanceType={instance['InstanceType']}"


def describe_resources():
    ec2_instances = get_ec2_instances()
    m4_summary = "\n".join(map(_describe_ec2, ec2_instances.m4_large))
    t2_summary = "\n".join(map(_describe_ec2, ec2_instances.t2_large))
    print(f"EC2 cluster1 instances:\n{m4_summary}\n")
    print(f"EC2 cluster2 instances:\n{t2_summary}\n")

    lb = get_elb()
    print(f'ELB: LoadBalancerName={lb["LoadBalancerArn"]}\n')
