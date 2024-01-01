import sys
import time
import traceback
import argparse

from algo.dyn import dyn
from algo.prob import probability
from algo.greedy import greedy
from block import Block


def main():

    args = extract_args()

    algorithm = args.algorithm
    file_path = args.file
    flag_p = args.flag_p
    flag_t = args.flag_t
    flag_z = args.flag_z

    print("Selected algorithm:", algorithm)
    print("File path:", file_path)
    print("Flag -p:", flag_p)
    print("Flag -t:", flag_t)
    print("Flag -z:", flag_z)

    max_height = 0
    max_width = 0
    max_depth = 0

    blocks = set()

    height = 0

    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            for line in lines:
                data = line.split()
                new_block = Block(float(data[0]), float(data[1]), float(data[2]))
                if new_block not in blocks:
                    blocks.add(new_block)
                    max_height += new_block.height
                    max_depth += new_block.depth
                    max_width += new_block.width

        try:
            if algorithm == "glouton":
                start = time.time()
                ret = greedy(blocks, max_height, max_depth, max_width)
                end = time.time()
                height = ret[1]
                print("Height: ", ret[1])

            if algorithm == "proba":
                start = time.time()
                ret = probability(blocks)
                end = time.time()
                height = ret[1]

            if algorithm == "progdyn":
                start = time.time()
                ret = dyn(blocks)
                end = time.time()
                height = ret[1]

            if flag_p:
                print("Used boxes: ")
                for box in ret[0]:
                    print(box)
            if flag_t:
                print("Execution time: ", end - start, " ms")
            if flag_z:
                print("Height: ", height)

            return height, end - start

        except Exception:
            print(traceback.format_exc())
            # or
            print(sys.exc_info()[2])

    except FileNotFoundError:
        print(f"The file '{file_path}' was not found.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")


def extract_args():
    parser = argparse.ArgumentParser(description="tp2")
    parser.add_argument('-a', '--algorithm', choices=['glouton', 'progdyn', 'proba'],
                        required=True, help="Select an algorithm")
    parser.add_argument('-e', '--file', required=True, help="Path to the file")
    parser.add_argument('-p', '--flag_p', action='store_true', help="Include this flag if needed")
    parser.add_argument('-t', '--flag_t', action='store_true', help="Include this flag if needed")
    parser.add_argument('-z', '--flag_z', action='store_true', help="Include this flag if needed")
    return parser.parse_args()


if __name__ == "__main__":
    main()
