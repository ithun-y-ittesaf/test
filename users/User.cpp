#include "User.h"
#include <sstream>

namespace users {
    std::string User::serialize() const {
        return id + "|" + name + "|" + username + "|" + password + "|" + std::to_string(static_cast<int>(role));
    }

    User User::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, name, username, password, roleStr;
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, username, '|');
        std::getline(ss, password, '|');
        std::getline(ss, roleStr, '|');
        int r = 0;
        try { r = std::stoi(roleStr); } catch (...) { r = 0; }
        return User(id, name, username, password, static_cast<utils::Role>(r));
    }
}
