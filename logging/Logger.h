#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <string>

namespace logging {
    class Logger {
    public:
        static void logCritical(const std::string &action, const std::string &details);
    };
}

#endif // LOGGING_LOGGER_H
