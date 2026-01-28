#include "FlightsCLI.h"
#include "../access/AccessControl.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace flights {
    void FlightsCLI::run(const utils::ID &userId, utils::Role userRole) {
        manager.load();
        ticketManager.load();
        
        cout << "\n--- Flight Management ---\n";
        
        if (access::AccessControl::anyOf(userRole, {utils::Role::Admin})) {
            cout << "1. List All Flights\n";
            cout << "2. Create New Flight\n";
            cout << "3. Book Seat for Passenger\n";
            cout << "4. Back\n";
            cout << "Choice: ";
        } else {
            cout << "1. List All Flights\n";
            cout << "2. Book a Flight\n";
            cout << "3. Back\n";
            cout << "Choice: ";
        }
        
        int choice = 0;
        cin >> choice;
        
        if (choice == 1) {
            // List all flights
            auto flights = manager.all();
            cout << "\nAvailable Flights (" << flights.size() << "):\n\n";
            for (const auto &flight : flights) {
                int seatsAvailable = flight.getCapacity() - flight.getSeatsBooked();
                cout << "Flight ID: " << flight.getId() << "\n";
                cout << "  Route: " << flight.getOrigin() << " → " << flight.getDestination() << "\n";
                cout << "  Date: " << flight.getDate() << "\n";
                cout << "  Seats: " << seatsAvailable << " available\n\n";
            }
        } else if (choice == 2) {
            if (access::AccessControl::anyOf(userRole, {utils::Role::Admin})) {
                // Admin: Create new flight
                string origin, destination, date;
                int capacity;
                
                cout << "\n--- Create Flight ---\n";
                cout << "Origin (City): ";
                cin >> origin;
                
                cout << "Destination (City): ";
                cin >> destination;
                
                cout << "Date (YYYY-MM-DD): ";
                cin >> date;
                
                cout << "Capacity: ";
                cin >> capacity;
                
                auto flightId = manager.createFlight(origin, destination, date, capacity);
                cout << "\n✓ Flight created with ID: " << flightId << "\n";
            } else {
                // Passenger: Book a flight
                if (userId.empty()) {
                    cout << "\nError: No user logged in.\n";
                    return;
                }
                
                string flightId;
                cout << "\nEnter Flight ID to book: ";
                cin >> flightId;
                
                const Flight* flight = manager.get(flightId);
                if (!flight) {
                    cout << "\nFlight not found.\n";
                    return;
                }
                
                bool success = manager.bookSeat(flightId);
                if (success) {
                    auto ticketId = ticketManager.issueTicket(userId, *flight);
                    cout << "\n✓ Booking successful!\n";
                    cout << "Ticket ID: " << ticketId << "\n";
                } else {
                    cout << "\nBooking failed (flight may be full).\n";
                }
            }
        } else if (choice == 3) {
            if (access::AccessControl::anyOf(userRole, {utils::Role::Admin})) {
                // Admin: Book for a passenger
                string passengerId, flightId;
                
                cout << "\nPassenger ID: ";
                cin >> passengerId;
                
                cout << "Flight ID: ";
                cin >> flightId;
                
                const Flight* flight = manager.get(flightId);
                if (!flight) {
                    cout << "\nFlight not found.\n";
                    return;
                }
                
                bool success = manager.bookSeat(flightId);
                if (success) {
                    auto ticketId = ticketManager.issueTicket(passengerId, *flight);
                    cout << "\n✓ Booked for passenger " << passengerId << "!\n";
                    cout << "Ticket ID: " << ticketId << "\n";
                } else {
                    cout << "\nBooking failed.\n";
                }
            }
        }
    }

    void FlightsCLI::runSearchAndBook(const utils::ID &userId, utils::Role userRole) {
        (void)userRole;
        manager.load();
        ticketManager.load();
        
        cout << "\n======= Search & Book Flights =======\n";
        cout << "1. Search by Route & Date\n";
        cout << "2. View All Flights\n";
        cout << "0. Back\n";
        cout << "\nSelect an option > ";
        
        int searchChoice = 0;
        cin >> searchChoice;
        
        if (searchChoice == 0) {
            return;
        }
        
        // Get search criteria
        string origin, destination, date;
        if (searchChoice == 1) {
            cout << "\n--- Enter Search Criteria ---\n";
            cout << "From (City): ";
            cin >> origin;
            cout << "To (City): ";
            cin >> destination;
            cout << "Date (YYYY-MM-DD): ";
            cin >> date;
        }
        
        // Search flights
        auto allFlights = manager.all();
        vector<Flight> results;
        
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
            cout << "\nNo flights found matching your criteria.\n";
            return;
        }
        
        cout << "\n--- Available Flights ---\n\n";
        for (size_t i = 0; i < results.size(); ++i) {
            const auto &flight = results[i];
            int seatsAvailable = flight.getCapacity() - flight.getSeatsBooked();
            
            cout << "[" << (i + 1) << "] " << flight.getId() << " | ";
            cout << flight.getOrigin() << " → " << flight.getDestination() << " | ";
            cout << flight.getDate() << " | ";
            cout << "BDT 45,000 | ";
            cout << seatsAvailable << " seats available\n";
        }
        
        cout << "\n0. Cancel\nSelect a flight to book > ";
        int selection = 0;
        cin >> selection;
        
        if (selection < 1 || selection > (int)results.size()) {
            cout << "\nBooking cancelled.\n";
            return;
        }
        
        const Flight &selectedFlight = results[selection - 1];
        
        // Confirm booking
        cout << "\n--- Booking Confirmation ---\n";
        cout << "Flight: " << selectedFlight.getId() << "\n";
        cout << "Route: " << selectedFlight.getOrigin() << " → " 
                  << selectedFlight.getDestination() << "\n";
        cout << "Date: " << selectedFlight.getDate() << "\n";
        
        // Check user's balance before showing price
        const banking::BankingAccount* account = bankingManager.getAccountByUser(userId);
        const long long FLIGHT_FARE_CENTS = 4500000; // 45,000 BDT in cents
        
        if (!account) {
            cout << "\nError: No banking account found for user.\n";
            return;
        }
        
        cout << "Price: BDT 45,000\n";
        cout << "Your Current Balance: BDT " << (account->getBalanceCents() / 100) << "\n\n";
        
        // Check if user has sufficient funds
        if (account->getBalanceCents() < FLIGHT_FARE_CENTS) {
            cout << "✗ Insufficient funds! You need BDT 45,000 to book this flight.\n";
            cout << "Please deposit more money to your account.\n";
            return;
        }
        
        cout << "Proceed with booking? (y/n) > ";
        
        char proceed;
        cin >> proceed;
        
        if (proceed != 'y' && proceed != 'Y') {
            cout << "\nBooking cancelled.\n";
            return;
        }
        
        // Process booking
        bool booked = manager.bookSeat(selectedFlight.getId());
        if (!booked) {
            cout << "\nBooking failed - no seats available.\n";
            return;
        }
        
        // Deduct fare from user's account
        utils::ID accountId = account->getId();
        auto withdrawResult = bankingManager.withdraw(accountId, FLIGHT_FARE_CENTS, 
                                                       "Flight ticket - " + selectedFlight.getId());
        
        if (!withdrawResult.ok) {
            cout << "\nPayment failed: " << withdrawResult.message << "\n";
            // Revert the booking since payment failed
            // Note: In a real system, this should be atomic
            return;
        }
        
        auto ticketId = ticketManager.issueTicket(userId, selectedFlight);
        cout << "\n✓ Payment successful!\n";
        cout << "Your ticket ID: " << ticketId << "\n";
        cout << "You're all set to fly!\n";
    }
}
