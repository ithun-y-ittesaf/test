#ifndef TICKETS_TICKET_H
#define TICKETS_TICKET_H

#include <string>
#include "../utils/Types.h"

namespace tickets {
    class Ticket {
    private:
        utils::ID id;
        utils::ID passengerId;
        utils::ID flightId;
        std::string issuedDate;
        std::string origin;
        std::string destination;
        std::string flightDate;
    public:
        Ticket() {}
        Ticket(const utils::ID &id, const utils::ID &passId, const utils::ID &flightId, const std::string &issued,
               const std::string &orig, const std::string &dest, const std::string &flightDate)
            : id(id), passengerId(passId), flightId(flightId), issuedDate(issued), origin(orig), destination(dest), flightDate(flightDate) {}

        const utils::ID &getId() const { return id; }
        const utils::ID &getPassengerId() const { return passengerId; }
        const utils::ID &getFlightId() const { return flightId; }
        const std::string &getIssuedDate() const { return issuedDate; }
        const std::string &getOrigin() const { return origin; }
        const std::string &getDestination() const { return destination; }
        const std::string &getFlightDate() const { return flightDate; }

        std::string serialize() const;
        static Ticket deserialize(const std::string &line);
    };
}

#endif // TICKETS_TICKET_H
