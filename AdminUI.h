// AdminUI.h

#ifndef ADMINUI_H
#define ADMINUI_H

#include <iostream>
#include <fstream>
#include <string>

class AdminUI {
public:
    static void showMenu() {
        int choice;

        while (true) {
            std::cout << "\nAdmin Menu:" << std::endl;
            std::cout << "1. View all user accounts" << std::endl;
            std::cout << "2. Log out" << std::endl;
            std::cout << "Enter your choice (1/2): ";

            std::cin >> choice;

            switch (choice) {
                case 1:
                    viewAllUserAccounts();
                    break;
                case 2:
                    std::cout << "Exiting admin account. Goodbye!" << std::endl;
                    return;
                default:
                    std::cout << "Invalid choice. Please enter a valid option (1/2)." << std::endl;
                    break;
            }
        }
    }

private:
    static void viewAllUserAccounts() {
        std::ifstream userFile("userAccount.txt");

        if (userFile.is_open()) {
            std::string username;
            std::string password;

            std::cout << "\nList of User Accounts:" << std::endl;
            while (userFile >> username >> password) {
                std::cout << "Username: " << username << "\tPassword: " << password << std::endl;
            }

            userFile.close();
        } else {
            std::cout << "Failed to open user account file." << std::endl;
        }
    }
};

#endif // ADMINUI_H
