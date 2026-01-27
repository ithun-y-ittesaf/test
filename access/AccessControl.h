#ifndef ACCESS_ACCESSCONTROL_H
#define ACCESS_ACCESSCONTROL_H

#include <string>
#include <initializer_list>
#include "../utils/Types.h"

namespace access {
    /**
     * Handles role-based access control throughout the system.
     * Determines what operations users with different roles can perform.
     */
    class AccessControl {
    public:
        /**
         * Check if a user has the required role for an operation.
         * @return Error result if user doesn't have required role
         */
        static utils::Result requireRole(utils::Role currentRole, utils::Role requiredRole);

        /**
         * Check if a user's role matches any of the given roles.
         * @return true if current role is in the provided list
         */
        static bool anyOf(utils::Role currentRole, const std::initializer_list<utils::Role> &allowedRoles);

        /**
         * Convert a role enum to a human-readable string.
         */
        static std::string roleToString(utils::Role role);
    };
}

#endif
