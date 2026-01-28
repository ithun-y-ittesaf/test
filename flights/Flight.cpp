#include "Flight.h"
#include <sstream>

using namespace std;

namespace flights {
    string Flight::serialize() const {
        // Format: id|origin|destination|date|capacity|seatsBooked
        return id + "|" + origin + "|" + destination + "|" + date + "|" +
               to_string(capacity) + "|" + to_string(seatsBooked);
    }

    Flight Flight::deserialize(const string &line) {
        stringstream ss(line);
        string id, origin, destination, date, capacityStr, bookedStr;
        
        // Parse pipe-delimited values
        getline(ss, id, '|');
        getline(ss, origin, '|');
        getline(ss, destination, '|');
        getline(ss, date, '|');
        getline(ss, capacityStr, '|');
        getline(ss, bookedStr, '|');
        
        // Convert capacity and booked seats to integers
        int capacity = 0, booked = 0;
        try {
            capacity = stoi(capacityStr);
        } catch (...) {
            capacity = 0;
        }
        try {
            booked = stoi(bookedStr);
        } catch (...) {
            booked = 0;
        }
        
        return Flight(id, origin, destination, date, capacity, booked);
    }
}
