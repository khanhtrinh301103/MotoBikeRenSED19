// searchEngine.h

#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include <iostream>

class SearchEngine {
public:
        static void searchMotorbikesByCity() {
        // Search for motorbikes in the specified city
        std::cout << "\nEnter the city to search for motorbikes: ";
        std::string searchCity;
        std::cin.ignore();
        std::getline(std::cin, searchCity);

        std::ifstream productDetailFile("ProductDetail.txt");
        bool foundMotorbikeInCity = false;
        std::vector<std::string> motorbikeDetails;

        std::string line;

        while (std::getline(productDetailFile, line)) {
            if (line.find("city: " + searchCity) != std::string::npos) {
                foundMotorbikeInCity = true;
                break; // Stop after finding the city line
            }
            motorbikeDetails.push_back(line);
            if (motorbikeDetails.size() > 11) {
                motorbikeDetails.erase(motorbikeDetails.begin()); // Limit to 11 lines before the city line
            }
        }

        productDetailFile.close();

        if (!foundMotorbikeInCity) {
            std::cout << "No available motorbikes found in " << searchCity << " City." << std::endl;
        } else {
            std::cout << "\nThe motorbikes available in " << searchCity << " city: \n" << std::endl;

            // Display motorbike details and the preceding lines
            for (const std::string& detail : motorbikeDetails) {
                std::cout << detail << std::endl;
            }
        }
    }
};

#endif // SEARCH_ENGINE_H
