#ifndef ACCESS_ACCESSCONTROL_H
#define ACCESS_ACCESSCONTROL_H

#include <string>
#include <initializer_list>
#include "../utils/Types.h"

namespace access {
    
    class AccessControl {
    public:
        
        static utils::Result requireRole(utils::Role currentRole, utils::Role requiredRole);

        static bool anyOf(utils::Role currentRole, const std::initializer_list<utils::Role> &allowedRoles);

        static std::string roleToString(utils::Role role);
    };
}

#endif
