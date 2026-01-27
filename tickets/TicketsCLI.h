#ifndef TICKETS_TICKETSCLI_H
#define TICKETS_TICKETSCLI_H

#include <string>
#include "TicketManager.h"
#include "../utils/Types.h"

namespace flights { 
    class FlightManager; 
}

namespace tickets {
    /**
     * CLI interface for ticket management and travel history.
     */
    class TicketsCLI {
    private:
        TicketManager &manager;
        flights::FlightManager &flightManager;

    public:
        TicketsCLI(TicketManager &m, flights::FlightManager &fm) 
            : manager(m), flightManager(fm) {}

        // Admin ticket management interface
        void run(const utils::ID &userId, utils::Role userRole);

        // View current tickets interface
        void runViewTickets(const utils::ID &userId, utils::Role userRole);

        // View travel history interface
        void runTravelHistory(const utils::ID &userId, utils::Role userRole);
    };
}

#endif
