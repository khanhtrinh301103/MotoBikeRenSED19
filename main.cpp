#include <iostream>
#include "AdminLogin.h"
#include "UserLogin.h"
#include "RegisterAccount.h"
#include "AdminUI.h"
#include "ProductDetails.h"
#include "UserUI.h"
#include "searchEngine.h"

using namespace std;

int main() {
    int choice;

    while (true) {
        cout << "========================================"<< endl;
        cout << "WELCOME TO THE ELITEMOTO RENTAL SERVICE!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. View Motorbikes Available" << endl; // New option
        cout << "4. Search for motorbikes by city name" << endl;
        cout << "5. Exit" << endl;
        cout << "========================================"<< endl;
        cout << "Enter your choice (1-5): ";

        cin >> choice;

        switch (choice) {
            case 1:
                {
                    cout << "\nYou selected 'Login'. Please enter your username: ";
                    string username;
                    cin >> username;
                    
                    cout << "Please enter your password: ";
                    string password;
                    cin >> password;

                    if (AdminLogin::isAdminLoginValid(username, password)) {
                        cout << "\nAdmin login successful. Welcome, " << username << "!" << endl;
                        AdminUI::showMenu(); // Show the admin menu
                    } else if (UserLogin::isUserLoginValid(username, password)) {
                        cout << "\nUser login successful. Welcome, " << username << "!" << endl;
                        UserUI::showMenu(username);
                        // Add user-specific functionality here
                    } else {
                        cout << "Login failed. Please check your username or password." << endl;
                    }
                }
                break;
            case 2:
                {
                    cout << "\nYou selected 'Register'. Please enter a new username: ";
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
                // Display product details when choosing option 3
                cout << "\nViewing available motorbikes:" << endl;
                ProductDetails::displayProductDetails(); // Call the function using the class
                break;
            case 4:
                SearchEngine::searchMotorbikesByCity();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please enter a valid option (1/2/3/4)." << endl;
                break;
        }
    }

    return 0;
}
