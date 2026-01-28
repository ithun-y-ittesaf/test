#ifndef TICKETS_TICKET_H
#define TICKETS_TICKET_H

#include <string>
#include "../utils/Types.h"

using namespace std;

namespace tickets {
    
    class Ticket {
    private:
        utils::ID id;
        utils::ID passengerId;
        utils::ID flightId;
        string issuedDate;
        string origin;
        string destination;
        string flightDate;

    public:

        Ticket() {}

        Ticket(const utils::ID &ticketId, const utils::ID &passId, 
               const utils::ID &flightId, const string &issued,
               const string &origin, const string &destination, 
               const string &flightDate)
            : id(ticketId), passengerId(passId), flightId(flightId), 
              issuedDate(issued), origin(origin), destination(destination), 
              flightDate(flightDate) {}

        // Getters
        const utils::ID &getId() const { return id; }

        const utils::ID &getPassengerId() const { return passengerId; }

        const utils::ID &getFlightId() const { return flightId; }
        
        const string &getIssuedDate() const { return issuedDate; }
        const string &getOrigin() const { return origin; }
        const string &getDestination() const { return destination; }
        const string &getFlightDate() const { return flightDate; }

        // Serialization for storage
        string serialize() const;
        static Ticket deserialize(const string &line);
    };
}

#endif
