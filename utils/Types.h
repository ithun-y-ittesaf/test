#ifndef UTILS_TYPES_H
#define UTILS_TYPES_H

#include <string>

namespace utils {
    using ID = std::string;

    enum class Role {
        Passenger = 0,
        Security = 1,
        SeniorSecurity = 2,
        Admin = 3
    };

    struct Result {
        bool ok;
        std::string message;

        static Result Ok(const std::string &msg = "") { return {true, msg}; }
        static Result Err(const std::string &msg) { return {false, msg}; }
    };
}

#endif // UTILS_TYPES_H
