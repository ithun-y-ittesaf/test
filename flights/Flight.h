#ifndef FLIGHTS_FLIGHT_H
#define FLIGHTS_FLIGHT_H

#include <string>
#include "../utils/Types.h"

using namespace std;

namespace flights {
    
    class Flight {
    private:
        utils::ID id;
        string origin;
        string destination;
        string date;
        int capacity;
        int seatsBooked;

    public:

        Flight() : capacity(0), seatsBooked(0) {}

        Flight(const utils::ID &flightId, const string &originCity, 
               const string &destCity, const string &flightDate, 
               int totalCapacity, int bookedSeats)
            : id(flightId), origin(originCity), destination(destCity), 
              date(flightDate), capacity(totalCapacity), seatsBooked(bookedSeats) {}

        // Getters for all flight properties
        const utils::ID &getId() const { return id; }
        const string &getOrigin() const { return origin; }
        const string &getDestination() const { return destination; }
        const string &getDate() const { return date; }
        int getCapacity() const { return capacity; }
        int getSeatsBooked() const { return seatsBooked; }

        // Update number of booked seats
        void setSeatsBooked(int seatsCount) { seatsBooked = seatsCount; }

        // Storage Functions
        string serialize() const;
        static Flight deserialize(const string &line);
    };
}

#endif
