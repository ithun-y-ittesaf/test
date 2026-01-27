#include "Ticket.h"
#include <sstream>

namespace tickets {
    std::string Ticket::serialize() const {
        return id + "|" + passengerId + "|" + flightId + "|" + issuedDate + "|" + origin + "|" + destination + "|" + flightDate;
    }

    Ticket Ticket::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, passId, flightId, issued, orig, dest, fDate;
        std::getline(ss, id, '|');
        std::getline(ss, passId, '|');
        std::getline(ss, flightId, '|');
        std::getline(ss, issued, '|');
        std::getline(ss, orig, '|');
        std::getline(ss, dest, '|');
        std::getline(ss, fDate, '|');
        return Ticket(id, passId, flightId, issued, orig, dest, fDate);
    }
}
