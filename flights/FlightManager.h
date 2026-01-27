#ifndef FLIGHTS_FLIGHTMANAGER_H
#define FLIGHTS_FLIGHTMANAGER_H

#include <map>
#include <vector>
#include "Flight.h"

namespace flights {
    /**
     * Manages all flights in the system.
     * Handles loading, saving, querying, and seat bookings.
     */
    class FlightManager {
    private:
        std::map<utils::ID, Flight> flightsById;

    public:
        // Load flights from persistent storage
        bool load();

        // Save all flights to persistent storage
        bool save() const;

        // Create a new flight
        utils::ID createFlight(const std::string &origin, const std::string &destination, 
                             const std::string &date, int capacity);

        // Get a flight by ID
        const Flight* get(const utils::ID &id) const;

        // Get all flights
        std::vector<Flight> all() const;

        // Book a seat on a flight (decrements available seats)
        bool bookSeat(const utils::ID &flightId);
    };
}

#endif
