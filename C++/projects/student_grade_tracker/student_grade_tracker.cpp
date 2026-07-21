#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>

class Student
{
private:
    std::string name;
    int grades[5] = {0};
    int grade_count = 0;

public:
    Student() : name("") {}
    Student(std::string student_name) : name(student_name) {}
    const std::string &getName() const
    {
        return name;
    }
    int *getGrade()
    {
        return grades;
    }
    int getGradeCount()
    {
        return grade_count;
    }
    void incrementGradeCount()
    {
        grade_count++;
    }
    double getAverage() const
    {
        int total = 0;

        if (grade_count == 0)
            return 0.0;
        for (int i = 0; i < grade_count; i++)
        {
            total += grades[i];
        }
        return (double)total / grade_count;
    }
};

std::vector<Student> students;
int student_count = students.size();

std::string toLowercase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return string;
}

void add_student();
void student_list();
void add_grade();
void get_average();
void display_student();
void top_student();

int main()
{
    int running = 1;
    char choice;

    std::cout << "************************************\n";
    std::cout << "Welcome to the student grade library\n";
    std::cout << "************************************\n";

    while (running)
    {
        std::cout << "Choose what to do:\n1.Add new student\n2.View student list\n3.Add grade\n4.Get average grade\n5.Display student\n6.Display top student\nPress q to quit\n";
        std::cin >> choice;
        std::cin.ignore();
        std::cout << '\n';

        switch (choice)
        {
        case '1':
            add_student();
            break;

        case '2':
            student_list();
            break;

        case '3':
            add_grade();
            break;
        case '4':
            get_average();
            break;
        case '5':
            display_student();
            break;
        case '6':
            top_student();
            break;
        default:
            if (choice == 'q' || choice == 'Q')
            {
                running = 0;
            }
            else
            {
                std::cout << "Enter the right choice\n";
            }
            break;
        }
    }

    return 0;
}

void add_student()
{
    bool dupl;
    std::string check;
    std::string student_name;
    std::cout << "\nEnter the student name: ";
    std::getline(std::cin, student_name);
    check = toLowercase(student_name);

    dupl = std::any_of(students.begin(), students.end(), [&check](const Student &student)
                       {std::string name;
                        name = student.getName();
                        name = toLowercase(name);
                        return name == check; });

    if (dupl)
    {
        std::cout << "The student name already exist.\n";
    }
    else
    {
        students.push_back(student_name);
        std::cout << student_name << " has been added\n\n";
        student_count = students.size();
    }
}
void student_list()
{
    if (student_count == 0)
    {
        std::cout << "No student in database\n";
        return;
    }
    for (int i = 0; i < student_count; i++)
    {
        std::cout << i + 1 << ". " << students[i].getName() << "\n";
        if (i == (student_count - 1))
        {
            std::cout << '\n';
        }
    }
}
void add_grade()
{
    int grade = {0};
    std::string student_name;
    std::string lower_name;
    std::string temp_name;
    std::vector<int> found_student;
    int number_grade;
    int entered_grade;
    std::cout << "Enter student name: ";
    std::getline(std::cin, student_name);

    lower_name = toLowercase(student_name);
    // std::cout << lower_name << "test\n";
    if (student_count == 0)
    {
        std::cout << "The list is empty\n";
    }
    else
    {
        for (int i = 0; i < student_count; i++)
        {
            temp_name = students[i].getName();
            temp_name = toLowercase(temp_name);
            // std::cout << temp_name << "test\n";

            if (temp_name.find(lower_name) != std::string::npos)
            {
                // std::cout << "student found";
                found_student.emplace_back(i);
            }
            // std::cout << found_student.size();
        }

        if (found_student.size() > 1)
        {
            for (int j = 0; j < found_student.size(); j++)
            {
                std::cout << j + 1 << ". " << students[found_student[j]].getName() << "\n";
                std::cout << "   Grade: " << students[found_student[j]].getGradeCount() << "\n";
            }
            int choice;
            std::cout << "Choose the student: ";
            std::cin >> choice;

            if (choice <= 0 || choice > found_student.size() + 1)
            {
                std::cout << "Not a valid choice\n";
            }
            else
            {
                Student &found_person = students[found_student[choice - 1]];
                std::cout << "How much grade to enter: ";
                std::cin >> number_grade;

                if (number_grade + found_person.getGradeCount() > 5)
                {
                    std::cout << "The grade count is more than 5\n";
                }
                else if (number_grade > 0 && number_grade + found_person.getGradeCount() <= 5)
                {
                    for (int l = 0; l < number_grade; l++)
                    {
                        std::cout << "Enter grade " << l + 1 << ": ";
                        std::cin >> entered_grade;
                        while (entered_grade < 0 || entered_grade > 100)
                        {
                            std::cout << "Entered grade is not valid\n";
                            std::cout << "Enter grade " << l + 1 << ": ";
                            std::cin >> entered_grade;
                        }
                        found_person.getGrade()[found_person.getGradeCount()] = entered_grade;
                        found_person.incrementGradeCount();
                        std::cout << "Grade " << entered_grade << "has been added\n\n";
                    }
                }
            }
        }
        else if (found_student.size() == 1)
        {
            int choice;
            std::cout << "Name: " << students[found_student[0]].getName() << "\n";
            std::cout << "Grade: " << students[found_student[0]].getGradeCount() << "\n";
            std::cout << "How much grade to enter: ";
            std::cin >> choice;

            if (choice + students[found_student[0]].getGradeCount() > 5)
            {
                std::cout << "The grade count is more than 5\n";
            }
            else if (choice > 0 && choice + students[found_student[0]].getGradeCount() <= 5)
            {

                for (int r = 0; r < choice; r++)
                {
                    std::cout << "Enter grade " << r + 1 << " : ";
                    std::cin >> entered_grade;
                    while (entered_grade < 0 || entered_grade > 100)
                    {
                        std::cout << "Entered grade is not valid\n";
                        std::cout << "Enter grade " << r + 1 << " : ";
                        std::cin >> entered_grade;
                    }
                    students[found_student[0]].getGrade()[students[found_student[0]].getGradeCount()] = entered_grade;
                    students[found_student[0]].incrementGradeCount();
                    std::cout << "Grade " << entered_grade << " has been added\n\n";
                }
            }
        }
        else if (found_student.size() == 0)
        {
            std::cout << "No student was found\n\n";
        }
    }
}
void get_average()
{
    std::string student_name;
    std::string lower_name;
    std::string temp_name;
    std::vector<int> found_student;
    std::cout << "Enter student name: ";
    std::getline(std::cin, student_name);

    lower_name = toLowercase(student_name);
    // std::cout << lower_name << "test\n";
    if (student_count == 0)
    {
        std::cout << "The list is empty\n";
    }
    else
    {
        for (int i = 0; i < student_count; i++)
        {
            temp_name = students[i].getName();
            temp_name = toLowercase(temp_name);

            if (temp_name.find(lower_name) != std::string::npos)
            {
                found_student.emplace_back(i);
            }
        }
        if (found_student.size() > 1)
        {
            for (int j = 0; j < found_student.size(); j++)
            {
                std::cout << j + 1 << ". " << students[found_student[j]].getName() << "\n";
                std::cout << "   Grade: " << students[found_student[j]].getGradeCount() << "\n";
            }
            int choice;
            std::cout << "Choose the student: ";
            std::cin >> choice;

            if (choice <= 0 || choice > found_student.size() + 1)
            {
                std::cout << "Not a valid choice\n\n";
            }
            else
            {
                Student &found_person = students[found_student[choice - 1]];
                std::cout << "Average: " << found_person.getAverage() << "\n\n";
            }
        }
        else if (found_student.size() == 1)
        {
            Student &found_person = students[found_student[0]];
            std::cout << "Average: " << found_person.getAverage() << "\n\n";
        }
        else if (found_student.size() == 0)
        {
            std::cout << "No student was found\n\n";
        }
    }
}
void display_student()
{
    std::string student_name;
    std::string lower_name;
    std::string temp_name;
    std::vector<int> found_student;
    std::cout << "Enter student name: ";
    std::getline(std::cin, student_name);

    lower_name = toLowercase(student_name);
    // std::cout << lower_name << "test\n";
    if (student_count == 0)
    {
        std::cout << "The list is empty\n";
    }
    else
    {
        for (int i = 0; i < student_count; i++)
        {
            temp_name = students[i].getName();
            temp_name = toLowercase(temp_name);

            if (temp_name.find(lower_name) != std::string::npos)
            {
                found_student.emplace_back(i);
            }
        }

        if (found_student.size() > 1)
        {
            for (int j = 0; j < found_student.size(); j++)
            {
                std::cout << j + 1 << ". " << students[found_student[j]].getName() << "\n";
            }
            int choice;
            std::cout << "Choose the student: ";
            std::cin >> choice;

            if (choice <= 0 || choice > found_student.size() + 1)
            {
                std::cout << "Not a valid choice\n\n";
            }
            else
            {
                Student found_person = students[found_student[choice - 1]];
                const int *found_person_grade = students[found_student[choice - 1]].getGrade();

                std::cout << "    " << found_person.getName() << "\n";
                for (int b = 0; b < found_person.getGradeCount(); b++)
                {
                    std::cout << "Grade " << b + 1 << ": " << found_person.getGrade()[b] << "\n";
                }
                std::cout << "Average: " << found_person.getAverage() << "\n\n";
            }
        }
        else if (found_student.size() == 1)
        {
            Student &found_person = students[found_student[0]];
            std::cout << "    " << found_person.getName() << "\n";
            for (int b = 0; b < found_person.getGradeCount(); b++)
            {
                std::cout << "Grade " << b + 1 << ": " << found_person.getGrade()[b] << "\n";
            }
            std::cout << "Average: " << found_person.getAverage() << "\n\n";
        }
        else if (found_student.size() == 0)
        {
            std::cout << "No student was found\n\n";
        }
    }
}
void top_student()
{
    std::vector<std::pair<std::string, double>> name_grade;
    for (const auto &student : students)
    {
        name_grade.emplace_back(student.getName(), student.getAverage());
    }
    size_t top_count = std::min(size_t(5), name_grade.size());

    std::partial_sort(name_grade.begin(), name_grade.begin() + top_count, name_grade.end(), [](const auto &a, const auto &b)
                      { return a.second > b.second; });

    size_t count = 1;
    for (const auto &member : name_grade)
    {
        std::cout << count << ". " << member.first << "\n";
        std::cout << "Grade average: " << member.second << "\n";
        count++;
    }
    std::cout << "\n";
}