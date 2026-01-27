#ifndef UTILS_TYPES_H
#define UTILS_TYPES_H

#include <string>

namespace utils {
    // Type alias for unique identifiers
    using ID = std::string;

    /**
     * Represents different user roles in the system with different permissions.
     */
    enum class Role {
        Passenger = 0,      // Regular passenger user
        Security = 1,       // Security officer
        SeniorSecurity = 2, // Senior security manager
        Admin = 3           // System administrator
    };

    /**
     * Represents the result of an operation (success or failure with message).
     */
    struct Result {
        bool ok;            // true if successful, false if failed
        std::string message; // description of the result

        // Factory method for successful results
        static Result Ok(const std::string &msg = "") { 
            return {true, msg}; 
        }

        // Factory method for error results
        static Result Err(const std::string &msg) { 
            return {false, msg}; 
        }
    };
}

#endif
