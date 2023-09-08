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
        std::streampos linePos;
        std::streampos nextLinePos;

        // Search for the specified MotorbikeID in the file
        while (std::getline(file, line)) {
            linePos = file.tellg(); // Store the position of the line

            // Check if the line contains the specified MotorbikeID
            if (line.find("MotorbikeID: " + std::to_string(motorbikeIDToEdit)) != std::string::npos) {
                motorbikeFound = true;

                // Ask the admin to enter new values for each field except MotorbikeID and update them
                std::string model, color, transmission, description, expectedRentedRate;
                int engineSize, yearMade, ownerID, rateID;

                // Skip the MotorbikeID line
                std::getline(file, line);

                // Read and update the rest of the fields
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

                // Move to the next line
                std::getline(file, line);
                nextLinePos = file.tellg();

                // Go back to the beginning of the line and replace it with the updated content
                file.seekp(linePos);
                file << "Model: " << model << std::endl;
                file << "Color: " << color << std::endl;
                file << "Engine Size: " << engineSize << std::endl;
                file << "Transmission Mode: " << transmission << std::endl;
                file << "Year Made: " << yearMade << std::endl;
                file << "Description: " << description << std::endl;
                file << "Owner ID: " << ownerID << std::endl;
                file << "Expected Rented Rate: " << expectedRentedRate << std::endl;
                file << "Rate ID: " << rateID << std::endl;

                // Set the file position to the end of the updated content
                file.seekp(nextLinePos);

                break; // Stop searching since the MotorbikeID was found and updated
            }
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
