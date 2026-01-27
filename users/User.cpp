#include "User.h"
#include <sstream>

namespace users {
    std::string User::serialize() const {
        // Format: id|name|username|password|role
        return id + "|" + name + "|" + username + "|" + password + 
               "|" + std::to_string(static_cast<int>(role));
    }

    User User::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, name, username, password, roleStr;
        
        // Parse pipe-delimited values
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, username, '|');
        std::getline(ss, password, '|');
        std::getline(ss, roleStr, '|');
        
        // Convert role string to enum, default to Passenger on error
        int roleValue = 0;
        try {
            roleValue = std::stoi(roleStr);
        } catch (...) {
            roleValue = 0;
        }
        
        return User(id, name, username, password, static_cast<utils::Role>(roleValue));
    }
}
