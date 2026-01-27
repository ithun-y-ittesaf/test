#include "DataStorage.h"
#include <fstream>

namespace storage {
    std::string DataStorage::pathFor(const std::string &name) {
        return std::string("storage/data/") + name;
    }

    std::vector<std::string> DataStorage::readAll(const std::string &file) {
        std::vector<std::string> lines;
        std::ifstream in(pathFor(file));
        if (!in) {
            return lines;
        }
        std::string line;
        while (std::getline(in, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    bool DataStorage::writeAll(const std::string &file, const std::vector<std::string> &lines) {
        std::ofstream out(pathFor(file));
        if (!out) return false;
        for (const auto &l : lines) {
            out << l << "\n";
        }
        return true;
    }

    bool DataStorage::appendLine(const std::string &file, const std::string &line) {
        std::ofstream out(pathFor(file), std::ios::app);
        if (!out) return false;
        out << line << "\n";
        return true;
    }
}
