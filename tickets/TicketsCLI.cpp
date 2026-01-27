#include "TicketsCLI.h"
#include "../access/AccessControl.h"
#include "../flights/FlightManager.h"
#include <iostream>
#include <algorithm>

namespace tickets {
    void TicketsCLI::run(const utils::ID &currentUserId, utils::Role currentRole) {
        (void)currentRole;
        manager.load();
        std::cout << "\n-- My Tickets --\n";
        auto myTickets = manager.getForPassenger(currentUserId);
        std::cout << "Tickets (" << myTickets.size() << "):\n";
        for (const auto &tk : myTickets) {
            std::cout << "- " << tk.getId() << " | Flight: " << tk.getFlightId() 
                      << " | Issued: " << tk.getIssuedDate() << "\n";
        }
    }

    void TicketsCLI::runViewTickets(const utils::ID &currentUserId, utils::Role currentRole) {
        (void)currentRole;
        manager.load();
        
        std::cout << "\n========== My Tickets ==========" << "\n\n";
        auto myTickets = manager.getForPassenger(currentUserId);
        
        if (myTickets.empty()) {
            std::cout << "No tickets found.\n";
            return;
        }
        
        for (size_t i = 0; i < myTickets.size(); ++i) {
            const auto &tk = myTickets[i];
            std::cout << "[" << (i+1) << "] " << tk.getId() << " | " << tk.getOrigin() << " → "
                      << tk.getDestination() << " | " << tk.getFlightDate() << " | VALID\n";
        }
        
        std::cout << "\n0. Back\nSelect ticket for details > ";
        int choice = 0;
        std::cin >> choice;
        
        if (choice < 1 || choice > (int)myTickets.size()) {
            return;
        }
        
        const auto &selected = myTickets[choice - 1];
        std::cout << "\nTicket ID     : " << selected.getId() << "\n";
        std::cout << "Flight        : " << selected.getFlightId() << " | " << selected.getOrigin() << " → "
                  << selected.getDestination() << " | " << selected.getFlightDate() << "\n";
        std::cout << "Status        : VALID\n";
        std::cout << "Boarding Gate : Assigned at airport\n";
    }

    void TicketsCLI::runTravelHistory(const utils::ID &currentUserId, utils::Role currentRole) {
        (void)currentRole;
        manager.load();
        flightManager.load();
        
        std::cout << "\n========== Travel History ==========" << "\n\n";
        auto history = manager.getForPassenger(currentUserId);
        
        if (history.empty()) {
            std::cout << "No travel history.\n";
            return;
        }
        
        std::sort(history.begin(), history.end(), [](const Ticket &a, const Ticket &b) {
            return a.getIssuedDate() > b.getIssuedDate();
        });

        for (const auto &tk : history) {
            std::string routeOrigin = tk.getOrigin();
            std::string routeDest = tk.getDestination();
            std::string flightDate = tk.getFlightDate();

            if (routeOrigin.empty() || routeDest.empty() || flightDate.empty()) {
                if (const auto *flight = flightManager.get(tk.getFlightId())) {
                    routeOrigin = flight->getOrigin();
                    routeDest = flight->getDestination();
                    flightDate = flight->getDate();
                }
            }

            std::cout << routeOrigin << " → " << routeDest << " | " << flightDate
                      << " | Ticket " << tk.getId() << "\n";
        }
    }
}
