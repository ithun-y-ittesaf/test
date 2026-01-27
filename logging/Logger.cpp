#include "Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>

namespace logging {
    static std::string nowTS() {
        using namespace std::chrono;
        auto t = system_clock::to_time_t(system_clock::now());
        std::tm tm = *std::localtime(&t);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
        return std::string(buf);
    }

    void Logger::logCritical(const std::string &action, const std::string &details) {
        std::ofstream out("storage/data/logs.txt", std::ios::app);
        if (!out) {
            return; // graceful: skip if cannot open
        }
        out << nowTS() << " | " << action << " | " << details << "\n";
    }
}
