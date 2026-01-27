#include "Flight.h"
#include <sstream>

namespace flights {
    std::string Flight::serialize() const {
        return id + "|" + origin + "|" + destination + "|" + date + "|" +
               std::to_string(capacity) + "|" + std::to_string(seatsBooked);
    }

    Flight Flight::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, orig, dest, date, capStr, bookedStr;
        std::getline(ss, id, '|');
        std::getline(ss, orig, '|');
        std::getline(ss, dest, '|');
        std::getline(ss, date, '|');
        std::getline(ss, capStr, '|');
        std::getline(ss, bookedStr, '|');
        int cap = 0, booked = 0;
        try { cap = std::stoi(capStr); } catch (...) { cap = 0; }
        try { booked = std::stoi(bookedStr); } catch (...) { booked = 0; }
        return Flight(id, orig, dest, date, cap, booked);
    }
}
