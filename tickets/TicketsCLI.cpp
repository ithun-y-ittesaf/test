#include "TicketsCLI.h"
#include "../access/AccessControl.h"
#include "../flights/FlightManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace tickets {
    void TicketsCLI::run(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        
        cout << "\n--- My Tickets ---\n";
        auto myTickets = manager.getForPassenger(userId);
        
        cout << "Total Tickets: " << myTickets.size() << "\n";
        for (const auto &ticket : myTickets) {
            cout << "- " << ticket.getId() << " | Flight: " << ticket.getFlightId() 
                      << " | Issued: " << ticket.getIssuedDate() << "\n";
        }
    }

    void TicketsCLI::runViewTickets(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        
        cout << "\n========== Your Tickets ==========\n\n";
        auto myTickets = manager.getForPassenger(userId);
        
        if (myTickets.empty()) {
            cout << "You don't have any tickets yet.\n";
            return;
        }
        
        // Display all tickets
        for (size_t i = 0; i < myTickets.size(); ++i) {
            const auto &ticket = myTickets[i];
            cout << "[" << (i + 1) << "] " << ticket.getId() << " | ";
            cout << ticket.getOrigin() << " → " << ticket.getDestination() << " | ";
            cout << ticket.getFlightDate() << " | Status: VALID\n";
        }
        
        cout << "\n0. Back\nSelect a ticket to view details > ";
        int choice = 0;
        cin >> choice;
        
        if (choice < 1 || choice > (int)myTickets.size()) {
            return;
        }
        
        // Show detailed information for selected ticket
        const auto &selectedTicket = myTickets[choice - 1];
        cout << "\n--- Ticket Details ---\n";
        cout << "Ticket ID     : " << selectedTicket.getId() << "\n";
        cout << "Flight        : " << selectedTicket.getFlightId() << "\n";
        cout << "Route         : " << selectedTicket.getOrigin() << " → " 
                  << selectedTicket.getDestination() << "\n";
        cout << "Flight Date   : " << selectedTicket.getFlightDate() << "\n";
        cout << "Issued        : " << selectedTicket.getIssuedDate() << "\n";
        cout << "Status        : VALID\n"; // More to be added later
    }

    void TicketsCLI::runTravelHistory(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        flightManager.load();
        
        cout << "\n========== Travel History ==========\n\n";
        auto travelHistory = manager.getForPassenger(userId);
        
        if (travelHistory.empty()) {
            cout << "You haven't taken any flights yet.\n";
            return;
        }
        
        // Sort by date (most recent first)
        sort(travelHistory.begin(), travelHistory.end(), 
                 [](const Ticket &a, const Ticket &b) {
            return a.getIssuedDate() > b.getIssuedDate();
        });

        cout << "Past Flights:\n\n";
        for (const auto &ticket : travelHistory) {
            string origin = ticket.getOrigin();
            string destination = ticket.getDestination();
            string flightDate = ticket.getFlightDate();

            // Try to get flight details if ticket info is incomplete
            if (origin.empty() || destination.empty() || flightDate.empty()) {
                if (const auto *flight = flightManager.get(ticket.getFlightId())) {
                    origin = flight->getOrigin();
                    destination = flight->getDestination();
                    flightDate = flight->getDate();
                }
            }

            cout << origin << " → " << destination << " | " << flightDate
                      << " | Ticket: " << ticket.getId() << "\n";
        }
    }
}
