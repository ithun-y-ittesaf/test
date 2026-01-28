#ifndef FLIGHTS_FLIGHTMANAGER_H
#define FLIGHTS_FLIGHTMANAGER_H

#include <map>
#include <vector>
#include "Flight.h"

using namespace std;

namespace flights {
    
    class FlightManager {
    private:
        map<utils::ID, Flight> flightsById;

    public:

        bool load();

        bool save() const;

        utils::ID createFlight(const string &origin, const string &destination, 
                             const string &date, int capacity);

        const Flight* get(const utils::ID &id) const;

        vector<Flight> all() const;

        // Book a seat on a flight (decrements available seats)
        bool bookSeat(const utils::ID &flightId);
    };
}

#endif
