#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <string>
#include "StudentManager.cpp"
#include "../User/UserManager.cpp"
using namespace std;

class Application {
private: 
    int choice;
    StudentManager studentManager;
    UserManager userManager;

    void displayMainMenu() {
        cout << "\n-----Main Menu------\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "0. Exit\n";
        cout << "---------------------------\n";
    }

    void displayAdminMenu() {
        cout << "\n-----Admin Menu------\n";
        cout << "1. User Management\n";
        cout << "2. Student Management\n";
        cout << "0. Logout\n";
        cout << "---------------------------\n";
    }

    void displayUserMenu() {
        cout << "\n-----User Menu------\n";
        cout << "1. View Students\n";
        cout << "2. Search Students\n";
        cout << "0. Logout\n";
        cout << "---------------------------\n";
    }

    void handleStudentManagement() {
        do {
            cout << "\n-----Student Manager------\n";
            cout << "1. Add Student\n";
            cout << "2. Edit Student\n";
            cout << "3. View Students\n";
            cout << "4. Delete Student\n";
            cout << "5. Sort Students\n";
            cout << "6. Search Students\n";
            cout << "7. Save Students\n";
            cout << "0. Exit\n";
            cout << "---------------------------\n";
            cin >> choice;

            switch(choice) {
                case 1: studentManager.addStudent(); break;
                case 2: studentManager.editStudent(); break;
                case 3: studentManager.viewStudents(); break;
                case 4: studentManager.deleteStudent(); break;
                case 5: studentManager.sortStudents(); break;
                case 6: studentManager.searchStudent(); break;
                case 7: studentManager.saveStudent(); break;
                case 0: return;
                default: cout << "Invalid choice\n";
            }
        } while(choice != 0);
    }

public: 
    void run() {
        try {
            do {
                displayMainMenu();
                cin >> choice;

                switch(choice) {
                    case 1: // Login
                        if (userManager.login()) {
                            User* currentUser = userManager.getCurrentUser();
                            if (currentUser->getRole() == UserRole::ADMIN) {
                                do {
                                    displayAdminMenu();
                                    cin >> choice;

                                    switch(choice) {
                                        case 1: userManager.displayUserManagement(); break;
                                        case 2: handleStudentManagement(); break;
                                        case 0: userManager.logout(); break;
                                        default: cout << "Invalid choice\n";
                                    }
                                } while(choice != 0);
                            } else { // User Role
                                do {
                                    displayUserMenu();
                                    cin >> choice;

                                    switch(choice) {
                                        case 1: studentManager.viewStudents(); break;
                                        case 2: studentManager.searchStudent(); break;
                                        case 0: userManager.logout(); break;
                                        default: cout << "Invalid choice\n";
                                    }
                                } while(choice != 0);
                            }
                        }
                        break;
                    case 2: // Register
                        userManager.registerUser();
                        break;
                    case 0: // Exit
                        cout << "Exiting....\n";
                        return;
                    default:
                        cout << "Invalid choice\n";
                }
            } while(true);
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};