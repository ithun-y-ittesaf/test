#ifndef TICKETS_TICKET_H
#define TICKETS_TICKET_H

#include <string>
#include "../utils/Types.h"

namespace tickets {
    /**
     * Represents a flight ticket purchased by a passenger.
     * Contains passenger, flight, and temporal information.
     */
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
        // Default constructor
        Ticket() {}

        // Full constructor with all ticket details
        Ticket(const utils::ID &ticketId, const utils::ID &passId, 
               const utils::ID &flightId, const std::string &issued,
               const std::string &origin, const std::string &destination, 
               const std::string &flightDate)
            : id(ticketId), passengerId(passId), flightId(flightId), 
              issuedDate(issued), origin(origin), destination(destination), 
              flightDate(flightDate) {}

        // Getters for all ticket properties
        const utils::ID &getId() const { return id; }
        const utils::ID &getPassengerId() const { return passengerId; }
        const utils::ID &getFlightId() const { return flightId; }
        const std::string &getIssuedDate() const { return issuedDate; }
        const std::string &getOrigin() const { return origin; }
        const std::string &getDestination() const { return destination; }
        const std::string &getFlightDate() const { return flightDate; }

        // Serialization for storage
        std::string serialize() const;
        static Ticket deserialize(const std::string &line);
    };
}

#endif
