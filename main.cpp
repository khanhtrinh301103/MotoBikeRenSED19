#include <iostream>
#include "AdminLogin.h"
#include "UserLogin.h"
#include "RegisterAccount.h"
#include "AdminUI.h"

using namespace std;

int main() {
    int choice;

    while (true) {
        cout << "\nWelcome to the EliteMoto rental service!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1/2/3): ";

        cin >> choice;

        switch (choice) {
            case 1:
                {
                    cout << "You selected 'Login'. Please enter your username: ";
                    string username;
                    cin >> username;
                    
                    cout << "Please enter your password: ";
                    string password;
                    cin >> password;

                    if (AdminLogin::isAdminLoginValid(username, password)) {
                        cout << "Admin login successful. Welcome, " << username << "!" << endl;
                        AdminUI::showMenu(); // Show the admin menu
                    } else if (UserLogin::isUserLoginValid(username, password)) {
                        cout << "User login successful. Welcome, " << username << "!" << endl;
                        // Add user-specific functionality here
                    } else {
                        cout << "Login failed. Please check your username and password." << endl;
                    }
                }
                break;
            case 2:
                {
                    cout << "You selected 'Register'. Please enter a new username: ";
                    string newUsername;
                    cin >> newUsername;

                    cout << "Please enter a new password: ";
                    string newPassword;
                    cin >> newPassword;

                    cout << "Please confirm your password: ";
                    string confirmPassword;
                    cin >> confirmPassword;

                    if (newPassword == confirmPassword) {
                        if (RegisterAccount::registerUser(newUsername, newPassword, confirmPassword)) {
                            cout << "Registration successful. You can now log in as a user." << endl;
                        } else {
                            cout << "Registration failed. Please try again." << endl;
                        }
                    } else {
                        cout << "Password confirmation does not match. Please try again." << endl;
                    }
                }
                break;
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please enter a valid option (1/2/3)." << endl;
                break;
        }
    }

    return 0;
}
