import os
import sys
import matplotlib.pyplot as plt
from main import main


def run_samples():
    sample_sizes = [250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000]
    avg_times = []
    avg_heights = []

    for sample_size in sample_sizes:
        total_time = 0
        total_height = 0
        for i in range(1, 11):
            file_name = f"/Users/mazilious/git/INF8775/tp2/samples/sample_{sample_size}_{i}.txt"
            file_path = os.path.join("sample", file_name)
            sys.argv = ['main.py', '-a', 'glouton', '-e', file_path, '-p', '-t']
            height, execution_time = main()
            total_time += execution_time
            total_height += height
        avg_time = total_time / 10
        avg_height = total_height / 10
        avg_heights.append(avg_height)
        avg_times.append(avg_time)

    # Save the data to a text file
    with open('glouton_plot_data.txt', 'w') as f:
        f.write("Sample Size Average Execution Time Average Height\n")
        for sample_size, avg_time, avg_height in zip(sample_sizes, avg_times, avg_heights):
            f.write(f"{sample_size} {avg_time} {avg_height}\n")

    plt.plot(sample_sizes, avg_times)
    plt.xlabel('Sample Size')
    plt.ylabel('Average Execution Time (s)')
    plt.title('Greedy: Average Execution Time by Sample Size')
    plt.show()


if __name__ == "__main__":
    run_samples()
