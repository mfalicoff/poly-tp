import json
import os
from pathlib import Path
from typing import List, Tuple

import boto3
from mypy_boto3_cloudwatch import CloudWatchClient

from ec2 import get_ec2_instances
from elb import get_elb
from widgets import (
    MetricWidget,
    cluster_cpu_utilization_widget,
    TimeRange,
    cluster_network_out_widget,
    elb_request_count_widget,
)

OUT_DIR = Path("out")
if not OUT_DIR.exists():
    os.makedirs(OUT_DIR, exist_ok=True)


def _output_widget_images(widgets: List[Tuple[MetricWidget, str]]) -> None:
    cloudwatch: CloudWatchClient = boto3.client("cloudwatch")
    for metric_widget, tag in widgets:
        img_bytes = cloudwatch.get_metric_widget_image(
            MetricWidget=json.dumps(metric_widget)
        )["MetricWidgetImage"]
        img_path = OUT_DIR / f"{tag}.png"
        print(f"Writing to {img_path.resolve().as_posix()}")
        img_path.write_bytes(img_bytes)


def get_results(time_range: TimeRange):
    ec2_instances = get_ec2_instances()
    lb = get_elb()
    widgets: List[Tuple[MetricWidget, str]] = []
    for cluster, cluster_name in (
        (ec2_instances.t2_large, "t2_large"),
        (ec2_instances.m4_large, "m4_large"),
    ):
        # CPU utilization per cluster
        metric_widget = cluster_cpu_utilization_widget(
            title=f"CPU utilization from {len(cluster)} {cluster_name} instances",
            instances=cluster,
            time_range=time_range,
        )
        tag = f"ec2-cluster-{cluster_name}-cpu_utilization"
        widgets.append((metric_widget, tag))

        # Network out per cluster
        metric_widget = cluster_network_out_widget(
            title=f"Network bytes out for cluster of {len(cluster)} {cluster_name} instances",
            instances=cluster,
            time_range=time_range,
        )
        tag = f"ec2-cluster-{cluster_name}-network_out"
        widgets.append((metric_widget, tag))

    all_instances = ec2_instances.t2_large + ec2_instances.m4_large
    # CPU utilization all instances
    metric_widget = cluster_cpu_utilization_widget(
        title="CPU utilization from all instances",
        instances=all_instances,
        time_range=time_range,
    )
    tag = "ec2-all-instances-cpu_utilization"
    widgets.append((metric_widget, tag))

    # Network out all instances
    metric_widget = cluster_network_out_widget(
        title=f"Network bytes out for all instances",
        instances=all_instances,
        time_range=time_range,
    )
    tag = "ec2-all-instances-network_out"
    widgets.append((metric_widget, tag))

    # ELB request count
    metric_widget = elb_request_count_widget(lb=lb, time_range=time_range)
    tag = "elb-request-count"
    widgets.append((metric_widget, tag))

    # Output to images
    _output_widget_images(widgets=widgets)
