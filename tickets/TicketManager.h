#ifndef TICKETS_TICKETMANAGER_H
#define TICKETS_TICKETMANAGER_H

#include <map>
#include <vector>
#include "Ticket.h"

namespace flights { 
    class Flight; 
}

namespace tickets {
    /**
     * Manages all flight tickets in the system.
     * Handles ticket issuance, storage, and retrieval.
     */
    class TicketManager {
    private:
        std::map<utils::ID, Ticket> ticketsById;

    public:
        // Load tickets from persistent storage
        bool load();

        // Save all tickets to persistent storage
        bool save() const;

        // Issue a new ticket for a passenger
        utils::ID issueTicket(const utils::ID &passengerId, const flights::Flight &flight);

        // Get a ticket by ID
        const Ticket* get(const utils::ID &id) const;

        // Get all tickets for a passenger
        std::vector<Ticket> getForPassenger(const utils::ID &passengerId) const;
    };
}

#endif
