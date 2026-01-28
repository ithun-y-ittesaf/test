#ifndef TICKETS_TICKETMANAGER_H
#define TICKETS_TICKETMANAGER_H

#include <map>
#include <vector>
#include "Ticket.h"

using namespace std;

namespace flights { 
    class Flight; 
}

namespace tickets {
   
    class TicketManager {
    private:
        map<utils::ID, Ticket> ticketsById;

    public:
        bool load();
        bool save() const;
        utils::ID issueTicket(const utils::ID &passengerId, const flights::Flight &flight);
        const Ticket* get(const utils::ID &id) const;

        vector<Ticket> getForPassenger(const utils::ID &passengerId) const;
    };
}

#endif
