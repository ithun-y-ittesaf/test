#include "FlightsCLI.h"
#include "../access/AccessControl.h"
#include <iostream>
#include <iomanip>

namespace flights {
    void FlightsCLI::run(const utils::ID &currentUserId, utils::Role currentRole) {
        manager.load();
        ticketManager.load();
        std::cout << "\n-- Flights --\n";
        if (access::AccessControl::anyOf(currentRole, {utils::Role::Admin})) {
            std::cout << "1) List Flights\n2) Create Flight\n3) Book Seat\n4) Back\nChoice: ";
        } else {
            std::cout << "1) List Flights\n2) Book Seat\n3) Back\nChoice: ";
        }
        int ch = 0; std::cin >> ch;
        if (ch == 1) {
            auto all = manager.all();
            std::cout << "Flights (" << all.size() << "):\n";
            for (const auto &f : all) {
                std::cout << "- " << f.getId() << " | " << f.getOrigin() << "->" << f.getDestination()
                          << " | " << f.getDate() << " | " << (f.getCapacity()-f.getSeatsBooked()) << " seats left\n";
            }
        } else if (ch == 2) {
            if (access::AccessControl::anyOf(currentRole, {utils::Role::Admin})) {
                std::string o,d,date; int cap;
                std::cout << "Origin: "; std::cin >> o;
                std::cout << "Destination: "; std::cin >> d;
                std::cout << "Date(YYYY-MM-DD): "; std::cin >> date;
                std::cout << "Capacity: "; std::cin >> cap;
                auto id = manager.createFlight(o,d,date,cap);
                std::cout << "Created flight ID: " << id << "\n";
            } else {
                if (currentUserId.empty()) { std::cout << "No user selected.\n"; return; }
                std::string fid;
                std::cout << "Flight ID to book: "; std::cin >> fid;
                const Flight* flight = manager.get(fid);
                if (!flight) { std::cout << "Flight not found.\n"; return; }
                bool ok = manager.bookSeat(fid);
                if (ok) {
                    auto ticketId = ticketManager.issueTicket(currentUserId, *flight);
                    std::cout << "Booked! Ticket ID: " << ticketId << "\n";
                } else {
                    std::cout << "Booking failed.\n";
                }
            }
        } else if (ch == 3) {
            if (access::AccessControl::anyOf(currentRole, {utils::Role::Admin})) {
                std::cout << "Passenger ID: "; std::string passId; std::cin >> passId;
                std::string fid;
                std::cout << "Flight ID to book: "; std::cin >> fid;
                const Flight* flight = manager.get(fid);
                if (!flight) { std::cout << "Flight not found.\n"; return; }
                bool ok = manager.bookSeat(fid);
                if (ok) {
                    auto ticketId = ticketManager.issueTicket(passId, *flight);
                    std::cout << "Booked for " << passId << "! Ticket ID: " << ticketId << "\n";
                } else {
                    std::cout << "Booking failed.\n";
                }
            }
        }
    }

    void FlightsCLI::runSearchAndBook(const utils::ID &currentUserId, utils::Role currentRole) {
        (void)currentRole;
        manager.load();
        ticketManager.load();
        
        std::cout << "\n======= Flight Search =======\n";
        std::cout << "1. Search by Route & Date\n";
        std::cout << "2. View All Flights\n";
        std::cout << "0. Back\n";
        std::cout << "\nSelect an option > ";
        
        int searchChoice = 0;
        std::cin >> searchChoice;
        
        if (searchChoice == 0) return;
        
        std::string from, to, date;
        if (searchChoice == 1) {
            std::cout << "\nFrom (Airport Code): ";
            std::cin >> from;
            std::cout << "To   (Airport Code): ";
            std::cin >> to;
            std::cout << "Date (YYYY-MM-DD)  : ";
            std::cin >> date;
        }
        
        auto allFlights = manager.all();
        std::vector<Flight> results;
        
        if (searchChoice == 1) {
            for (const auto &f : allFlights) {
                if (f.getOrigin() == from && f.getDestination() == to && f.getDate() == date) {
                    results.push_back(f);
                }
            }
        } else {
            results = allFlights;
        }
        
        if (results.empty()) {
            std::cout << "\nNo flights found matching your criteria.\n";
            return;
        }
        
        std::cout << "\nAvailable Flights:\n\n";
        for (size_t i = 0; i < results.size(); ++i) {
            const auto &f = results[i];
            int seatsAvailable = f.getCapacity() - f.getSeatsBooked();
            std::cout << "[" << (i+1) << "] " << f.getId() << " | " 
                      << f.getOrigin() << " → " << f.getDestination() << " | "
                      << f.getDate() << " | BDT 45,000 | " 
                      << seatsAvailable << " seats\n";
        }
        
        std::cout << "\n0. Cancel\nSelect a flight > ";
        int selection = 0;
        std::cin >> selection;
        
        if (selection < 1 || selection > (int)results.size()) {
            std::cout << "\nBooking cancelled.\n";
            return;
        }
        
        const Flight &selectedFlight = results[selection - 1];
        
        std::cout << "\nConfirm booking for " << selectedFlight.getId() << "\n";
        std::cout << "Price: BDT 45,000\n\n";
        std::cout << "Proceed? (y/n) > ";
        char proceed;
        std::cin >> proceed;
        
        if (proceed != 'y' && proceed != 'Y') {
            std::cout << "\nBooking cancelled.\n";
            return;
        }
        
        bool booked = manager.bookSeat(selectedFlight.getId());
        if (!booked) {
            std::cout << "\n❌ Booking failed. No seats available.\n";
            return;
        }
        
        auto ticketId = ticketManager.issueTicket(currentUserId, selectedFlight);
        std::cout << "\n✅ Payment successful.\n";
        std::cout << "🎟 Ticket ID: " << ticketId << "\n";
    }
}
