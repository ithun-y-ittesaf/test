#ifndef USERS_USERCLI_H
#define USERS_USERCLI_H

#include <string>
#include "UserManager.h"
#include "../utils/Types.h"

namespace users {
    /**
     * CLI interface for user authentication and account management.
     */
    class UserCLI {
    private:
        UserManager &manager;
        
        void showWelcome();
        bool runSignup(std::string &outUserId);
        bool runLogin(std::string &outUserId);
        void linkBankAccount(const std::string &userId);
        
    public:
        explicit UserCLI(UserManager &m) : manager(m) {}
        
        // Run the welcome flow (login or signup)
        bool welcomeFlow(std::string &outUserId, utils::Role &outRole);
    };
}

#endif 
