#include "AccessControl.h"

namespace access {
    utils::Result AccessControl::requireRole(utils::Role current, utils::Role required) {
        if (current == required) return utils::Result::Ok();
        return utils::Result::Err("Access denied: requires role " + roleToString(required));
    }

    bool AccessControl::anyOf(utils::Role current, const std::initializer_list<utils::Role> &roles) {
        for (auto r : roles) { if (current == r) return true; }
        return false;
    }

    std::string AccessControl::roleToString(utils::Role r) {
        switch (r) {
            case utils::Role::Passenger: return "Passenger";
            case utils::Role::Security: return "Security";
            case utils::Role::SeniorSecurity: return "SeniorSecurity";
            case utils::Role::Admin: return "Admin";
        }
        return "Unknown";
    }
}
