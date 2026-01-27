#include "UserManager.h"
#include "../storage/DataStorage.h"
#include <chrono>

namespace users {
    bool UserManager::load() {
        auto lines = storage::DataStorage::readAll("users.txt");
        usersById.clear();
        usernameToId.clear();
        
        // Deserialize all users from storage
        for (const auto &line : lines) {
            User user = User::deserialize(line);
            usersById[user.getId()] = user;
            usernameToId[user.getUsername()] = user.getId();
        }
        
        return true;
    }

    bool UserManager::save() const {
        std::vector<std::string> lines;
        
        // Serialize all users to file
        for (const auto &pair : usersById) {
            lines.push_back(pair.second.serialize());
        }
        
        return storage::DataStorage::writeAll("users.txt", lines);
    }

    utils::ID UserManager::createUser(const std::string &name, const std::string &username, 
                                     const std::string &password) {
        using namespace std::chrono;
        
        // Generate unique ID using current timestamp
        auto timestamp = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID userId = "U" + std::to_string(timestamp);
        
        // Ensure ID is unique
        while (usersById.find(userId) != usersById.end()) {
            ++timestamp;
            userId = "U" + std::to_string(timestamp);
        }
        
        // Create new user (passengers by default)
        User newUser(userId, name, username, password, utils::Role::Passenger);
        usersById[userId] = newUser;
        usernameToId[username] = userId;
        
        // Persist to storage
        storage::DataStorage::appendLine("users.txt", newUser.serialize());
        
        return userId;
    }

    const User* UserManager::get(const utils::ID &id) const {
        auto it = usersById.find(id);
        if (it == usersById.end()) {
            return nullptr;
        }
        return &it->second;
    }

    const User* UserManager::findByUsername(const std::string &username) const {
        auto it = usernameToId.find(username);
        if (it == usernameToId.end()) {
            return nullptr;
        }
        return get(it->second);
    }

    bool UserManager::authenticate(const std::string &username, const std::string &password, 
                                   utils::ID &outId) const {
        const User* user = findByUsername(username);
        
        // User must exist and password must match
        if (!user) {
            return false;
        }
        if (user->getPassword() != password) {
            return false;
        }
        
        outId = user->getId();
        return true;
    }

    std::vector<User> UserManager::all() const {
        std::vector<User> users;
        users.reserve(usersById.size());
        
        for (const auto &pair : usersById) {
            users.push_back(pair.second);
        }
        
        return users;
    }

    bool UserManager::updateRole(const utils::ID &id, utils::Role newRole) {
        auto it = usersById.find(id);
        if (it == usersById.end()) {
            return false;
        }
        
        it->second.setRole(newRole);
        return save();
    }
}
