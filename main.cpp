#include <iostream>
#include "AdminLogin.h"
#include "UserLogin.h"
#include "RegisterAccount.h"
#include "AdminUI.h"
#include "ProductDetails.h"
#include "UserUI.h"
#include "searchEngine.h"
#include <limits> // Include this header for numeric_limits

using namespace std;

int main() {
    int userType;
    string username;
    string password;
    
    while (true) {
        cout << "===============================================" << endl;
        cout << "    WELCOME TO THE ELITEMOTO RENTAL SERVICE" << endl;
        cout << "===============================================" << endl;
        cout << "Use the app as: 1. Guest   2. Member   3. Admin" << endl;
        cout << "Enter choice: ";
        
        if (!(cin >> userType)) {
            // Input is not an integer
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Invalid input. Please enter a valid integer choice (1-3).\n" << endl;
            continue; // Skip the rest of the loop iteration and ask for input again
        }

        switch (userType) {
            case 1: // Guest
                while (true) {
                    cout << "\nGuest Menu:" << endl;
                    cout << "1. Register" << endl;
                    cout << "2. View Motorbikes Available" << endl;
                    cout << "3. Search for motorbikes by city name" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter choice: ";
                    if (!(cin >> userType)) {
                        // Input is not an integer
                        cin.clear(); // Clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                        cout << "Invalid input. Please enter a valid integer choice (1-4).\n" << endl;
                        continue; // Skip the rest of the loop iteration and ask for input again
                    }

                    switch (userType) {
                        case 1:
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

                                RegisterAccount::PaymentMethod paymentMethod = RegisterAccount::selectPaymentMethod();

                                if (newPassword == confirmPassword) {
                                    if (RegisterAccount::registerUser(newUsername, newPassword, confirmPassword, paymentMethod)) {
                                        cout << "Registration successful. You can now log in as a user." << endl;
                                        cout << "\nLogin successfully. Welcome, our member " << newUsername << "!" << endl;
                                        UserUI::showMenu(newUsername);
                                    } else {
                                        cout << "Registration failed. Please try again." << endl;
                                    }
                                } else {
                                    cout << "Password confirmation does not match. Please try again." << endl;
                                }
                            }
                            break;
                        case 2:
                            // Display product details when choosing option 3
                            cout << "\nViewing available motorbikes:" << endl;
                            ProductDetails::displayProductDetails(); // Call the function using the class
                            break;
                        case 3:
                            SearchEngine::searchMotorbikesByCity();
                            break;
                        case 4:
                            cout << "Exiting the program. Goodbye!" << endl;
                            return 0;
                        default:
                            cout << "Invalid choice. Please enter a valid option (1/2/3/4)." << endl;
                            break;
                    }
                }
                break;
            case 2: // Member
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (UserLogin::isUserLoginValid(username, password)) {
                    cout << "\nLogin successfully. Welcome, our member " << username << "!" << endl;
                    UserUI::showMenu(username);
                    // Add user-specific functionality here
                } else {
                    cout << "Login failed. Please check your username or password." << endl;
                }
                break;
            case 3: // Admin
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (AdminLogin::isAdminLoginValid(username, password)) {
                    cout << "\nLogin to admin successfully. Welcome !!!" << endl;
                    AdminUI::showMenu(); // Show the admin menu
                } else {
                    cout << "Login failed. Please check your username or password." << endl;
                }
                break;
            default:
                cout << "Invalid choice. Please enter a valid option (1/2/3)." << endl;
                break;
        }
    }

    return 0;
}
