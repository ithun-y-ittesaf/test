#include "TicketManager.h"
#include "../storage/DataStorage.h"
#include "../logging/Logger.h"
#include "../flights/Flight.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

namespace tickets {
    // Helper function to get current date as YYYY-MM-DD string
    static string getCurrentDateString() {
        using namespace chrono;
        
        auto now = system_clock::to_time_t(system_clock::now());
        tm timeinfo = *localtime(&now);
        
        stringstream ss;
        ss << put_time(&timeinfo, "%Y-%m-%d");
        return ss.str();
    }

    bool TicketManager::load() {
        ticketsById.clear();
        auto lines = storage::DataStorage::readAll("tickets.txt");
        
        for (const auto &line : lines) {
            if (line.empty()) {
                continue;
            }
            
            Ticket ticket = Ticket::deserialize(line);
            ticketsById[ticket.getId()] = ticket;
        }
        
        return true;
    }

    bool TicketManager::save() const {
        vector<string> lines;
        
        for (const auto &pair : ticketsById) {
            lines.push_back(pair.second.serialize());
        }
        
        return storage::DataStorage::writeAll("tickets.txt", lines);
    }

    utils::ID TicketManager::issueTicket(const utils::ID &passengerId, const flights::Flight &flight) {
        using namespace chrono;
        
        auto timestamp = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID ticketId = "TK" + to_string(timestamp);
        
        // Ensure ID is unique
        while (ticketsById.find(ticketId) != ticketsById.end()) {
            ++timestamp;
            ticketId = "TK" + to_string(timestamp);
        }
        
        // Create new ticket
        Ticket newTicket(ticketId, passengerId, flight.getId(), getCurrentDateString(), 
                        flight.getOrigin(), flight.getDestination(), flight.getDate());
        ticketsById[ticketId] = newTicket;
        
        storage::DataStorage::appendLine("tickets.txt", newTicket.serialize());
        
        // Log the ticket issuance
        logging::Logger::logCritical("TicketIssue", 
            "PASSENGER=" + passengerId + "|FLIGHT=" + flight.getId() + "|TICKET=" + ticketId);
        
        return ticketId;
    }

    const Ticket* TicketManager::get(const utils::ID &id) const {
        auto it = ticketsById.find(id);
        if (it == ticketsById.end()) {
            return nullptr;
        }
        return &it->second;
    }

    vector<Ticket> TicketManager::getForPassenger(const utils::ID &passengerId) const {
        vector<Ticket> tickets;
        
        for (const auto &pair : ticketsById) {
            if (pair.second.getPassengerId() == passengerId) {
                tickets.push_back(pair.second);
            }
        }
        
        return tickets;
    }
}
