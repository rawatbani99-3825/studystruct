/* Login (C++ class that uses the C hash map in auth.c) */
#include <iostream>
#include <string>
using namespace std;

#include "login.h"
#include "auth.h"

bool Login::run() {
    int choice;
    string name, pass;
    while (true) {
        cout << "\nSMART STUDY PLANNER\n";
        cout << "1. Signup  2. Login  0. Exit\nChoice: ";
        cin >> choice;
        if (cin.eof())
            return false;
        if (cin.fail()) {          // letters or symbols instead of a number
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }
        if (choice == 0)
            return false;
        if (choice != 1 && choice != 2) {
            cout << "Invalid choice. Enter 0, 1 or 2.\n";
            continue;
        }
        cout << "Username: ";
        cin >> name;
        cout << "Password: ";
        cin >> pass;
        if (choice == 1) {
            signupUser(name.c_str(), pass.c_str());
        } else {
            if (loginUser(name.c_str(), pass.c_str())) {
                cout << "Welcome " << name << endl;
                return true;
            }
            cout << "Wrong username or password\n";
        }
    }
}
