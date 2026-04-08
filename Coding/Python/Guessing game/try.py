class Student:
    count = 0
    total_gpa = 0
    def __init__(self, name, gpa):
        self.name = name
        self.gpa = gpa
        Student.count += 1

    def get_info(self):
        print(f'{self.name} = {self.gpa}')

    @classmethod
    def get_count(cls):
        print(f'Total number of students is {cls.count}')

student1 = Student('Spongebob', 4.0)
student2 = Student('Patrick', 2.0)
student3 = Student('Squidward', 4.5)
student4 = Student('Akmal', 4.0)
student5 = Student('Muhammad Bappe', 0.1)



Student.get_count()
print(student1.name + student2.name)
