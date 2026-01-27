#ifndef STORAGE_DATASTORAGE_H
#define STORAGE_DATASTORAGE_H

#include <string>
#include <vector>

namespace storage {
    /**
     * Handles all persistent data storage operations.
     * Manages reading and writing data files to disk.
     */
    class DataStorage {
    public:
        /**
         * Read all lines from a data file.
         */
        static std::vector<std::string> readAll(const std::string &filename);

        /**
         * Write all lines to a data file (overwrites existing content).
         */
        static bool writeAll(const std::string &filename, const std::vector<std::string> &lines);

        /**
         * Append a line to a data file.
         */
        static bool appendLine(const std::string &filename, const std::string &line);

        /**
         * Get the full path for a data file.
         */
        static std::string pathFor(const std::string &filename);
    };
}

#endif
