#include "Ticket.h"
#include <sstream>

namespace tickets {
    std::string Ticket::serialize() const {
        // Format: id|passengerId|flightId|issuedDate|origin|destination|flightDate
        return id + "|" + passengerId + "|" + flightId + "|" + issuedDate + "|" + 
               origin + "|" + destination + "|" + flightDate;
    }

    Ticket Ticket::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, passengerId, flightId, issuedDate, origin, destination, flightDate;
        
        // Parse pipe-delimited values
        std::getline(ss, id, '|');
        std::getline(ss, passengerId, '|');
        std::getline(ss, flightId, '|');
        std::getline(ss, issuedDate, '|');
        std::getline(ss, origin, '|');
        std::getline(ss, destination, '|');
        std::getline(ss, flightDate, '|');
        
        return Ticket(id, passengerId, flightId, issuedDate, origin, destination, flightDate);
    }
}
