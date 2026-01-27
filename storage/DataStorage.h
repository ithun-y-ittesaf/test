#ifndef STORAGE_DATASTORAGE_H
#define STORAGE_DATASTORAGE_H

#include <string>
#include <vector>

namespace storage {
    class DataStorage {
    public:
        static std::vector<std::string> readAll(const std::string &file);
        static bool writeAll(const std::string &file, const std::vector<std::string> &lines);
        static bool appendLine(const std::string &file, const std::string &line);
        static std::string pathFor(const std::string &name);
    };
}

#endif // STORAGE_DATASTORAGE_H
