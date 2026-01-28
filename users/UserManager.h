#ifndef USERS_USERMANAGER_H
#define USERS_USERMANAGER_H

#include <map>
#include <vector>
#include "User.h"

using namespace std;

namespace users {
    
    class UserManager {
    private:
        map<utils::ID, User> usersById;
        map<string, utils::ID> usernameToId;

    public:

        bool load();
        
        bool save() const;
        
        utils::ID createUser(const string &name, const string &username, 
                           const string &password);
        
        const User* get(const utils::ID &id) const;
        
        const User* findByUsername(const string &username) const;
        
        bool authenticate(const string &username, const string &password, 
                         utils::ID &outId) const;
        
        vector<User> all() const;
        
        bool updateRole(const utils::ID &id, utils::Role newRole);
    };
}

#endif
