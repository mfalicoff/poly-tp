import sys
import time
import traceback
import argparse

from denombrement import denombrement
from quicksort import quicksort, quicksort_threshold, quicksort_random


def main():
    sys.setrecursionlimit(1000000)

    args = extract_args()

    algorithm = args.algorithm
    file_path = args.file
    flag_p = args.flag_p
    flag_t = args.flag_t

    print("Selected algorithm:", algorithm)
    print("File path:", file_path)
    print("Flag -p:", flag_p)
    print("Flag -t:", flag_t)

    try:
        with open(file_path, 'r') as file:
            data = file.read().split()
            data_array = [int(value) for value in data]

        try:

            if algorithm == "counting":
                start = time.time()
                denombrement(data_array)  # Use random pivot
                end = time.time()
            elif algorithm == "quick":
                start = time.time()
                quicksort(data_array, 0, len(data_array) - 1, random_pivot=False)  # Use random pivot
                end = time.time()
            elif algorithm == "quickSeuil":
                start = time.time()
                quicksort_threshold(data_array, 0, len(data_array) - 1, random_pivot=False)  # Use random pivot
                end = time.time()
            elif algorithm == "quickRandomSeuil":
                start = time.time()
                quicksort_random(data_array, 0, len(data_array) - 1, random_pivot=True)  # Use random pivot
                end = time.time()

            if flag_p:
                print("Sorted numbers: ", data_array)
            if flag_t:
                print("Execution time: ", end - start, " ms")

        except Exception:
            print(traceback.format_exc())
            # or
            print(sys.exc_info()[2])

    except FileNotFoundError:
        print(f"The file '{file_path}' was not found.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")


def extract_args():
    parser = argparse.ArgumentParser(description="tp1")
    parser.add_argument('-a', '--algorithm', choices=['counting', 'quick', 'quickSeuil', 'quickRandomSeuil'],
                        required=True, help="Select an algorithm")
    parser.add_argument('-e', '--file', required=True, help="Path to the file")
    parser.add_argument('-p', '--flag_p', action='store_true', help="Include this flag if needed")
    parser.add_argument('-t', '--flag_t', action='store_true', help="Include this flag if needed")
    return parser.parse_args()


if __name__ == "__main__":
    main()
