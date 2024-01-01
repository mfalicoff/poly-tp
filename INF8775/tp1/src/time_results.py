import os
import glob
import time

from denombrement import denombrement
from quicksort import quicksort, quicksort_threshold, quicksort_random

# assign directory
directory = 'samples/'

patterns = [1000,50000,100000,500000,1000000]
# Define your glob pattern inside the loop

for it in patterns:
    pattern = "sample_" + str(it)+ "_*_*"
    # pattern = "sample_" + str(it)+ "_" + str(it) + "_*"
    # pattern = "sample_10000_" + str(it)+ "_*"

    # Use glob.glob to find files that match the pattern
    matching_files = glob.glob(os.path.join(directory, pattern))

    sum = 0

    if matching_files:
        for file_path in matching_files:
            # print(file_path)
            with open(file_path, 'r') as file:
                data = file.read().split()
                data_array = [int(value) for value in data]
            start = time.time()
            # denombrement(data_array)  # Use random pivot
            # quicksort(data_array, 0, len(data_array) - 1, random_pivot=False)  # Use random pivot
            # quicksort_threshold(data_array, 0, len(data_array) - 1, random_pivot=False)  # Use random pivot
            quicksort_random(data_array, 0, len(data_array) - 1, random_pivot=True)  # Use random pivot
            end = time.time()
            # print("Execution time: ", end - start, " ms")
            sum += end-start
        print("Execution time average: ", it, sum/10, " ms")


