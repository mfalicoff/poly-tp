import os
import numpy as np
import pandas as pd
import scipy.stats as stats


def parse_data_from_file(file_path):
    with open(file_path, 'r') as file:
        data = file.read()

    runs = data.split("##################################################################################")
    runs = [run.strip() for run in runs if run.strip() != ""]

    parsed_runs = []

    for run in runs:
        run_data = {}
        lines = run.split("\n")
        for line in lines:
            if line.startswith("[") and "], " in line:
                key, value = line.split("], ", 1)
                key = key.strip("[]")
                value = value.split(", ")
                if len(value) == 1:
                    run_data[key] = float(value[0])
                else:
                    run_data[f"{key}_{value[0]}"] = float(value[1])
        parsed_runs.append(run_data)

    return parsed_runs


def calculate_mean_and_confidence_interval(data):
    mean = np.mean(data)
    confidence_interval = stats.t.interval(0.95, len(data) - 1, loc=mean, scale=stats.sem(data))
    return mean, confidence_interval


def create_summary_file_transposed(parsed_runs, summary_file_path):
    metrics = {}
    for run in parsed_runs:
        for key, value in run.items():
            if key not in metrics:
                metrics[key] = []
            metrics[key].append(value)

    data = {
        'Metric': [],
        'Mean': [],
        'Confidence Interval Low': [],
        'Confidence Interval High': []
    }
    for metric, values in metrics.items():
        mean, (ci_low, ci_high) = calculate_mean_and_confidence_interval(values)
        data['Metric'].append(metric)
        data['Mean'].append(mean)
        data['Confidence Interval Low'].append(ci_low)
        data['Confidence Interval High'].append(ci_high)

    df = pd.DataFrame(data)
    df_transposed = df.set_index('Metric').transpose()
    df_transposed.to_csv(summary_file_path)


def process_all_files(raw_folder, sanitized_folder):
    if not os.path.exists(sanitized_folder):
        os.makedirs(sanitized_folder)

    for filename in os.listdir(raw_folder):
        file_path = os.path.join(raw_folder, filename)
        summary_file_path = os.path.join(sanitized_folder, filename)

        if os.path.isfile(file_path):
            parsed_runs = parse_data_from_file(file_path)
            create_summary_file_transposed(parsed_runs, summary_file_path)  # Updated function call
            print(f"Processed {filename} and saved results to {sanitized_folder}")


raw_folder = 'raw'
sanitized_folder = 'sanitized'

process_all_files(raw_folder, sanitized_folder)
