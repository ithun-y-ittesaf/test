#ifndef TICKETS_TICKETSCLI_H
#define TICKETS_TICKETSCLI_H

#include <string>
#include "TicketManager.h"
#include "../utils/Types.h"

namespace flights { 
    class FlightManager; 
}

namespace tickets {
    
    class TicketsCLI {
    private:
        TicketManager &manager;
        flights::FlightManager &flightManager;

    public:
        TicketsCLI(TicketManager &m, flights::FlightManager &fm) 
            : manager(m), flightManager(fm) {}

        void run(const utils::ID &userId, utils::Role userRole);

        void runViewTickets(const utils::ID &userId, utils::Role userRole);

        void runTravelHistory(const utils::ID &userId, utils::Role userRole);
    };
}

#endif
