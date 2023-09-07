#include <iostream>
#include "AdminLogin.h"
#include "UserLogin.h"
#include "RegisterAccount.h"

using namespace std;

int main() {
    int choice;

    while (true) {
        cout << "Welcome to the program!" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Member" << endl;
        cout << "3. Register" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1/2/3/4): ";

        cin >> choice;

        switch (choice) {
            case 1:
                {
                    cout << "You selected 'Login as Admin'. Please enter your username: ";
                    string username;
                    cin >> username;
                    
                    cout << "Please enter your password: ";
                    string password;
                    cin >> password;

                    if (AdminLogin::isAdminLoginValid(username, password)) {
                        cout << "Admin login successful. Welcome, " << username << "!" << endl;
                        // Add admin-specific functionality here
                    } else {
                        cout << "Admin login failed. Please check your username and password." << endl;
                    }
                }
                break;
            case 2:
                {
                    cout << "You selected 'Login as Member'. Please enter your username: ";
                    string username;
                    cin >> username;
                    
                    cout << "Please enter your password: ";
                    string password;
                    cin >> password;

                    if (UserLogin::isUserLoginValid(username, password)) {
                        cout << "User login successful. Welcome, " << username << "!" << endl;
                        // Add user-specific functionality here
                    } else {
                        cout << "User login failed. Please check your username and password." << endl;
                    }
                }
                break;
            case 3:
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

                    if (RegisterAccount::registerUser(newUsername, newPassword, confirmPassword)) {
                        cout << "Registration successful. You can now log in as a user." << endl;
                    } else {
                        cout << "Registration failed. Please try again." << endl;
                    }
                }
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please enter a valid option (1/2/3/4)." << endl;
                break;
        }
    }

    return 0;
}
