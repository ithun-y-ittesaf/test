#include "FlightManager.h"
#include "../storage/DataStorage.h"
#include "../logging/Logger.h"
#include <chrono>

namespace flights {
    bool FlightManager::load() {
        flightsById.clear();
        auto lines = storage::DataStorage::readAll("flights.txt");
        
        for (const auto &line : lines) {
            if (line.empty()) {
                continue;
            }
            
            Flight flight = Flight::deserialize(line);
            flightsById[flight.getId()] = flight;
        }
        
        return true;
    }

    bool FlightManager::save() const {
        std::vector<std::string> lines;
        
        for (const auto &pair : flightsById) {
            lines.push_back(pair.second.serialize());
        }
        
        return storage::DataStorage::writeAll("flights.txt", lines);
    }

    utils::ID FlightManager::createFlight(const std::string &origin, const std::string &destination, 
                                         const std::string &date, int capacity) {
        using namespace std::chrono;
        
        // Generate unique ID using current timestamp
        auto timestamp = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID flightId = "F" + std::to_string(timestamp);
        
        // Ensure ID is unique
        while (flightsById.find(flightId) != flightsById.end()) {
            ++timestamp;
            flightId = "F" + std::to_string(timestamp);
        }
        
        // Create new flight with no bookings yet
        Flight newFlight(flightId, origin, destination, date, capacity, 0);
        flightsById[flightId] = newFlight;
        
        // Persist to storage
        storage::DataStorage::appendLine("flights.txt", newFlight.serialize());
        
        // Log the creation
        logging::Logger::logCritical("FlightCreate", 
            "FLIGHT=" + flightId + "|" + origin + "->" + destination + 
            "|capacity=" + std::to_string(capacity));
        
        return flightId;
    }

    const Flight* FlightManager::get(const utils::ID &id) const {
        auto it = flightsById.find(id);
        if (it == flightsById.end()) {
            return nullptr;
        }
        return &it->second;
    }

    std::vector<Flight> FlightManager::all() const {
        std::vector<Flight> flights;
        flights.reserve(flightsById.size());
        
        for (const auto &pair : flightsById) {
            flights.push_back(pair.second);
        }
        
        return flights;
    }

    bool FlightManager::bookSeat(const utils::ID &flightId) {
        auto it = flightsById.find(flightId);
        if (it == flightsById.end()) {
            return false;
        }
        
        // Check if flight is full
        if (it->second.getSeatsBooked() >= it->second.getCapacity()) {
            return false;
        }
        
        // Book a seat
        it->second.setSeatsBooked(it->second.getSeatsBooked() + 1);
        save();
        
        // Log the booking
        logging::Logger::logCritical("Booking", "FLIGHT=" + flightId);
        
        return true;
    }
}
