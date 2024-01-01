def place_student_height(student, student_line):
    for i in range(len(student_line)):
        if student_line[i].height < student.height:
            return student_line[:i] + [student] + student_line[i:]

    return student_line + [student]


def place_students_optimized(students):
    students_sorted_by_height = sorted(students, key=lambda x: -x.height)

    student_line = []

    for student in students_sorted_by_height:
        placed = False

        for i in range(len(student_line) + 1):
            if i == len(student_line) or student not in student_line[i].conflicts:
                if i == 0 or student_line[i - 1] not in student.conflicts:
                    student_line.insert(i, student)
                    placed = True
                    break

        if not placed:
            student_line = place_student_height(student, student_line)

    res = ""
    for student in student_line:
        res += f"{student.id} "

    return res
