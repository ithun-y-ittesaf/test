#include "UserCLI.h"
#include <iostream>

namespace users {
    void UserCLI::showWelcome() {
        std::cout << "\n==================================================\n";
        std::cout << "              airCLI ✈\n";
        std::cout << "          Lite Booking Demo\n";
        std::cout << "==================================================\n\n";
        std::cout << "1. Login\n";
        std::cout << "2. Sign Up\n";
        std::cout << "3. Exit\n\n";
        std::cout << "Select an option > ";
    }

    bool UserCLI::runSignup(std::string &outUserId) {
        std::cout << "\n========== Passenger Registration ==========" << "\n";
        std::cout << "Enter Full Name        : ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);
        
        std::cout << "Choose Username        : ";
        std::string username;
        std::getline(std::cin, username);
        
        if (manager.findByUsername(username)) {
            std::cout << "\n❌ Username already taken. Try another.\n";
            return false;
        }
        
        std::cout << "Choose Password        : ";
        std::string password;
        std::getline(std::cin, password);
        
        std::cout << "Confirm Password       : ";
        std::string confirm;
        std::getline(std::cin, confirm);
        
        if (password != confirm) {
            std::cout << "\n❌ Passwords do not match.\n";
            return false;
        }
        
        outUserId = manager.createUser(name, username, password);
        
        std::cout << "\n✅ Account created successfully.\n";
        std::cout << "Your ID: " << outUserId << "\n";
        
        return true;
    }

    bool UserCLI::runLogin(std::string &outUserId) {
        std::cout << "\n============== Login ==============" << "\n";
        std::cout << "Username : ";
        std::string username;
        std::cin.ignore();
        std::getline(std::cin, username);
        
        std::cout << "Password : ";
        std::string password;
        std::getline(std::cin, password);
        
        if (!manager.authenticate(username, password, outUserId)) {
            std::cout << "\n❌ Authentication failed. Try again.\n";
            return false;
        }
        
        const User* user = manager.get(outUserId);
        std::cout << "\n✅ Login successful.\n";
        std::cout << "Welcome, " << user->getName() << "!\n";
        return true;
    }

    void UserCLI::linkBankAccount(const std::string &userId) {
        (void)userId;
    }

    bool UserCLI::welcomeFlow(std::string &outUserId, utils::Role &outRole) {
        manager.load();
        
        while (true) {
            showWelcome();
            int choice = 0;
            std::cin >> choice;
            
            if (choice == 1) {
                if (runLogin(outUserId)) {
                    const User* user = manager.get(outUserId);
                    outRole = user->getRole();
                    return true;
                }
            } else if (choice == 2) {
                if (runSignup(outUserId)) {
                    const User* user = manager.get(outUserId);
                    outRole = user->getRole();
                    return true;
                }
            } else if (choice == 3) {
                std::cout << "\nGoodbye.\n";
                return false;
            } else {
                std::cout << "\nInvalid option. Please choose 1–3.\n";
            }
        }
    }
}
