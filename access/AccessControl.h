#ifndef ACCESS_ACCESSCONTROL_H
#define ACCESS_ACCESSCONTROL_H

#include <string>
#include <initializer_list>
#include "../utils/Types.h"

namespace access {
    class AccessControl {
    public:
        static utils::Result requireRole(utils::Role current, utils::Role required);
        static bool anyOf(utils::Role current, const std::initializer_list<utils::Role> &roles);
        static std::string roleToString(utils::Role r);
    };
}

#endif 
