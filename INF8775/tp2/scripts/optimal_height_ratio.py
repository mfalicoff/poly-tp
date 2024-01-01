import os
import sys
import csv
import matplotlib.pyplot as plt

from algo.greedy import greedy
from main import main

def run_samples():
    sample_size = 7500
    num_trials = 50  # Number of trials to collect data
    num_runs = 100

    optimal_height = None
    average_runs_needed = 0

    # Calculate the optimal height using dynamic programming (assuming it's the same for all runs)
    file_path = f"/Users/mazilious/git/INF8775/tp2/samples/sample_{sample_size}_1.txt"
    sys.argv = ['main.py', '-a', 'progdyn', '-e', file_path, '-p', '-t']
    optimal_height, _ = main()

    for trial in range(1, num_trials + 1):
        runs_needed = 0

        for i in range(1, num_runs + 1):
            file_name = f"/Users/mazilious/git/INF8775/tp2/samples/sample_{sample_size}_1.txt"
            file_path = os.path.join("sample", file_name)

            sys.argv = ['main.py', '-a', 'proba', '-e', file_path, '-p', '-t']
            height, execution_time = main()

            ratio = height / optimal_height
            if ratio >= 0.99:
                runs_needed = i
                break

        average_runs_needed += runs_needed
        print(f"Trial {trial} - Runs needed: {runs_needed}")

    average_runs_needed /= num_trials

    print(f"Average number of runs needed to achieve 99% of optimal height: {average_runs_needed}")

if __name__ == "__main__":
    run_samples()
