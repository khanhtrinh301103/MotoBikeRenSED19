#ifndef USERUI_H
#define USERUI_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "searchEngine.h"
#include <limits>

class UserUI {
public:
    static void showMenu(const std::string& username) {
        int choice;

        while (true) {
            std::cout << "\nMember Menu for " << username << ":" << std::endl;
            std::cout << "1. Fill User Profile" << std::endl;
            std::cout << "2. Edit User Profile" << std::endl;
            std::cout << "3. Search Motorbikes by City" << std::endl;
            std::cout << "4. Rent a Motorbike" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "Enter your choice (1-5): ";

            if (!(std::cin >> choice) || choice < 1 || choice > 5) {
                // Input is not a valid integer in the range (1-5)
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid input. Please enter a valid integer choice (1-5).\n" << std::endl;
                continue; // Skip the rest of the loop iteration and ask for input again
            }

            switch (choice) {
                case 1:
                    fillUserProfile(username);
                    break;
                case 2:
                    editUserProfile(username);
                    break;
                case 3:
                    SearchEngine::searchMotorbikesByCity();
                    break;
                case 4:
                    rentMotorbike(username);
                    break;
                case 5:
                    std::cout << "Exiting the User Menu. Goodbye!\n" << std::endl;
                    return;
                default:
                    break;
            }
        }
    }

    static void fillUserProfile(const std::string& username) {
        std::fstream userProfileFile("userProfile.txt", std::ios::in | std::ios::out);

        if (!userProfileFile.is_open()) {
            std::cout << "Error opening userProfile.txt." << std::endl;
            return;
        }

        bool found = false;
        std::string line;
        std::string updatedProfileData;

        while (std::getline(userProfileFile, line)) {
            if (line.find("Username: " + username) != std::string::npos) {
                // User profile already exists
                found = true;
                std::cout << "Profile for username " << username << " already exists." << std::endl;
                break;
            }
        }

        if (found) {
            userProfileFile.close();
            return;
        }

        // Prompt the user to fill in their profile details
        std::string fullName;
        int phone;
        std::string idType;
        int idNum;
        int driverLicenseNum;
        std::string expiredDate;

        std::cin.ignore(); // Consume the newline character left in the buffer

        std::cout << "Please fill in your profile details:" << std::endl;

        std::cout << "Full Name: ";
        std::getline(std::cin, fullName);

        std::cout << "Phone: ";
        std::cin >> phone;

        std::cin.ignore(); // Consume the newline character left in the buffer

        std::cout << "ID Type: ";
        std::getline(std::cin, idType);

        std::cout << "ID Number: ";
        std::cin >> idNum;

        std::cout << "Driver's License Number: ";
        std::cin >> driverLicenseNum;

        std::cout << "Expired Date (MM/YY): ";
        std::cin >> expiredDate;

        // Add the user's profile data to the file
        userProfileFile.seekp(0, std::ios::end);
        userProfileFile << "Username: " << username << "\n";
        userProfileFile << "Full Name: " << fullName << "\n";
        userProfileFile << "Phone: " << phone << "\n";
        userProfileFile << "ID Type: " << idType << "\n";
        userProfileFile << "ID Number: " << idNum << "\n";
        userProfileFile << "Driver's License Number: " << driverLicenseNum << "\n";
        userProfileFile << "Expired Date: " << expiredDate << "\n";
        userProfileFile << "MotorbikeRentingID: 0\n"; // Initialize to 0
        userProfileFile << std::endl; // Add an empty line to separate profiles

        userProfileFile.close();
        std::cout << "Profile saved successfully!" << std::endl;
    }

    static void editUserProfile(const std::string& username) {
        std::string fileName = "userProfile.txt"; // Use just the file name

        std::ifstream inputFile(fileName);
        if (!inputFile) {
            std::cout << "File not found." << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }

        inputFile.close();

        bool found = false;

        for (size_t i = 0; i < lines.size(); i++) {
            if (lines[i].find("Username: " + username) != std::string::npos) {
                // User profile found, display and edit details
                std::cout << "Found user profile for: " << username << std::endl;
                std::cout << "Current details:" << std::endl;

                // Print current details
                for (size_t j = i; j < i + 7; j++) {
                    std::cout << lines[j] << std::endl;
                }

                // Prompt for new details
                std::cout << "\nEnter new details:" << std::endl;

                std::cout << "Full Name: ";
                std::string newFullName;
                std::cin.ignore(); // Clear the newline left in the buffer
                std::getline(std::cin, newFullName);
                lines[i + 1] = "Full Name: " + newFullName;

                std::cout << "Phone: ";
                std::string newPhone;
                std::getline(std::cin, newPhone);
                lines[i + 2] = "Phone: " + newPhone;

                std::cout << "ID Type: ";
                std::string newIdType;
                std::getline(std::cin, newIdType);
                lines[i + 3] = "ID Type: " + newIdType;

                std::cout << "ID Number: ";
                std::string newIdNumber;
                std::getline(std::cin, newIdNumber);
                lines[i + 4] = "ID Number: " + newIdNumber;

                std::cout << "Driver's License Number: ";
                std::string newDriverLicenseNum;
                std::getline(std::cin, newDriverLicenseNum);
                lines[i + 5] = "Driver's License Number: " + newDriverLicenseNum;

                std::cout << "Expired Date (MM/YY): ";
                std::string newExpiredDate;
                std::getline(std::cin, newExpiredDate);
                lines[i + 6] = "Expired Date: " + newExpiredDate;

                std::ofstream outputFile(fileName);
                if (outputFile) {
                    for (const std::string& modifiedLine : lines) {
                        outputFile << modifiedLine << std::endl;
                    }

                    outputFile.close();
                    std::cout << "User profile updated successfully." << std::endl;
                } else {
                    std::cout << "Error writing to the file." << std::endl;
                }

                found = true;
                break;
            }
            else{
                std::cout << "\nPlease fill your profile first" << std::endl;
                break;
            }
        }

        if (!found) {
            std::cout << "User profile not found." << std::endl;
        }
    }


    static void rentMotorbike(const std::string& username) {
        // Check if the user has filled in their profile
        std::ifstream userProfileFile("userProfile.txt");
        std::string line;
        bool profileComplete = false;

        while (std::getline(userProfileFile, line)) {
            if (line.find("Username: " + username) != std::string::npos) {
                profileComplete = true;
                break;
            }
        }

        userProfileFile.close();

        if (!profileComplete) {
            std::cout << "Please fill in your profile before renting a motorbike." << std::endl;
            return;
        }

        // Implement the motorbike rental logic here
        // ...
        std::cout << "Motorbike rented successfully!" << std::endl;
    }

};

#endif // USERUI_H
