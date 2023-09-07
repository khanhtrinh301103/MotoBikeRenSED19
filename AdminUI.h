// AdminUI.h

#ifndef ADMINUI_H
#define ADMINUI_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class AdminUI {
public:
    static void showMenu() {
        int choice;

        while (true) {
            std::cout << "\nAdmin Menu:" << std::endl;
            std::cout << "1. View all user accounts" << std::endl;
            std::cout << "2. View Product Details" << std::endl; // New option
            std::cout << "3. Edit Product Details" << std::endl; // New option
            std::cout << "4. Log out" << std::endl;
            std::cout << "Enter your choice (1/2/3/4): ";

            std::cin >> choice;

            switch (choice) {
                case 1:
                    viewAllUserAccounts();
                    break;
                case 2:
                    viewProductDetails(); // New function to view product details
                    break;
                case 3:
                    editProductDetails(); // New function to edit product details
                    break;
                case 4:
                    std::cout << "Exiting admin account. Goodbye!" << std::endl;
                    return;
                default:
                    std::cout << "Invalid choice. Please enter a valid option (1/2/3/4)." << std::endl;
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
            std::cerr << "Failed to open user account file." << std::endl;
        }
    }

    static void viewProductDetails() {
        std::ifstream productFile("ProductDetail.txt");
        std::string line;

        if (productFile.is_open()) {
            std::cout << "\nProduct Detail:" << std::endl;
            while (std::getline(productFile, line)) {
                std::cout << line << std::endl;
            }

            productFile.close();
        } else {
            std::cerr << "Failed to open product details file." << std::endl;
        }
    }

    static void editProductDetails() {
        int motorbikeIDToEdit;
        std::cout << "Enter the MotorbikeID to edit: ";
        std::cin >> motorbikeIDToEdit;

        // Open the input file stream in read mode and output file stream in write mode
        std::fstream file("ProductDetail.txt", std::ios::in | std::ios::out);

        if (!file.is_open()) {
            std::cerr << "Failed to open the file for editing." << std::endl;
            return;
        }

        bool motorbikeFound = false;
        std::string line;
        std::vector<std::string> updatedLines; // To store the updated lines

        // Search for the specified MotorbikeID in the file
        while (std::getline(file, line)) {
            // Check if the line contains the specified MotorbikeID
            if (line.find("MotorbikeID: " + std::to_string(motorbikeIDToEdit)) != std::string::npos) {
                motorbikeFound = true;

                // Update the existing line with new values
                updatedLines.push_back(line); // MotorbikeID line

                // Ask the admin to enter new values for each field except MotorbikeID and update them
                std::string model, color, transmission, description, expectedRentedRate;
                int engineSize, yearMade, ownerID, rateID;

                std::cout << "Enter new Model: ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, model);
                std::cout << "Enter new Color: ";
                std::getline(std::cin, color);
                std::cout << "Enter new Engine Size: ";
                std::cin >> engineSize;
                std::cout << "Enter new Transmission Mode: ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, transmission);
                std::cout << "Enter new Year Made: ";
                std::cin >> yearMade;
                std::cout << "Enter new Description: ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, description);
                std::cout << "Enter new Owner ID: ";
                std::cin >> ownerID;
                std::cout << "Enter new Expected Rented Rate: ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, expectedRentedRate);
                std::cout << "Enter new Rate ID: ";
                std::cin >> rateID;

                updatedLines.push_back("Model: " + model); // Add updated Model line
                updatedLines.push_back("Color: " + color);
                updatedLines.push_back("Engine Size: " + std::to_string(engineSize));
                updatedLines.push_back("Transmission Mode: " + transmission);
                updatedLines.push_back("Year Made: " + std::to_string(yearMade));
                updatedLines.push_back("Description: " + description);
                updatedLines.push_back("Owner ID: " + std::to_string(ownerID));
                updatedLines.push_back("Expected Rented Rate: " + expectedRentedRate);
                updatedLines.push_back("Rate ID: " + std::to_string(rateID));
            } else {
                updatedLines.push_back(line); // Keep other lines as they are
            }
        }

        // Close the file stream
        file.close();

        // Open the file again in write mode to overwrite its content
        file.open("ProductDetail.txt", std::ios::out | std::ios::trunc);

        if (!file.is_open()) {
            std::cerr << "Failed to open the file for writing." << std::endl;
            return;
        }

        // Write the updated lines back to the file
        for (const std::string& updatedLine : updatedLines) {
            file << updatedLine << std::endl;
        }

        // Close the file stream
        file.close();

        if (motorbikeFound) {
            std::cout << "Product details updated successfully." << std::endl;
        } else {
            std::cout << "Motorbike with MotorbikeID " << motorbikeIDToEdit << " not found." << std::endl;
        }
    }


};

#endif // ADMINUI_H
