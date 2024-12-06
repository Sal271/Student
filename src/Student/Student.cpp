#pragma once

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Student {
protected:
    string firstName;
    string lastName;
    string studentID;
    string major;
    string email;
    double gpa;
    int semester;

public:
    // Constructor with default values
    Student(string first = "none", string last = "none", string id = "none", 
            string studentMajor = "Undeclared", string studentEmail = "none", 
            double studentGPA = 0.0, int currentSemester = 0)
        : firstName(first), lastName(last), studentID(id), 
          major(studentMajor), email(studentEmail), 
          gpa(studentGPA), semester(currentSemester) {}

    // Getters
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getFullName() const { return firstName + " " + lastName; }
    string getStudentID() const { return studentID; }
    string getMajor() const { return major; }
    string getEmail() const { return email; }
    double getGPA() const { return gpa; }
    int getSemester() const { return semester; }

    // Setters
    void setFirstName(const string& newFirstName) { firstName = newFirstName; }
    void setLastName(const string& newLastName) { lastName = newLastName; }
    void setStudentID(const string& newID) { studentID = newID; }
    void setMajor(const string& newMajor) { major = newMajor; }
    void setEmail(const string& newEmail) { email = newEmail; }
    void setGPA(double newGPA) { gpa = newGPA; }
    void setSemester(int newSemester) { semester = newSemester; }

    // Display student information
    virtual void displayInfo() const {
        cout << left 
             << setw(20) << getFullName()
             << setw(15) << studentID
             << setw(20) << major
             << setw(10) << fixed << setprecision(2) << gpa
             << setw(10) << semester;
    }

    virtual ~Student() {}
};