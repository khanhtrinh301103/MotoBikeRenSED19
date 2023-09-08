// RegisterAccount.h

#ifndef REGISTERACCOUNT_H
#define REGISTERACCOUNT_H

#include <string>
#include <fstream>

class RegisterAccount {
public:
    static bool registerUser(const std::string& username, const std::string& password, const std::string& confirmPassword) {
        if (password == confirmPassword) {
            // Check if the username already exists in userAccount.txt
            if (isUsernameInFile(username, "userAccount.txt")) {
                std::cout << "\nThis username already exists. Please choose a different username." << std::endl;
                return false; // Registration failed
            }
            
            // Check if the username already exists in adminAccount.txt
            if (isUsernameInFile(username, "adminAccount.txt")) {
                std::cout << "\nThis username is only for admin. Please choose another username." << std::endl;
                return false; // Registration failed
            }

            std::ofstream userFile("userAccount.txt", std::ios::app); // Open the file in append mode

            if (userFile.is_open()) {
                // Write the new username and password to the file
                userFile << username << " " << password << "\n";
                userFile.close();
                return true; // Registration successful
            }
        }

        return false; // Registration failed
    }

private:
    static bool isUsernameInFile(const std::string& username, const std::string& filename) {
        std::ifstream file(filename);
        std::string existingUsername;

        if (file.is_open()) {
            while (file >> existingUsername) {
                if (username == existingUsername) {
                    file.close();
                    return true; // Username exists in the file
                }
            }
            file.close();
        }

        return false; // Username does not exist in the file
    }
};

#endif // REGISTERACCOUNT_H
