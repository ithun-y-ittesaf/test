#include "FlightManager.h"
#include "../storage/DataStorage.h"
#include "../logging/Logger.h"
#include <chrono>

namespace flights {
    bool FlightManager::load() {
        flightsById.clear();
        auto lines = storage::DataStorage::readAll("flights.txt");
        for (const auto &l : lines) {
            if (l.empty()) continue;
            Flight f = Flight::deserialize(l);
            flightsById[f.getId()] = f;
        }
        return true;
    }

    bool FlightManager::save() const {
        std::vector<std::string> lines;
        for (const auto &p : flightsById) {
            lines.push_back(p.second.serialize());
        }
        return storage::DataStorage::writeAll("flights.txt", lines);
    }

    utils::ID FlightManager::createFlight(const std::string &orig, const std::string &dest, const std::string &date, int capacity) {
        using namespace std::chrono;
        auto ts = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID id = "F" + std::to_string(ts);
        while (flightsById.find(id) != flightsById.end()) { ++ts; id = "F" + std::to_string(ts); }
        Flight f(id, orig, dest, date, capacity, 0);
        flightsById[id] = f;
        storage::DataStorage::appendLine("flights.txt", f.serialize());
        logging::Logger::logCritical("FlightCreate", "FLIGHT=" + id + "|" + orig + "->" + dest + "|cap=" + std::to_string(capacity));
        return id;
    }

    const Flight* FlightManager::get(const utils::ID &id) const {
        auto it = flightsById.find(id);
        if (it == flightsById.end()) return nullptr;
        return &it->second;
    }

    std::vector<Flight> FlightManager::all() const {
        std::vector<Flight> v;
        v.reserve(flightsById.size());
        for (const auto &p : flightsById) v.push_back(p.second);
        return v;
    }

    bool FlightManager::bookSeat(const utils::ID &id) {
        auto it = flightsById.find(id);
        if (it == flightsById.end()) return false;
        if (it->second.getSeatsBooked() >= it->second.getCapacity()) return false;
        it->second.setSeatsBooked(it->second.getSeatsBooked() + 1);
        save();
        logging::Logger::logCritical("Booking", std::string("FLIGHT=") + id);
        return true;
    }
}
