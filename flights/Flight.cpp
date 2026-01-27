#include "Flight.h"
#include <sstream>

namespace flights {
    std::string Flight::serialize() const {
        // Format: id|origin|destination|date|capacity|seatsBooked
        return id + "|" + origin + "|" + destination + "|" + date + "|" +
               std::to_string(capacity) + "|" + std::to_string(seatsBooked);
    }

    Flight Flight::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, origin, destination, date, capacityStr, bookedStr;
        
        // Parse pipe-delimited values
        std::getline(ss, id, '|');
        std::getline(ss, origin, '|');
        std::getline(ss, destination, '|');
        std::getline(ss, date, '|');
        std::getline(ss, capacityStr, '|');
        std::getline(ss, bookedStr, '|');
        
        // Convert capacity and booked seats to integers
        int capacity = 0, booked = 0;
        try {
            capacity = std::stoi(capacityStr);
        } catch (...) {
            capacity = 0;
        }
        try {
            booked = std::stoi(bookedStr);
        } catch (...) {
            booked = 0;
        }
        
        return Flight(id, origin, destination, date, capacity, booked);
    }
}
