// RegisterAccount.h

#ifndef REGISTERACCOUNT_H
#define REGISTERACCOUNT_H

#include <string>
#include <fstream>

class RegisterAccount {
public:
    static bool registerUser(const std::string& username, const std::string& password, const std::string& confirmPassword) {
        if (password == confirmPassword) {
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
};

#endif // REGISTERACCOUNT_H
