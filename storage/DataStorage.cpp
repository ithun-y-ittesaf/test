#include "DataStorage.h"
#include <fstream>

using namespace std;

namespace storage {
    string DataStorage::pathFor(const string &filename) {
        return string("storage/data/") + filename;
    }

    vector<string> DataStorage::readAll(const string &filename) {
        vector<string> lines;
        ifstream inputFile(pathFor(filename));
        
        if (!inputFile) {
            // File doesn't exist or can't be opened
            return lines;
        }
        
        string line;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        
        return lines;
    }

    bool DataStorage::writeAll(const string &filename, const vector<string> &lines) {
        ofstream outputFile(pathFor(filename));
        
        if (!outputFile) {
            return false;
        }
        
        for (const auto &line : lines) {
            outputFile << line << "\n";
        }
        
        return true;
    }

    bool DataStorage::appendLine(const string &filename, const string &line) {
        ofstream outputFile(pathFor(filename), ios::app);
        
        if (!outputFile) {
            return false;
        }
        
        outputFile << line << "\n";
        return true;
    }
}
