#include "AccessControl.h"

namespace access {
    utils::Result AccessControl::requireRole(utils::Role currentRole, utils::Role requiredRole) {
        if (currentRole == requiredRole) {
            return utils::Result::Ok();
        }
        return utils::Result::Err("Access denied: requires " + roleToString(requiredRole) + " role");
    }

    bool AccessControl::anyOf(utils::Role currentRole, const std::initializer_list<utils::Role> &allowedRoles) {
        for (auto role : allowedRoles) {
            if (currentRole == role) {
                return true;
            }
        }
        return false;
    }

    std::string AccessControl::roleToString(utils::Role role) {
        switch (role) {
            case utils::Role::Passenger:
                return "Passenger";
            case utils::Role::Security:
                return "Security";
            case utils::Role::SeniorSecurity:
                return "Senior Security";
            case utils::Role::Admin:
                return "Administrator";
            default:
                return "Unknown";
        }
    }
}
