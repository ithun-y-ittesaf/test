#ifndef FLIGHTS_FLIGHTSCLI_H
#define FLIGHTS_FLIGHTSCLI_H

#include <string>
#include "FlightManager.h"
#include "../tickets/TicketManager.h"
#include "../utils/Types.h"

namespace flights {
    /**
     * CLI interface for flight management and booking operations.
     */
    class FlightsCLI {
    private:
        FlightManager &manager;
        tickets::TicketManager &ticketManager;

    public:
        explicit FlightsCLI(FlightManager &m, tickets::TicketManager &tm) 
            : manager(m), ticketManager(tm) {}

        // Admin flight management interface
        void run(const utils::ID &userId, utils::Role userRole);

        // Passenger flight search and booking interface
        void runSearchAndBook(const utils::ID &userId, utils::Role userRole);
    };
}

#endif
