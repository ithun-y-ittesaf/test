#include "UserCLI.h"
#include <iostream>

namespace users {
    void UserCLI::showWelcome() {
        std::cout << "\n==================================================\n";
        std::cout << "              Welcome to airCLI ✈\n";
        std::cout << "              Flight Booking System\n";
        std::cout << "==================================================\n\n";
        std::cout << "1. Login\n";
        std::cout << "2. Create New Account\n";
        std::cout << "3. Exit\n\n";
        std::cout << "What would you like to do? > ";
    }

    bool UserCLI::runSignup(std::string &outUserId) {
        std::cout << "\n--- Create Your Account ---\n";
        
        std::cout << "\nFull Name     : ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);
        
        std::cout << "Username      : ";
        std::string username;
        std::getline(std::cin, username);
        
        if (manager.findByUsername(username)) {
            std::cout << "\nSorry, that username is already taken. Please try another.\n";
            return false;
        }
        
        std::cout << "Password      : ";
        std::string password;
        std::getline(std::cin, password);
        
        std::cout << "Confirm       : ";
        std::string confirmPassword;
        std::getline(std::cin, confirmPassword);
        
        if (password != confirmPassword) {
            std::cout << "\nThe passwords don't match. Please try again.\n";
            return false;
        }
        
        outUserId = manager.createUser(name, username, password);
        
        std::cout << "\n✓ Account created successfully!\n";
        std::cout << "Your user ID: " << outUserId << "\n";
        std::cout << "You can now log in with your username and password.\n";
        
        return true;
    }

    bool UserCLI::runLogin(std::string &outUserId) {
        std::cout << "\n--- Login ---\n";
        
        std::cout << "\nUsername : ";
        std::string username;
        std::cin.ignore();
        std::getline(std::cin, username);
        
        std::cout << "Password : ";
        std::string password;
        std::getline(std::cin, password);
        
        if (!manager.authenticate(username, password, outUserId)) {
            std::cout << "\nIncorrect username or password. Please try again.\n";
            return false;
        }
        
        const User* user = manager.get(outUserId);
        std::cout << "\n✓ Login successful!\n";
        std::cout << "Welcome back, " << user->getName() << "!\n";
        
        return true;
    }

    void UserCLI::linkBankAccount(const std::string &userId) {
        // Future feature: link external bank account
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
                std::cout << "\nThanks for visiting airCLI. Goodbye!\n";
                return false;
            } else {
                std::cout << "\nPlease enter 1, 2, or 3.\n";
            }
        }
    }
}
