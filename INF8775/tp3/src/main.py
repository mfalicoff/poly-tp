import sys
import traceback
import argparse

from algo.greedy import place_students_optimized
from check_sol import score
from student import Student


def main():
    args = extract_args()

    file_path = args.file
    flag_p = args.flag_p

    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

        num_students = int(lines[0])

        heights = list(map(int, lines[2:num_students + 2]))
        students = [Student(i, height) for i, height in enumerate(heights)]
        conflict_lines = lines[num_students + 2:]
        for line in conflict_lines:
            a, b = map(int, line.split())
            students[a].add_conflict(students[b])
            students[b].add_conflict(students[a])

        try:
            result = place_students_optimized(students)

            if flag_p:
                print(result)
            else:
                con = []
                for line in conflict_lines:
                    a, b = map(int, line.split())
                    con.append([a, b])
                result = [int(i) for i in result.split()]
                print(score(result, heights, con))

            return result

        except Exception:
            print(traceback.format_exc())
            # or
            print(sys.exc_info()[2])

    except FileNotFoundError:
        print(f"The file '{file_path}' was not found.")

    except Exception as e:
        print(traceback.format_exc())
        print(sys.exc_info()[2])


def get_score(res, heights, conflict_lines):
    x = [int(i) for i in res.split()]
    con = []
    for line in conflict_lines:
        a, b = map(int, line.split())
        con.append([a, b])
    return score(x, heights, con)


def extract_args():
    parser = argparse.ArgumentParser(description="tp3")
    parser.add_argument('-e', '--file', required=True, help="Path to the file")
    parser.add_argument('-p', '--flag_p', action='store_true', help="Include this flag if needed")
    return parser.parse_args()


def save_solution_to_file(solution, file_path):
    with open(file_path, 'w') as file:
        for student in solution:
            file.write(str(student.id) + " ")


if __name__ == "__main__":
    main()
