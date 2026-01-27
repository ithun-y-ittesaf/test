#ifndef FLIGHTS_FLIGHTMANAGER_H
#define FLIGHTS_FLIGHTMANAGER_H

#include <map>
#include <vector>
#include "Flight.h"

namespace flights {
    class FlightManager {
    private:
        std::map<utils::ID, Flight> flightsById;
    public:
        bool load();
        bool save() const;

        utils::ID createFlight(const std::string &orig, const std::string &dest, const std::string &date, int capacity);
        const Flight* get(const utils::ID &id) const;
        std::vector<Flight> all() const;
        bool bookSeat(const utils::ID &id);
    };
}

#endif // FLIGHTS_FLIGHTMANAGER_H
