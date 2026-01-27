#include "Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>

namespace logging {
    // Helper function to get current timestamp as human-readable string
    static std::string getCurrentTimestamp() {
        using namespace std::chrono;
        
        auto now = system_clock::to_time_t(system_clock::now());
        std::tm timeinfo = *std::localtime(&now);
        
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        
        return std::string(buffer);
    }

    void Logger::logCritical(const std::string &action, const std::string &details) {
        std::ofstream logFile("storage/data/logs.txt", std::ios::app);
        
        if (!logFile) {
            // Gracefully handle if log file cannot be opened
            return;
        }
        
        logFile << getCurrentTimestamp() << " | " << action << " | " << details << "\n";
    }
}
