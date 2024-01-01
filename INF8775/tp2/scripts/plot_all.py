import os
import sys
import csv
import matplotlib.pyplot as plt

from algo.greedy import greedy
from main import main

def run_samples():
    sample_sizes = [250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000]

    avg_times_proba = []
    avg_times_greedy = []
    avg_times_progdyn = []

    avg_heights_proba = []
    avg_heights_greedy = []
    avg_heights_progdyn = []

    for sample_size in sample_sizes:
        total_time_proba = 0
        total_time_greedy = 0
        total_time_progdyn = 0

        total_height_proba = 0
        total_height_greedy = 0
        total_height_progdyn = 0

        for i in range(1, 11):
            file_name = f"/Users/mazilious/git/INF8775/tp2/samples/sample_{sample_size}_{i}.txt"
            file_path = os.path.join("sample", file_name)
            sys.argv = ['main.py', '-a', 'proba', '-e', file_path, '-p', '-t', '-z']
            height, execution_time = main()
            total_height_proba += height
            total_time_proba += execution_time

            sys.argv = ['main.py', '-a', 'glouton', '-e', file_path, '-p', '-t', '-z']
            height1, execution_time1 = main()
            total_height_greedy += height1
            total_time_greedy += execution_time1

            sys.argv = ['main.py', '-a', 'progdyn', '-e', file_path, '-p', '-t', '-z']
            height2, execution_time2 = main()
            total_height_progdyn += height2
            total_time_progdyn += execution_time2

        avg_time_greedy = total_time_greedy / 10
        avg_time_proba = total_time_proba / 10
        avg_time_progdyn = total_time_progdyn / 10

        avg_height_greedy = total_height_greedy / 10
        avg_height_proba = total_height_proba / 10
        avg_height_progdyn = total_height_progdyn / 10

        avg_times_proba.append(avg_time_proba)
        avg_times_greedy.append(avg_time_greedy)
        avg_times_progdyn.append(avg_time_progdyn)

        avg_heights_proba.append(avg_height_proba)
        avg_heights_greedy.append(avg_height_greedy)
        avg_heights_progdyn.append(avg_height_progdyn)

    # Save the data to a CSV file
    with open('algorithm_data.csv', 'w', newline='') as csvfile:
        fieldnames = ['Sample Size', 'Avg Time Proba', 'Avg Height Proba', 'Avg Time Greedy', 'Avg Height Greedy', 'Avg Time Progdyn', 'Avg Height Progdyn']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        for sample_size, avg_time_proba, avg_height_proba, avg_time_greedy, avg_height_greedy, avg_time_progdyn, avg_height_progdyn in zip(
                sample_sizes, avg_times_proba, avg_heights_proba, avg_times_greedy, avg_heights_greedy, avg_times_progdyn, avg_heights_progdyn):
            writer.writerow({
                'Sample Size': sample_size,
                'Avg Time Proba': avg_time_proba,
                'Avg Height Proba': avg_height_proba,
                'Avg Time Greedy': avg_time_greedy,
                'Avg Height Greedy': avg_height_greedy,
                'Avg Time Progdyn': avg_time_progdyn,
                'Avg Height Progdyn': avg_height_progdyn
            })

    # Plot all sets of data in a single plot
    plt.plot(sample_sizes, avg_times_proba, label='Proba')
    plt.plot(sample_sizes, avg_times_greedy, label='Greedy')
    plt.plot(sample_sizes, avg_times_progdyn, label='Porgrammation Dynamique')
    plt.xlabel('Sample Size')
    plt.ylabel('Average')
    plt.title('Comparison of Proba, Greedy, and Progdyn')
    plt.legend()
    plt.show()

    # plt.plot(sample_sizes, avg_times_proba, label='Proba')
    # plt.plot(sample_sizes, avg_times_greedy, label='Greedy')
    # # plt.plot(sample_sizes, avg_times_progdyn, label='Porgrammation Dynamique')
    # plt.xlabel('Sample Size')
    # plt.ylabel('Average')
    # plt.title('Comparison of Proba, Greedy')
    # plt.legend()
    # plt.show()

if __name__ == "__main__":
    run_samples()
