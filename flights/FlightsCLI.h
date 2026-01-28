#ifndef FLIGHTS_FLIGHTSCLI_H
#define FLIGHTS_FLIGHTSCLI_H

#include <string>
#include "FlightManager.h"
#include "../tickets/TicketManager.h"
#include "../banking/BankingManager.h"
#include "../utils/Types.h"

using namespace std;

namespace flights {

    class FlightsCLI {
    private:
        FlightManager &manager;
        tickets::TicketManager &ticketManager;
        banking::BankingManager &bankingManager;

    public:
        explicit FlightsCLI(FlightManager &m, tickets::TicketManager &tm, banking::BankingManager &bm) 
            : manager(m), ticketManager(tm), bankingManager(bm) {}

        void run(const utils::ID &userId, utils::Role userRole);

        void runSearchAndBook(const utils::ID &userId, utils::Role userRole);
    };
}

#endif
