#include "TicketsCLI.h"
#include "../access/AccessControl.h"
#include "../flights/FlightManager.h"
#include <iostream>
#include <algorithm>

namespace tickets {
    void TicketsCLI::run(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        
        std::cout << "\n--- My Tickets ---\n";
        auto myTickets = manager.getForPassenger(userId);
        
        std::cout << "Total Tickets: " << myTickets.size() << "\n";
        for (const auto &ticket : myTickets) {
            std::cout << "- " << ticket.getId() << " | Flight: " << ticket.getFlightId() 
                      << " | Issued: " << ticket.getIssuedDate() << "\n";
        }
    }

    void TicketsCLI::runViewTickets(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        
        std::cout << "\n========== Your Tickets ==========\n\n";
        auto myTickets = manager.getForPassenger(userId);
        
        if (myTickets.empty()) {
            std::cout << "You don't have any tickets yet.\n";
            return;
        }
        
        // Display all tickets
        for (size_t i = 0; i < myTickets.size(); ++i) {
            const auto &ticket = myTickets[i];
            std::cout << "[" << (i + 1) << "] " << ticket.getId() << " | ";
            std::cout << ticket.getOrigin() << " → " << ticket.getDestination() << " | ";
            std::cout << ticket.getFlightDate() << " | Status: VALID\n";
        }
        
        std::cout << "\n0. Back\nSelect a ticket to view details > ";
        int choice = 0;
        std::cin >> choice;
        
        if (choice < 1 || choice > (int)myTickets.size()) {
            return;
        }
        
        // Show detailed information for selected ticket
        const auto &selectedTicket = myTickets[choice - 1];
        std::cout << "\n--- Ticket Details ---\n";
        std::cout << "Ticket ID     : " << selectedTicket.getId() << "\n";
        std::cout << "Flight        : " << selectedTicket.getFlightId() << "\n";
        std::cout << "Route         : " << selectedTicket.getOrigin() << " → " 
                  << selectedTicket.getDestination() << "\n";
        std::cout << "Flight Date   : " << selectedTicket.getFlightDate() << "\n";
        std::cout << "Issued        : " << selectedTicket.getIssuedDate() << "\n";
        std::cout << "Status        : VALID\n";
        std::cout << "Boarding Gate : Assigned at airport\n";
    }

    void TicketsCLI::runTravelHistory(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        flightManager.load();
        
        std::cout << "\n========== Travel History ==========\n\n";
        auto travelHistory = manager.getForPassenger(userId);
        
        if (travelHistory.empty()) {
            std::cout << "You haven't taken any flights yet.\n";
            return;
        }
        
        // Sort by date (most recent first)
        std::sort(travelHistory.begin(), travelHistory.end(), 
                 [](const Ticket &a, const Ticket &b) {
            return a.getIssuedDate() > b.getIssuedDate();
        });

        std::cout << "Past Flights:\n\n";
        for (const auto &ticket : travelHistory) {
            std::string origin = ticket.getOrigin();
            std::string destination = ticket.getDestination();
            std::string flightDate = ticket.getFlightDate();

            // Try to get flight details if ticket info is incomplete
            if (origin.empty() || destination.empty() || flightDate.empty()) {
                if (const auto *flight = flightManager.get(ticket.getFlightId())) {
                    origin = flight->getOrigin();
                    destination = flight->getDestination();
                    flightDate = flight->getDate();
                }
            }

            std::cout << origin << " → " << destination << " | " << flightDate
                      << " | Ticket: " << ticket.getId() << "\n";
        }
    }
}
