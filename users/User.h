#ifndef USERS_USER_H
#define USERS_USER_H

#include <string>
#include "../utils/Types.h"

using namespace std;

namespace users {
    
    class User {
    private:
        utils::ID id;
        string name;
        string username;
        string password;
        utils::Role role;

    public:

        User() : role(utils::Role::Passenger) {}

        User(const utils::ID &userId, const string &fullName, 
             const string &userName, const string &pass, utils::Role userRole)
            : id(userId), name(fullName), username(userName), 
              password(pass), role(userRole) {}

        // Getters
        const utils::ID &getId() const { return id; }
        const string &getName() const { return name; }
        const string &getUsername() const { return username; }
        const string &getPassword() const { return password; }
        utils::Role getRole() const { return role; }

        // Update user role
        void setRole(utils::Role newRole) { role = newRole; }

        // Serialization for storage
        string serialize() const;
        static User deserialize(const string &line);
    };
}

#endif
