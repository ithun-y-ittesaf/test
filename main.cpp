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

int main() {
    users::UserManager userManager;
    banking::BankingManager bankingManager;
    flights::FlightManager flightManager;
    tickets::TicketManager ticketManager;

    // load persisted data
    userManager.load();
    bankingManager.load();
    flightManager.load();
    ticketManager.load();

    users::UserCLI userCLI(userManager);
    banking::BankingCLI bankingCLI(bankingManager);
    flights::FlightsCLI flightsCLI(flightManager, ticketManager);
    tickets::TicketsCLI ticketsCLI(ticketManager, flightManager);

    std::string currentUserId;
    utils::Role currentRole = utils::Role::Passenger;

    if (!userCLI.welcomeFlow(currentUserId, currentRole)) {
        return 0; // user chose to exit
    }

    bool running = true;
    while (running) {
        std::cout << "\n==============================\n";
        std::cout << " airCLI Lite Dashboard\n";
        std::cout << "==============================\n";
        std::cout << "1. Search & Book Flights\n";
        std::cout << "2. My Tickets\n";
        std::cout << "3. Travel History\n";
        std::cout << "4. Banking\n";
        if (currentRole == utils::Role::Admin) {
            std::cout << "5. Admin: Manage Flights\n";
            std::cout << "6. Logout\n";
        } else {
            std::cout << "5. Logout\n";
        }
        std::cout << "\nSelect an option > ";

        int choice = 0;
        std::cin >> choice;

        if (choice == 1) {
            flightsCLI.runSearchAndBook(currentUserId, currentRole);
        } else if (choice == 2) {
            ticketsCLI.runViewTickets(currentUserId, currentRole);
        } else if (choice == 3) {
            ticketsCLI.runTravelHistory(currentUserId, currentRole);
        } else if (choice == 4) {
            bankingCLI.runBanking(currentUserId, currentRole);
        } else if (choice == 5 && currentRole == utils::Role::Admin) {
            flightsCLI.run(currentUserId, currentRole);
        } else if ((choice == 5 && currentRole != utils::Role::Admin) ||
                   (choice == 6 && currentRole == utils::Role::Admin)) {
            std::cout << "\nLogging out...\n";
            running = false;
        } else {
            std::cout << "\nInvalid option.\n";
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
