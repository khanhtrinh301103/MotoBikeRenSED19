#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Forward declarations
class Member;
class Admin;
class Motorbike;
class MotorbikeCatalog;

class Guest {
public:
    Guest() {}

    void registerAsMember(std::vector<Member>& members);
    void viewMotorbikeDetails(const MotorbikeCatalog& catalog);
    void rentMotorbike(Member& member, MotorbikeCatalog& catalog);
};

class Member {
public:
    Member(const std::string& username, const std::string& password);
    void login(std::vector<Member>& members, const Admin& admin);
    void viewInformation(const MotorbikeCatalog& catalog);
    void listMotorbikeForRent(MotorbikeCatalog& catalog);
    void unlistMotorbikeForRent(MotorbikeCatalog& catalog);
    void searchMotorbikes(const MotorbikeCatalog& catalog);
    void requestToRentMotorbike(Member& member, MotorbikeCatalog& catalog);
    void viewRequests(const MotorbikeCatalog& catalog);
    void acceptRequest(Member& member, MotorbikeCatalog& catalog);
    void rentMotorbike(Member& member, MotorbikeCatalog& catalog);
    void rateMotorbike(Member& member, MotorbikeCatalog& catalog);
    int getCreditPoints() const;
    int getRating() const;
    void listMotorbikeForRent(MotorbikeCatalog& catalog, int motorbikeId);
    void unlistMotorbikeForRent(MotorbikeCatalog& catalog, int motorbikeId);
    void requestToRentMotorbike(Member& member, MotorbikeCatalog& catalog, int motorbikeId);
    void viewRequests(const MotorbikeCatalog& catalog);
    void acceptRequest(Member& member, MotorbikeCatalog& catalog, int motorbikeId, int requestId);
    void rentMotorbike(Member& member, MotorbikeCatalog& catalog, int motorbikeId, int requestId);
    void rateMotorbike(Member& member, MotorbikeCatalog& catalog, int motorbikeId, int rating, const std::string& comments);
    void rateRenter(Member& member, int renterId, int rating, const std::string& comments);

private:
    std::string username;
    std::string password;
    int creditPoints;
    int rating;
    std::vector<int> listedMotorbikes; // Motorbike IDs listed by this member
};

class MotorbikeReservation {
public:
    MotorbikeReservation(int reservationId, const std::string& date, int motorbikeId, int memberId);

    int getReservationId() const;
    int getMotorbikeId() const;
    int getMemberId() const;
    std::string getDate() const;

private:
    int reservationId;
    std::string date;
    int motorbikeId;
    int memberId;
};

class CreditPoint {
public:
    CreditPoint(int memberId, int points);

    int getMemberId() const;
    int getPoints() const;
    void addPoints(int points);

private:
    int memberId;
    int points;
};

class Rating {
public:
    Rating(int motorbikeId, int rating);

    int getMotorbikeId() const;
    int getRating() const;

private:
    int motorbikeId;
    int rating;
};

class Motorbike {
public:
    Motorbike(int motorbikeId, const std::string& make, const std::string& model);

    int getMotorbikeId() const;
    void displayInfo() const;
    int getConsumingPoints() const;
    int getMinRatingScore() const;
    bool isAvailableForMember(const Member& member) const;

private:
    int motorbikeId;
    std::string make;
    std::string model;
    int consumingPoints;
    int minRatingScore;
    std::vector<int> renters; // Member IDs who have rented this motorbike
};

class MotorbikeCatalog {
public:
    void addMotorbike(const Motorbike& motorbike);
    void displayMotorbikes() const;
    Motorbike* findMotorbikeById(int motorbikeId);
    std::vector<Motorbike*> searchMotorbikesForCity(const std::string& city);

private:
    std::vector<Motorbike> motorbikes;
};

class Admin {
public:
    Admin(const std::string& adminUsername, const std::string& adminPassword);

    void login(const std::vector<Member>& members, MotorbikeCatalog& catalog);
    void viewMemberInformation(const std::vector<Member>& members);
    void viewMotorbikeInformation(const MotorbikeCatalog& catalog);
    void saveDataToFile(const std::vector<Member>& members, const MotorbikeCatalog& catalog) const;
    void loadDataFromFile(std::vector<Member>& members, MotorbikeCatalog& catalog);

    std::string getAdminUsername() const;
    std::string getAdminPassword() const;

private:
    std::string adminUsername;
    std::string adminPassword;
};

class CreditRate {
public:
    CreditRate(int memberId, int rate);

    int getMemberId() const;
    int getRate() const;

private:
    int memberId;
    int rate;
};

CreditRate::CreditRate(int memberId, int rate) : memberId(memberId), rate(rate) {}

int CreditRate::getMemberId() const {
    return memberId;
}

int CreditRate::getRate() const {
    return rate;
}


int main() {
    std::vector<Member> members;
    MotorbikeCatalog catalog;
    Admin admin("admin", "adminpassword");

    admin.loadDataFromFile(members, catalog);

    int choice;
    std::string username, password;
    Member* loggedInMember = nullptr;

    do {
        std::cout << "Use the app as:" << std::endl;
        std::cout << "1. Guest" << std::endl;
        std::cout << "2. Member" << std::endl;
        std::cout << "3. Admin" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Guest guest;
                guest.registerAsMember(members);
                guest.viewMotorbikeDetails(catalog);
                guest.rentMotorbike(*loggedInMember, catalog);
                break;
            }
            // Inside the main function, when a member selects option 2:
            case 2: {
                if (loggedInMember == nullptr) {
                    std::cout << "Enter your username: ";
                    std::cin >> username;
                    std::cout << "Enter your password: ";
                    std::cin >> password;

                    // Find and authenticate member list
                    for (Member& member : members) {
                        if (member.login(username, password, admin)) {
                            loggedInMember = &member;
                            break;
                        }
                    }

                    if (loggedInMember != nullptr) {
                        loggedInMember->viewInformation(catalog);
                    } else {
                        std::cout << "Login failed. Invalid username or password." << std::endl;
                    }
                } else {
                    loggedInMember->viewInformation(catalog);
                }
                break;
            }
            // Inside the main function, when an admin selects option 3:
            case 3: {
                std::cout << "Enter admin username: ";
                std::cin >> username;
                std::cout << "Enter admin password: ";
                std::cin >> password;

                if (admin.login(username, password, catalog)) {
                    // Admin is successfully logged in
                    int adminChoice;
                    do {
                        // Display admin menu
                        std::cout << "Admin Menu:" << std::endl;
                        std::cout << "1. View Member Information" << std::endl;
                        std::cout << "2. View Motorbike Information" << std::endl;
                        std::cout << "3. Save Data to File" << std::endl;
                        std::cout << "4. Load Data from File" << std::endl;
                        std::cout << "0. Logout" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                admin.viewMemberInformation(members);
                                break;
                            case 2:
                                admin.viewMotorbikeInformation(catalog);
                                break;
                            case 3:
                                admin.saveDataToFile(members, catalog);
                                break;
                            case 4:
                                admin.loadDataFromFile(members, catalog);
                                break;
                            case 0:
                                // Admin logs out
                                break;
                            default:
                                std::cout << "Invalid choice." << std::endl;
                        }
                    } while (adminChoice != 0);
                } else {
                    std::cout << "Login failed. Invalid admin username or password." << std::endl;
                }
                break;
            }
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
