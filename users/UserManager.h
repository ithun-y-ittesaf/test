#ifndef USERS_USERMANAGER_H
#define USERS_USERMANAGER_H

#include <map>
#include <vector>
#include "User.h"

namespace users {
    /**
     * Manages all users in the system.
     * Handles loading, saving, and querying user data.
     */
    class UserManager {
    private:
        std::map<utils::ID, User> usersById;
        std::map<std::string, utils::ID> usernameToId;

    public:
        // Load users from persistent storage
        bool load();
        
        // Save all users to persistent storage
        bool save() const;
        
        // Create a new user with given credentials
        utils::ID createUser(const std::string &name, const std::string &username, 
                           const std::string &password);
        
        // Get a user by their ID
        const User* get(const utils::ID &id) const;
        
        // Find a user by their username
        const User* findByUsername(const std::string &username) const;
        
        // Verify credentials and return user ID if valid
        bool authenticate(const std::string &username, const std::string &password, 
                         utils::ID &outId) const;
        
        // Get all users
        std::vector<User> all() const;
        
        // Update a user's role
        bool updateRole(const utils::ID &id, utils::Role newRole);
    };
}

#endif
