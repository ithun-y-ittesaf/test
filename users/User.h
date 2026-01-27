#ifndef USERS_USER_H
#define USERS_USER_H

#include <string>
#include "../utils/Types.h"

namespace users {
    /**
     * Represents a user in the airCLI system.
     * Stores their profile info and role permissions.
     */
    class User {
    private:
        utils::ID id;
        std::string name;
        std::string username;
        std::string password;
        utils::Role role;

    public:
        // Default constructor for empty user
        User() : role(utils::Role::Passenger) {}

        // Full constructor with all user details
        User(const utils::ID &userId, const std::string &fullName, 
             const std::string &userName, const std::string &pass, utils::Role userRole)
            : id(userId), name(fullName), username(userName), 
              password(pass), role(userRole) {}

        // Getters for all user properties
        const utils::ID &getId() const { return id; }
        const std::string &getName() const { return name; }
        const std::string &getUsername() const { return username; }
        const std::string &getPassword() const { return password; }
        utils::Role getRole() const { return role; }

        // Update user role
        void setRole(utils::Role newRole) { role = newRole; }

        // Serialization for storage
        std::string serialize() const;
        static User deserialize(const std::string &line);
    };
}

#endif
