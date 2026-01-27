#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <string>

namespace logging {
    /**
     * Handles system logging for critical events and activities.
     * Records important transactions and system actions.
     */
    class Logger {
    public:
        /**
         * Log a critical event to the system log.
         * @param action The type of action being logged
         * @param details Additional details about the action
         */
        static void logCritical(const std::string &action, const std::string &details);
    };
}

#endif
