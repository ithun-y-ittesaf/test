#include "FlightsCLI.h"
#include "../access/AccessControl.h"
#include <iostream>
#include <iomanip>

namespace flights {
    void FlightsCLI::run(const utils::ID &userId, utils::Role userRole) {
        manager.load();
        ticketManager.load();
        
        std::cout << "\n--- Flight Management ---\n";
        
        if (access::AccessControl::anyOf(userRole, {utils::Role::Admin})) {
            std::cout << "1. List All Flights\n";
            std::cout << "2. Create New Flight\n";
            std::cout << "3. Book Seat for Passenger\n";
            std::cout << "4. Back\n";
            std::cout << "Choice: ";
        } else {
            std::cout << "1. List All Flights\n";
            std::cout << "2. Book a Flight\n";
            std::cout << "3. Back\n";
            std::cout << "Choice: ";
        }
        
        int choice = 0;
        std::cin >> choice;
        
        if (choice == 1) {
            // List all flights
            auto flights = manager.all();
            std::cout << "\nAvailable Flights (" << flights.size() << "):\n\n";
            for (const auto &flight : flights) {
                int seatsAvailable = flight.getCapacity() - flight.getSeatsBooked();
                std::cout << "Flight ID: " << flight.getId() << "\n";
                std::cout << "  Route: " << flight.getOrigin() << " → " << flight.getDestination() << "\n";
                std::cout << "  Date: " << flight.getDate() << "\n";
                std::cout << "  Seats: " << seatsAvailable << " available\n\n";
            }
        } else if (choice == 2) {
            if (access::AccessControl::anyOf(userRole, {utils::Role::Admin})) {
                // Admin: Create new flight
                std::string origin, destination, date;
                int capacity;
                
                std::cout << "\n--- Create Flight ---\n";
                std::cout << "Origin (City): ";
                std::cin >> origin;
                
                std::cout << "Destination (City): ";
                std::cin >> destination;
                
                std::cout << "Date (YYYY-MM-DD): ";
                std::cin >> date;
                
                std::cout << "Capacity: ";
                std::cin >> capacity;
                
                auto flightId = manager.createFlight(origin, destination, date, capacity);
                std::cout << "\n✓ Flight created with ID: " << flightId << "\n";
            } else {
                // Passenger: Book a flight
                if (userId.empty()) {
                    std::cout << "\nError: No user logged in.\n";
                    return;
                }
                
                std::string flightId;
                std::cout << "\nEnter Flight ID to book: ";
                std::cin >> flightId;
                
                const Flight* flight = manager.get(flightId);
                if (!flight) {
                    std::cout << "\nFlight not found.\n";
                    return;
                }
                
                bool success = manager.bookSeat(flightId);
                if (success) {
                    auto ticketId = ticketManager.issueTicket(userId, *flight);
                    std::cout << "\n✓ Booking successful!\n";
                    std::cout << "Ticket ID: " << ticketId << "\n";
                } else {
                    std::cout << "\nBooking failed (flight may be full).\n";
                }
            }
        } else if (choice == 3) {
            if (access::AccessControl::anyOf(userRole, {utils::Role::Admin})) {
                // Admin: Book for a passenger
                std::string passengerId, flightId;
                
                std::cout << "\nPassenger ID: ";
                std::cin >> passengerId;
                
                std::cout << "Flight ID: ";
                std::cin >> flightId;
                
                const Flight* flight = manager.get(flightId);
                if (!flight) {
                    std::cout << "\nFlight not found.\n";
                    return;
                }
                
                bool success = manager.bookSeat(flightId);
                if (success) {
                    auto ticketId = ticketManager.issueTicket(passengerId, *flight);
                    std::cout << "\n✓ Booked for passenger " << passengerId << "!\n";
                    std::cout << "Ticket ID: " << ticketId << "\n";
                } else {
                    std::cout << "\nBooking failed.\n";
                }
            }
        }
    }

    void FlightsCLI::runSearchAndBook(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        ticketManager.load();
        
        std::cout << "\n======= Search & Book Flights =======\n";
        std::cout << "1. Search by Route & Date\n";
        std::cout << "2. View All Flights\n";
        std::cout << "0. Back\n";
        std::cout << "\nSelect an option > ";
        
        int searchChoice = 0;
        std::cin >> searchChoice;
        
        if (searchChoice == 0) {
            return;
        }
        
        // Get search criteria
        std::string origin, destination, date;
        if (searchChoice == 1) {
            std::cout << "\n--- Enter Search Criteria ---\n";
            std::cout << "From (City): ";
            std::cin >> origin;
            std::cout << "To (City): ";
            std::cin >> destination;
            std::cout << "Date (YYYY-MM-DD): ";
            std::cin >> date;
        }
        
        // Search flights
        auto allFlights = manager.all();
        std::vector<Flight> results;
        
        if (searchChoice == 1) {
            for (const auto &flight : allFlights) {
                if (flight.getOrigin() == origin && 
                    flight.getDestination() == destination && 
                    flight.getDate() == date) {
                    results.push_back(flight);
                }
            }
        } else {
            results = allFlights;
        }
        
        // Display results
        if (results.empty()) {
            std::cout << "\nNo flights found matching your criteria.\n";
            return;
        }
        
        std::cout << "\n--- Available Flights ---\n\n";
        for (size_t i = 0; i < results.size(); ++i) {
            const auto &flight = results[i];
            int seatsAvailable = flight.getCapacity() - flight.getSeatsBooked();
            
            std::cout << "[" << (i + 1) << "] " << flight.getId() << " | ";
            std::cout << flight.getOrigin() << " → " << flight.getDestination() << " | ";
            std::cout << flight.getDate() << " | ";
            std::cout << "BDT 45,000 | ";
            std::cout << seatsAvailable << " seats available\n";
        }
        
        std::cout << "\n0. Cancel\nSelect a flight to book > ";
        int selection = 0;
        std::cin >> selection;
        
        if (selection < 1 || selection > (int)results.size()) {
            std::cout << "\nBooking cancelled.\n";
            return;
        }
        
        const Flight &selectedFlight = results[selection - 1];
        
        // Confirm booking
        std::cout << "\n--- Booking Confirmation ---\n";
        std::cout << "Flight: " << selectedFlight.getId() << "\n";
        std::cout << "Route: " << selectedFlight.getOrigin() << " → " 
                  << selectedFlight.getDestination() << "\n";
        std::cout << "Date: " << selectedFlight.getDate() << "\n";
        std::cout << "Price: BDT 45,000\n\n";
        std::cout << "Proceed with booking? (y/n) > ";
        
        char proceed;
        std::cin >> proceed;
        
        if (proceed != 'y' && proceed != 'Y') {
            std::cout << "\nBooking cancelled.\n";
            return;
        }
        
        // Process booking
        bool booked = manager.bookSeat(selectedFlight.getId());
        if (!booked) {
            std::cout << "\nBooking failed - no seats available.\n";
            return;
        }
        
        auto ticketId = ticketManager.issueTicket(userId, selectedFlight);
        std::cout << "\n✓ Payment successful!\n";
        std::cout << "Your ticket ID: " << ticketId << "\n";
        std::cout << "You're all set to fly!\n";
    }
}
