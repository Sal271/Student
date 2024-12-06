#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <fstream>
#include <iomanip>
#include "Student.cpp"
using namespace std;

class StudentManager {
private:
    vector<Student*> students;

    // Helper function to validate email format
    bool validateEmail(const string& email) {
        regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
        return regex_match(email, emailPattern);
    }

    // Helper function to validate student ID format
    bool validateStudentID(const string& id) {
        regex idPattern(R"(^\d{8}$)"); // Assumes 8-digit student ID
        return regex_match(id, idPattern);
    }

public:
    void addStudent() {
        char choice;
        do {
            string firstName, lastName, studentID, major, email;
            double gpa;
            int semester;

            cout << "Enter the first name: ";
            cin.ignore();
            getline(cin, firstName);

            cout << "Enter the last name: ";
            getline(cin, lastName);

            // Student ID input with validation
            while (true) {
                cout << "Enter student ID (8 digits): ";
                getline(cin, studentID);
                if (validateStudentID(studentID)) {
                    // Check if student ID already exists
                    auto it = find_if(students.begin(), students.end(),
                        [&studentID](Student* student) { 
                            return student->getStudentID() == studentID; 
                        });
                    
                    if (it == students.end()) break;
                    cout << "Student ID already exists. Please enter a unique ID.\n";
                }
                cout << "Invalid student ID. Please enter an 8-digit number.\n";
            }

            cout << "Enter major: ";
            getline(cin, major);

            // Email input with validation
            while (true) {
                cout << "Enter email address: ";
                getline(cin, email);
                if (validateEmail(email)) break;
                cout << "Invalid email format. Please enter a valid email address.\n";
            }

            cout << "Enter current semester (1-8): ";
            while (!(cin >> semester) || semester < 1 || semester > 8) {
                cin.clear();
                cin.ignore(10, '\n');
                cout << "Invalid input. Please enter a semester between 1 and 8: ";
            }
            cin.ignore();

            cout << "Enter current GPA (0.0-4.0): ";
            while (!(cin >> gpa) || gpa < 0.0 || gpa > 4.0) {
                cin.clear();
                cin.ignore(10, '\n');
                cout << "Invalid input. Please enter a GPA between 0.0 and 4.0: ";
            }
            cin.ignore();

            students.push_back(new Student(firstName, lastName, studentID, major, email, gpa, semester));
            cout << "Student added successfully.\n";

            cout << "Do you want to add another student? (y/n): ";
            cin >> choice;
            cin.ignore();

        } while (tolower(choice) == 'y');
    }

    void editStudent() {
        if (students.empty()) {
            cout << "No students available to edit.\n";
            return;
        }

        string studentID;
        cout << "Enter the student ID of the student you want to edit: ";
        cin.ignore();
        getline(cin, studentID);

        auto it = find_if(students.begin(), students.end(),
                          [&studentID](Student* student) { 
                              return student->getStudentID() == studentID; 
                          });

        if (it != students.end()) {
            Student* student = *it;
            int editChoice;

            cout << "What would you like to edit?\n";
            cout << "1. First Name\n";
            cout << "2. Last Name\n";
            cout << "3. Major\n";
            cout << "4. Email\n";
            cout << "5. Semester\n";
            cout << "6. GPA\n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            cin >> editChoice;
            cin.ignore();

            switch (editChoice) {
                case 1: {
                    string newFirstName;
                    cout << "Enter new first name: ";
                    getline(cin, newFirstName);
                    student->setFirstName(newFirstName);
                    break;
                }
                case 2: {
                    string newLastName;
                    cout << "Enter new last name: ";
                    getline(cin, newLastName);
                    student->setLastName(newLastName);
                    break;
                }
                case 3: {
                    string newMajor;
                    cout << "Enter new major: ";
                    getline(cin, newMajor);
                    student->setMajor(newMajor);
                    break;
                }
                case 4: {
                    string newEmail;
                    while (true) {
                        cout << "Enter new email address: ";
                        getline(cin, newEmail);
                        if (validateEmail(newEmail)) {
                            student->setEmail(newEmail);
                            break;
                        }
                        cout << "Invalid email format.\n";
                    }
                    break;
                }
                case 5: {
                    int newSemester;
                    cout << "Enter new semester (1-8): ";
                    while (!(cin >> newSemester) || newSemester < 1 || newSemester > 8) {
                        cin.clear();
                        cin.ignore(10, '\n');
                        cout << "Invalid input. Please enter a semester between 1 and 8: ";
                    }
                    cin.ignore();
                    student->setSemester(newSemester);
                    break;
                }
                case 6: {
                    double newGPA;
                    cout << "Enter new GPA (0.0-4.0): ";
                    while (!(cin >> newGPA) || newGPA < 0.0 || newGPA > 4.0) {
                        cin.clear();
                        cin.ignore(10, '\n');
                        cout << "Invalid input. Please enter a GPA between 0.0 and 4.0: ";
                    }
                    cin.ignore();
                    student->setGPA(newGPA);
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
            }

            cout << "Student information updated successfully.\n";
        } else {
            cout << "Student with ID \"" << studentID << "\" not found.\n";
        }
    }

    void viewStudents() {
        if (students.empty()) {
            cout << "No students were found.\n";
            return;
        }

        cout << left
             << setw(20) << "Full Name"
             << setw(15) << "Student ID"
             << setw(20) << "Major"
             << setw(10) << "GPA"
             << setw(10) << "Semester"
             << endl;
        cout << string(75, '-') << endl;

        for (Student* student : students) {
            student->displayInfo();
            cout << endl;
        }
    }

    void deleteStudent() {
        if (students.empty()) {
            cout << "No students available to delete.\n";
            return;
        }

        string studentID;
        cout << "Enter the student ID of the student you want to delete: ";
        cin.ignore();
        getline(cin, studentID);

        auto it = find_if(students.begin(), students.end(),
                          [&studentID](Student* student) { 
                              return student->getStudentID() == studentID; 
                          });

        if (it != students.end()) {
            char confirm;
            cout << "Are you sure you want to delete the student with ID \"" << studentID << "\"? (y/n): ";
            cin >> confirm;

            if (tolower(confirm) == 'y') {
                delete *it;
                students.erase(it);
                cout << "Student deleted successfully.\n";
            } else {
                cout << "Deletion cancelled.\n";
            }
        } else {
            cout << "Student with ID \"" << studentID << "\" not found.\n";
        }
    }

    void searchStudent() {
        if (students.empty()) {
            cout << "No students were found.\n";
            return;
        }

        string searchTerm;
        cout << "Enter the student ID or name to search: ";
        cin.ignore();
        getline(cin, searchTerm);

        bool found = false;
        for (Student* student : students) {
            if (student->getStudentID() == searchTerm || 
                student->getFirstName() == searchTerm || 
                student->getLastName() == searchTerm ||
                student->getFullName() == searchTerm) {
                
                cout << left
                     << setw(20) << "Full Name"
                     << setw(15) << "Student ID"
                     << setw(20) << "Major"
                     << setw(10) << "GPA"
                     << setw(10) << "Semester"
                     << endl;
                cout << string(75, '-') << endl;

                student->displayInfo();
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No student found with the search term \"" << searchTerm << "\".\n";
        }
    }

    void sortStudents() {
        if (students.empty()) {
            cout << "No students available to sort.\n";
            return;
        }

        int sortChoice;
        cout << "Sort by:\n";
        cout << "1. Name (Alphabetical)\n";
        cout << "2. GPA (Ascending)\n";
        cout << "3. GPA (Descending)\n";
        cout << "4. Semester\n";
        cout << "Enter your choice: ";
        cin >> sortChoice;
        cin.ignore();

        switch (sortChoice) {
            case 1:
                sort(students.begin(), students.end(),
                     [](Student* a, Student* b) { 
                         return a->getFullName() < b->getFullName(); 
                     });
                cout << "Students sorted alphabetically by name.\n";
                break;
            case 2:
                sort(students.begin(), students.end(),
                     [](Student* a, Student* b) { 
                         return a->getGPA() < b->getGPA(); 
                     });
                cout << "Students sorted by GPA in ascending order.\n";
                break;
            case 3:
                sort(students.begin(), students.end(),
                     [](Student* a, Student* b) { 
                         return a->getGPA() > b->getGPA(); 
                     });
                cout << "Students sorted by GPA in descending order.\n";
                break;
            case 4:
                sort(students.begin(), students.end(),
                     [](Student* a, Student* b) { 
                         return a->getSemester() < b->getSemester(); 
                     });
                cout << "Students sorted by semester.\n";
                break;
            default:
                cout << "Invalid choice.\n";
                return;
        }
    }
    void saveStudent() {
    string filePath = "../data/students.dat";
    ofstream file(filePath, ios::binary);
    
    if (!file) {
        cerr << "Failed to open file: " << filePath << endl;
        return;
    }

    size_t studentCount = students.size();
    file.write(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));

    for (const auto* student : students) {
        // Write each student's data
        string data = student->getFirstName() + "\n" + 
                      student->getLastName() + "\n" + 
                      student->getStudentID() + "\n" + 
                      student->getMajor() + "\n" + 
                      student->getEmail() + "\n" + 
                      to_string(student->getGPA()) + "\n" + 
                      to_string(student->getSemester()) + "\n";
        
        size_t dataSize = data.size();
        file.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        file.write(data.c_str(), dataSize);
    }

    file.close();
    cout << "Students saved successfully.\n";
}

    // Destructor to free dynamically allocated memory
    ~StudentManager() {
        for (Student* student : students) {
            delete student;
        }
        students.clear();
    }
};