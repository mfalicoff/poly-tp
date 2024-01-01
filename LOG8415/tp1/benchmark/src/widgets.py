import datetime
import enum
from dataclasses import dataclass
from typing import TypedDict, List, Any, Dict, Tuple, Union, Optional

from mypy_boto3_ec2.type_defs import InstanceTypeDef
from mypy_boto3_elbv2.type_defs import LoadBalancerTypeDef

IMAGE_SCALING_FACTOR = 1.5


class Namespaces(enum.StrEnum):
    EC2_NAMESPACE = "AWS/EC2"
    ELB_NAMESPACE = "AWS/ApplicationELB"
    AUTO_SCALING_NAMESPACE = "AWS/AutoScaling"


class ElbMetricNames(enum.StrEnum):
    ActiveConnectionCount = "ActiveConnectionCount"
    IPv6RequestCount = "IPv6RequestCount"
    NewConnectionCount = "NewConnectionCount"
    ProcessedBytes = "ProcessedBytes"
    RequestCount = "RequestCount"
    RuleEvaluations = "RuleEvaluations"
    HealthyHostCount = "HealthyHostCount"
    HTTPCode_Target_2XX_Count = "HTTPCode_Target_2XX_Count"
    RequestCountPerTarget = "RequestCountPerTarget"
    TargetResponseTime = "TargetResponseTime"
    HealthyStateDNS = "HealthyStateDNS"
    HealthyStateRouting = "HealthyStateRouting"


class Ec2MetricNames(enum.StrEnum):
    CPUUtilization = "CPUUtilization"
    NetworkIn = "NetworkIn"
    NetworkOut = "NetworkOut"
    NetworkPacketsIn = "NetworkPacketsIn"
    NetworkPacketsOut = "NetworkPacketsOut"
    CPUCreditUsage = "CPUCreditUsage"
    CPUCreditBalance = "CPUCreditBalance"
    CPUSurplusCreditBalance = "CPUSurplusCreditBalance"
    CPUSurplusCreditsCharged = "CPUSurplusCreditsCharged"


class StatType(enum.StrEnum):
    SampleCount = "SampleCount"
    Average = "Average"
    Sum = "Sum"
    Minimum = "Minimum"
    Maximum = "Maximum"


@dataclass
class Metric:
    namespace: Namespaces
    metric_name: Union[Ec2MetricNames, ElbMetricNames]
    dimensions: Optional[List[Tuple[str, str]]] = None
    options: Optional[Dict[str, Any]] = None

    def to_array(self) -> List[Any]:
        arr = [self.namespace, self.metric_name]
        if self.dimensions:
            for k, v in self.dimensions:
                arr.extend([k, v])
        if self.options:
            arr.append(self.options)
        return arr


class Annotations(TypedDict):
    horizontal: Union[Dict, List[Dict]]
    vertical: Union[Dict, List[Dict]]


class MetricWidget(TypedDict, total=False):
    metrics: List[List[Any]]
    annotations: Annotations
    start: str
    end: str
    timezone: str
    height: int
    width: int
    title: str
    stat: StatType
    period: int


@dataclass
class TimeRange:
    start: datetime.datetime
    end: datetime.datetime


def _to_metric_widget(
    metrics: List[Metric],
    time_range: TimeRange,
    title: str,
    period: Optional[int] = None,
    stat: StatType = StatType.Average,
    annotations: Optional[Annotations] = None,
) -> MetricWidget:
    metric_widget: MetricWidget = {
        "metrics": [m.to_array() for m in metrics],
        "timezone": "-0400",
        "height": int(400 * IMAGE_SCALING_FACTOR),
        "width": int(600 * IMAGE_SCALING_FACTOR),
        "title": title,
        "stat": stat,
    }
    if annotations:
        metric_widget["annotations"] = annotations
    if period:
        metric_widget["period"] = period
    metric_widget["start"] = time_range.start.isoformat()
    metric_widget["end"] = time_range.end.isoformat()
    return metric_widget


def cluster_cpu_utilization_widget(
    title: str, instances: List[InstanceTypeDef], time_range: TimeRange
) -> MetricWidget:
    return _to_metric_widget(
        metrics=[
            Metric(
                namespace=Namespaces.EC2_NAMESPACE,
                metric_name=Ec2MetricNames.CPUUtilization,
                dimensions=[("InstanceId", instance["InstanceId"])],
            )
            for instance in instances
        ],
        time_range=time_range,
        title=title,
        period=60,
    )


def cluster_network_out_widget(
    title: str, instances: List[InstanceTypeDef], time_range: TimeRange
) -> MetricWidget:
    return _to_metric_widget(
        metrics=[
            Metric(
                namespace=Namespaces.EC2_NAMESPACE,
                metric_name=Ec2MetricNames.NetworkOut,
                dimensions=[("InstanceId", instance["InstanceId"])],
            )
            for instance in instances
        ],
        time_range=time_range,
        title=title,
        period=60,
    )


def elb_request_count_widget(
    lb: LoadBalancerTypeDef, time_range: TimeRange
) -> MetricWidget:
    lb_dimension_value = lb["LoadBalancerArn"].split(":loadbalancer/")[1]
    return _to_metric_widget(
        metrics=[
            Metric(
                namespace=Namespaces.ELB_NAMESPACE,
                metric_name=ElbMetricNames.RequestCount,
                dimensions=[("LoadBalancer", lb_dimension_value)],
            ),
        ],
        time_range=time_range,
        title="Load balancer request count",
        stat=StatType.Average,
        period=60,
    )
