#include <iostream>
#include "users/UserManager.h"
#include "users/UserCLI.h"
#include "banking/BankingManager.h"
#include "banking/BankingCLI.h"
#include "flights/FlightManager.h"
#include "flights/FlightsCLI.h"
#include "tickets/TicketManager.h"
#include "tickets/TicketsCLI.h"
#include "utils/Types.h"

using namespace std;

int main() {
    // Initialize all our core services
    users::UserManager userManager;
    banking::BankingManager bankingManager;
    flights::FlightManager flightManager;
    tickets::TicketManager ticketManager;

    // Load existing data from storage
    userManager.load();
    bankingManager.load();
    flightManager.load();
    ticketManager.load();

    // Set up the CLI interfaces
    users::UserCLI userCLI(userManager);
    banking::BankingCLI bankingCLI(bankingManager);
    flights::FlightsCLI flightsCLI(flightManager, ticketManager);
    tickets::TicketsCLI ticketsCLI(ticketManager, flightManager);

    // Handle user authentication
    string userId;
    utils::Role userRole = utils::Role::Passenger;

    if (!userCLI.welcomeFlow(userId, userRole)) {
        return 0;
    }

    // Main dashboard loop
    bool isRunning = true;
    while (isRunning) {
        cout << "\n==============================\n";
        cout << " airCLI Dashboard\n";
        cout << "==============================\n";
        cout << "1. Search & Book Flights\n";
        cout << "2. My Tickets\n";
        cout << "3. Travel History\n";
        cout << "4. Banking\n";
        
        if (userRole == utils::Role::Admin) {
            cout << "5. Admin: Manage Flights\n";
            cout << "6. Logout\n";
        } else {
            cout << "5. Logout\n";
        }
        
        cout << "\nSelect an option > ";

        int choice = 0;
        cin >> choice;

        switch (choice) {
            case 1:
            flightsCLI.runSearchAndBook(userId, userRole);
            break;
            case 2:
            ticketsCLI.runViewTickets(userId, userRole);
            break;
            case 3:
            ticketsCLI.runTravelHistory(userId, userRole);
            break;
            case 4:
            bankingCLI.runBanking(userId, userRole);
            break;
            case 5:
            if (userRole == utils::Role::Admin) {
                flightsCLI.run(userId, userRole);
            } else {
                cout << "\nLogging out...\n";
                isRunning = false;
            }
            break;
            case 6:
            if (userRole == utils::Role::Admin) {
                cout << "\nLogging out...\n";
                isRunning = false;
            } else {
                cout << "\nInvalid option. Please try again.\n";
            }
            break;
            default:
            cout << "\nInvalid option. Please try again.\n";
        }
    }

    cout << "\nThanks for using airCLI. Goodbye!\n";
    return 0;
}
