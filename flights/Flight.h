#ifndef FLIGHTS_FLIGHT_H
#define FLIGHTS_FLIGHT_H

#include <string>
#include "../utils/Types.h"

namespace flights {
    /**
     * Represents a flight in the system.
     * Contains route, date, and seat availability information.
     */
    class Flight {
    private:
        utils::ID id;
        std::string origin;
        std::string destination;
        std::string date;
        int capacity;
        int seatsBooked;

    public:
        // Default constructor for empty flight
        Flight() : capacity(0), seatsBooked(0) {}

        // Full constructor with all flight details
        Flight(const utils::ID &flightId, const std::string &originCity, 
               const std::string &destCity, const std::string &flightDate, 
               int totalCapacity, int bookedSeats)
            : id(flightId), origin(originCity), destination(destCity), 
              date(flightDate), capacity(totalCapacity), seatsBooked(bookedSeats) {}

        // Getters for all flight properties
        const utils::ID &getId() const { return id; }
        const std::string &getOrigin() const { return origin; }
        const std::string &getDestination() const { return destination; }
        const std::string &getDate() const { return date; }
        int getCapacity() const { return capacity; }
        int getSeatsBooked() const { return seatsBooked; }

        // Update number of booked seats
        void setSeatsBooked(int seatsCount) { seatsBooked = seatsCount; }

        // Serialization for storage
        std::string serialize() const;
        static Flight deserialize(const std::string &line);
    };
}

#endif
