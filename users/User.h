#ifndef USERS_USER_H
#define USERS_USER_H

#include <string>
#include "../utils/Types.h"

namespace users {
    class User {
    private:
        utils::ID id;
        std::string name;
        std::string username;
        std::string password;
        utils::Role role;
    public:
        User() : role(utils::Role::Passenger) {}
        User(const utils::ID &id, const std::string &name, const std::string &username, 
             const std::string &password, utils::Role role)
            : id(id), name(name), username(username), password(password), role(role) {}

        const utils::ID &getId() const { return id; }
        const std::string &getName() const { return name; }
        const std::string &getUsername() const { return username; }
        const std::string &getPassword() const { return password; }
        utils::Role getRole() const { return role; }
        void setRole(utils::Role r) { role = r; }

        std::string serialize() const;
        static User deserialize(const std::string &line);
    };
}

#endif 
