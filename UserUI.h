// UserUI.h

#ifndef USERUI_H
#define USERUI_H

#include <iostream>
#include <string>

class UserUI {
public:
    static void showMenu(const std::string& username) { // Accept username as a parameter
        int choice;

        while (true) {
            std::cout << "\nUser Menu for " << username << ":" << std::endl;
            std::cout << "1. Edit Profile" << std::endl;
            std::cout << "2. Rent a Motorbike" << std::endl;
            std::cout << "3. Log out" << std::endl;
            std::cout << "Enter your choice (1/2/3): ";

            std::cin >> choice;

            switch (choice) {
                case 1:
                    editUserProfile(username);
                    break;
                case 2:
                    rentMotorbike(username);
                    break;
                case 3:
                    std::cout << "Logging out. Goodbye, " << username << "!" << std::endl;
                    return;
                default:
                    std::cout << "Invalid choice. Please enter a valid option (1/2/3)." << std::endl;
                    break;
            }
        }
    }

private:
    static void editUserProfile(const std::string& username) {
        // Implement user profile editing functionality here
        std::cout << "Editing user profile for " << username << "." << std::endl;
    }

    static void rentMotorbike(const std::string& username) {
        // Implement motorbike rental functionality here
        std::cout << "Renting a motorbike for " << username << "." << std::endl;
    }
};

#endif // USERUI_H
