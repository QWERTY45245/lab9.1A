#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

// Перелік спеціальностей
enum Specialization {
    COMPUTER_SCIENCE,
    COMPUTER_ENGINEERING,
    INFORMATION_SYSTEMS_AND_TECHNOLOGIES,
    CIVIL_ENGINEERING
};

// Структура для зберігання інформації про студента
struct Student {
    string surname;
    int course;
    Specialization specialization;
    double physicsGrade;
    double mathGrade;
    double computerScienceGrade;
};

// Функція для введення інформації про одного студента
void inputStudentData(Student& student) {
    cout << "Прізвище: ";
    cin >> student.surname;

    cout << "Курс: ";
    cin >> student.course;

    cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Компю'терна інженерія, 2 - Інформаційні системи та технології): ";
    int specializationInput;
    cin >> specializationInput;

    if (specializationInput >= 0 && specializationInput <= 2) {
        student.specialization = static_cast<Specialization>(specializationInput);
    }
    else {
        cout << "Некоректний ввід для спеціальності. Використовується значення за замовчуванням (Комп'ютерні науки).\n";
        student.specialization = COMPUTER_SCIENCE;
    }

    cout << "Оцінка з фізики: ";
    cin >> student.physicsGrade;

    cout << "Оцінка з математики: ";
    cin >> student.mathGrade;

    cout << "Оцінка з інформатики: ";
    cin >> student.computerScienceGrade;

    cout << "\n";
}

// Функція для введення інформації про всіх студентів
void inputStudentsData(Student* students, int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        cout << "Введіть інформацію для студента " << i + 1 << ":\n";
        inputStudentData(students[i]);
    }
}

// Функція для обчислення кількості студентів з високими оцінками з фізики
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
    cout << "Введіть кількість студентів: ";
    cin >> numStudents;

    // Створення динамічного масиву студентів
    Student* students = new Student[numStudents];

    // Введення інформації про студентів
    inputStudentsData(students, numStudents);

    // Визначення максимальної довжини спеціальності
    size_t maxSpecializationLength = 0;
    for (int i = 0; i < numStudents; ++i) {
        switch (students[i].specialization) {
        case COMPUTER_SCIENCE:
            maxSpecializationLength = max(maxSpecializationLength, strlen("Комп'ютерні науки"));
            break;
        case COMPUTER_ENGINEERING:
            maxSpecializationLength = max(maxSpecializationLength, strlen("Електротехніка"));
            break;
        case INFORMATION_SYSTEMS_AND_TECHNOLOGIES:
            maxSpecializationLength = max(maxSpecializationLength, strlen("Механічна інженерія"));
            break;
        case CIVIL_ENGINEERING:
            maxSpecializationLength = max(maxSpecializationLength, strlen("Цивільна інженерія"));
            break;
        }
    }

    // Виведення заголовка таблиці
    cout << "-----------------------------------------------------------------------------------------------------------------\n";
    cout << "| Порядковий №  | Прізвище      | Курс | Спеціальність                      | Фізика | Математика | Інформатика |\n";
    cout << "-----------------------------------------------------------------------------------------------------------------\n";

    // Виведення даних про студентів
    for (int i = 0; i < numStudents; ++i) {
        cout << "| " << setw(13) << i + 1 << " | " << setw(13) << students[i].surname << " | " << setw(4) << students[i].course << " | ";

        switch (students[i].specialization) {
        case COMPUTER_SCIENCE:
            cout << "Комп'ютерні науки                 ";
            break;
        case COMPUTER_ENGINEERING:
            cout << "Компю'терна інженерія             ";
            break;
        case INFORMATION_SYSTEMS_AND_TECHNOLOGIES:
            cout << "Інформаційні системи та технології";
            break;
        }

        cout << " | " << setw(6) << students[i].physicsGrade << " | " << setw(10) << students[i].mathGrade << " | " << setw(11) << students[i].computerScienceGrade << " |\n"<< "-----------------------------------------------------------------------------------------------------------------\n";
    }

    // Обчислення та виведення кількості студентів, які отримали з фізики оцінки "5" або "4"
    int studentsWithGoodPhysicsGrades = countStudentsWithGoodPhysicsGrades(students, numStudents);
    cout << "Кількість студентів з високими оцінками з фізики: " << studentsWithGoodPhysicsGrades << endl;
    // Обчислення та виведення середнього балу для кожного предмету
    double averagePhysicsGrade = calculateAverageGrade(students, numStudents, &Student::physicsGrade);
    double averageMathGrade = calculateAverageGrade(students, numStudents, &Student::mathGrade);
    double averageComputerScienceGrade = calculateAverageGrade(students, numStudents, &Student::computerScienceGrade);

    cout << "\nСередні бали:\n";
    cout << "Фізика: " << averagePhysicsGrade << endl;
    cout << "Математика: " << averageMathGrade << endl;
    cout << "Інформатика: " << averageComputerScienceGrade << endl;
    // Звільнення пам'яті, виділеної для динамічного масиву
    delete[] students;

    return 0;
}
