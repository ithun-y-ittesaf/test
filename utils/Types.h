#ifndef UTILS_TYPES_H
#define UTILS_TYPES_H

#include <string>

using namespace std;

namespace utils {
    // Type alias for unique identifiers
    using ID = string;

    
    enum class Role {
        Passenger = 0,      // Regular passenger user
        Security = 1,       // Security officer
        SeniorSecurity = 2, // Senior security manager
        Admin = 3           // System administrator
    };

    // Basic Result Structure
    struct Result {
        bool ok;            
        string message; 

        static Result Ok(const string &msg = "") { 
            return {true, msg}; 
        }

        static Result Err(const string &msg) { 
            return {false, msg}; 
        }
    };
}

#endif
