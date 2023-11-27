#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

// ������ ��������������
enum Specialization {
    COMPUTER_SCIENCE,
    COMPUTER_ENGINEERING,
    INFORMATION_SYSTEMS_AND_TECHNOLOGIES,
    CIVIL_ENGINEERING
};

// ��������� ��� ��������� ���������� ��� ��������
struct Student {
    string surname;
    int course;
    Specialization specialization;
    double physicsGrade;
    double mathGrade;
    double computerScienceGrade;
};

// ������� ��� �������� ���������� ��� ������ ��������
void inputStudentData(Student& student) {
    cout << "�������: ";
    cin >> student.surname;

    cout << "����: ";
    cin >> student.course;

    cout << "������������ (0 - ����'����� �����, 1 - �����'����� ��������, 2 - ����������� ������� �� �������㳿): ";
    int specializationInput;
    cin >> specializationInput;

    if (specializationInput >= 0 && specializationInput <= 2) {
        student.specialization = static_cast<Specialization>(specializationInput);
    }
    else {
        cout << "����������� ��� ��� ������������. ��������������� �������� �� ������������� (����'����� �����).\n";
        student.specialization = COMPUTER_SCIENCE;
    }

    cout << "������ � ������: ";
    cin >> student.physicsGrade;

    cout << "������ � ����������: ";
    cin >> student.mathGrade;

    cout << "������ � �����������: ";
    cin >> student.computerScienceGrade;

    cout << "\n";
}

// ������� ��� �������� ���������� ��� ��� ��������
void inputStudentsData(Student* students, int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        cout << "������ ���������� ��� �������� " << i + 1 << ":\n";
        inputStudentData(students[i]);
    }
}

// ������� ��� ���������� ������� �������� � �������� �������� � ������
int countStudentsWithGoodPhysicsGrades(Student* students, int numStudents) {
    int count = 0;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].physicsGrade == 4 || students[i].physicsGrade == 5) {
            count++;
        }
    }
    return count;
}
double calculateAverageGrade(Student* students, int numStudents, double Student::* gradeType) {
    double totalGrade = 0;
    for (int i = 0; i < numStudents; ++i) {
        totalGrade += students[i].*gradeType;
    }
    return totalGrade / numStudents;
}
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int numStudents;
    cout << "������ ������� ��������: ";
    cin >> numStudents;

    // ��������� ���������� ������ ��������
    Student* students = new Student[numStudents];

    // �������� ���������� ��� ��������
    inputStudentsData(students, numStudents);

    // ���������� ����������� ������� ������������
    size_t maxSpecializationLength = 0;
    for (int i = 0; i < numStudents; ++i) {
        switch (students[i].specialization) {
        case COMPUTER_SCIENCE:
            maxSpecializationLength = max(maxSpecializationLength, strlen("����'����� �����"));
            break;
        case COMPUTER_ENGINEERING:
            maxSpecializationLength = max(maxSpecializationLength, strlen("�������������"));
            break;
        case INFORMATION_SYSTEMS_AND_TECHNOLOGIES:
            maxSpecializationLength = max(maxSpecializationLength, strlen("�������� ��������"));
            break;
        case CIVIL_ENGINEERING:
            maxSpecializationLength = max(maxSpecializationLength, strlen("������� ��������"));
            break;
        }
    }

    // ��������� ��������� �������
    cout << "-----------------------------------------------------------------------------------------------------------------\n";
    cout << "| ���������� �  | �������      | ���� | ������������                      | Գ���� | ���������� | ����������� |\n";
    cout << "-----------------------------------------------------------------------------------------------------------------\n";

    // ��������� ����� ��� ��������
    for (int i = 0; i < numStudents; ++i) {
        cout << "| " << setw(13) << i + 1 << " | " << setw(13) << students[i].surname << " | " << setw(4) << students[i].course << " | ";

        switch (students[i].specialization) {
        case COMPUTER_SCIENCE:
            cout << "����'����� �����                 ";
            break;
        case COMPUTER_ENGINEERING:
            cout << "�����'����� ��������             ";
            break;
        case INFORMATION_SYSTEMS_AND_TECHNOLOGIES:
            cout << "����������� ������� �� �������㳿";
            break;
        }

        cout << " | " << setw(6) << students[i].physicsGrade << " | " << setw(10) << students[i].mathGrade << " | " << setw(11) << students[i].computerScienceGrade << " |\n"<< "-----------------------------------------------------------------------------------------------------------------\n";
    }

    // ���������� �� ��������� ������� ��������, �� �������� � ������ ������ "5" ��� "4"
    int studentsWithGoodPhysicsGrades = countStudentsWithGoodPhysicsGrades(students, numStudents);
    cout << "ʳ������ �������� � �������� �������� � ������: " << studentsWithGoodPhysicsGrades << endl;
    // ���������� �� ��������� ���������� ���� ��� ������� ��������
    double averagePhysicsGrade = calculateAverageGrade(students, numStudents, &Student::physicsGrade);
    double averageMathGrade = calculateAverageGrade(students, numStudents, &Student::mathGrade);
    double averageComputerScienceGrade = calculateAverageGrade(students, numStudents, &Student::computerScienceGrade);

    cout << "\n������ ����:\n";
    cout << "Գ����: " << averagePhysicsGrade << endl;
    cout << "����������: " << averageMathGrade << endl;
    cout << "�����������: " << averageComputerScienceGrade << endl;
    // ��������� ���'��, ������� ��� ���������� ������
    delete[] students;

    return 0;
}
