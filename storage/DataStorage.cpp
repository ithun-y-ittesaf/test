#include "DataStorage.h"
#include <fstream>

namespace storage {
    std::string DataStorage::pathFor(const std::string &filename) {
        return std::string("storage/data/") + filename;
    }

    std::vector<std::string> DataStorage::readAll(const std::string &filename) {
        std::vector<std::string> lines;
        std::ifstream inputFile(pathFor(filename));
        
        if (!inputFile) {
            // File doesn't exist or can't be opened
            return lines;
        }
        
        std::string line;
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }
        
        return lines;
    }

    bool DataStorage::writeAll(const std::string &filename, const std::vector<std::string> &lines) {
        std::ofstream outputFile(pathFor(filename));
        
        if (!outputFile) {
            return false;
        }
        
        for (const auto &line : lines) {
            outputFile << line << "\n";
        }
        
        return true;
    }

    bool DataStorage::appendLine(const std::string &filename, const std::string &line) {
        std::ofstream outputFile(pathFor(filename), std::ios::app);
        
        if (!outputFile) {
            return false;
        }
        
        outputFile << line << "\n";
        return true;
    }
}
