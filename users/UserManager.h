#ifndef USERS_USERMANAGER_H
#define USERS_USERMANAGER_H

#include <map>
#include <vector>
#include "User.h"

namespace users {
    class UserManager {
    private:
        std::map<utils::ID, User> usersById;
        std::map<std::string, utils::ID> usernameToId;
    public:
        bool load();
        bool save() const;
        utils::ID createUser(const std::string &name, const std::string &username, const std::string &password);
        const User* get(const utils::ID &id) const;
        const User* findByUsername(const std::string &username) const;
        bool authenticate(const std::string &username, const std::string &password, utils::ID &outId) const;
        std::vector<User> all() const;
        bool updateRole(const utils::ID &id, utils::Role newRole);
    };
}

#endif 
