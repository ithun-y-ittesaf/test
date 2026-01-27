#include "TicketManager.h"
#include "../storage/DataStorage.h"
#include "../logging/Logger.h"
#include "../flights/Flight.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace tickets {
    static std::string nowDateStr() {
        using namespace std::chrono;
        auto t = system_clock::to_time_t(system_clock::now());
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }

    bool TicketManager::load() {
        ticketsById.clear();
        auto lines = storage::DataStorage::readAll("tickets.txt");
        for (const auto &l : lines) {
            if (l.empty()) continue;
            Ticket t = Ticket::deserialize(l);
            ticketsById[t.getId()] = t;
        }
        return true;
    }

    bool TicketManager::save() const {
        std::vector<std::string> lines;
        for (const auto &p : ticketsById) {
            lines.push_back(p.second.serialize());
        }
        return storage::DataStorage::writeAll("tickets.txt", lines);
    }

    utils::ID TicketManager::issueTicket(const utils::ID &passengerId, const flights::Flight &flight) {
        using namespace std::chrono;
        auto ts = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID id = "TK" + std::to_string(ts);
        while (ticketsById.find(id) != ticketsById.end()) { ++ts; id = "TK" + std::to_string(ts); }
        Ticket t(id, passengerId, flight.getId(), nowDateStr(), flight.getOrigin(), flight.getDestination(), flight.getDate());
        ticketsById[id] = t;
        storage::DataStorage::appendLine("tickets.txt", t.serialize());
        logging::Logger::logCritical("TicketIssue", "PASS=" + passengerId + "|FLIGHT=" + flight.getId() + "|TICKET=" + id);
        return id;
    }

    const Ticket* TicketManager::get(const utils::ID &id) const {
        auto it = ticketsById.find(id);
        if (it == ticketsById.end()) return nullptr;
        return &it->second;
    }

    std::vector<Ticket> TicketManager::getForPassenger(const utils::ID &passengerId) const {
        std::vector<Ticket> out;
        for (const auto &p : ticketsById) {
            if (p.second.getPassengerId() == passengerId) out.push_back(p.second);
        }
        return out;
    }
}
