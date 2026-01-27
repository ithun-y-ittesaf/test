#ifndef FLIGHTS_FLIGHT_H
#define FLIGHTS_FLIGHT_H

#include <string>
#include "../utils/Types.h"

namespace flights {
    class Flight {
    private:
        utils::ID id;
        std::string origin;
        std::string destination;
        std::string date;
        int capacity;
        int seatsBooked;
    public:
        Flight() : capacity(0), seatsBooked(0) {}
        Flight(const utils::ID &id, const std::string &orig, const std::string &dest,
               const std::string &date, int capacity, int seatsBooked)
            : id(id), origin(orig), destination(dest), date(date), capacity(capacity), seatsBooked(seatsBooked) {}

        const utils::ID &getId() const { return id; }
        const std::string &getOrigin() const { return origin; }
        const std::string &getDestination() const { return destination; }
        const std::string &getDate() const { return date; }
        int getCapacity() const { return capacity; }
        int getSeatsBooked() const { return seatsBooked; }
        void setSeatsBooked(int v) { seatsBooked = v; }

        std::string serialize() const;
        static Flight deserialize(const std::string &line);
    };
}

#endif // FLIGHTS_FLIGHT_H
