#include "Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;

namespace logging {
    
    // Helper function to get current timestamp as String
    static string getCurrentTimestamp() {
        using namespace chrono;
        
        auto now = system_clock::to_time_t(system_clock::now());
        tm timeinfo = *localtime(&now);
        
        char buffer[32];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        
        return string(buffer);
    }

    void Logger::logCritical(const string &action, const string &details) {
        ofstream logFile("storage/data/logs.txt", ios::app);
        
        if (!logFile) {
            // Gracefully handle if log file cannot be opened
            return;
        }
        
        logFile << getCurrentTimestamp() << " | " << action << " | " << details << "\n";
    }
}
