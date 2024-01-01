class Student:
    def __init__(self, id, height):
        self.id = id
        self.height = height
        self.conflicts = set()

    def __str__(self):
        return f"Student(ID: {self.id}, Height: {self.height}, Conflicts: {[student.id for student in self.conflicts]})"

    def add_conflict(self, other_student):
        self.conflicts.add(other_student)

    def remove_conflict(self, other_student):
        if other_student in self.conflicts:
            self.conflicts.remove(other_student)

    def __repr__(self):
        return f"Student(ID: {self.id}, Height: {self.height}, Conflicts: {[student.id for student in self.conflicts]})"

