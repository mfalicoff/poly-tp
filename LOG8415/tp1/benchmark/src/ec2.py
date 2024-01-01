from dataclasses import dataclass
from typing import List

import boto3
from mypy_boto3_ec2 import EC2Client
from mypy_boto3_ec2.type_defs import InstanceTypeDef


@dataclass
class Ec2Instances:
    t2_large: List[InstanceTypeDef]
    m4_large: List[InstanceTypeDef]


def get_ec2_instances() -> Ec2Instances:
    client: EC2Client = boto3.client("ec2")
    instances = Ec2Instances(t2_large=[], m4_large=[])
    for reservation in client.describe_instances(
        Filters=[{"Name": "instance.group-name", "Values": ["flask-ec2"]}]
    )["Reservations"]:
        for instance in reservation["Instances"]:
            if instance["InstanceType"] == "t2.large":
                instances.t2_large.append(instance)
            elif instance["InstanceType"] == "m4.large":
                instances.m4_large.append(instance)
    return instances
