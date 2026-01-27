#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

g++ -std=c++17 -Wall -Wextra -Werror \
  main.cpp \
  users/User.cpp users/UserManager.cpp users/UserCLI.cpp \
  banking/BankingAccount.cpp banking/Transaction.cpp banking/BankingManager.cpp banking/BankingCLI.cpp \
  flights/Flight.cpp flights/FlightManager.cpp flights/FlightsCLI.cpp \
  tickets/Ticket.cpp tickets/TicketManager.cpp tickets/TicketsCLI.cpp \
  access/AccessControl.cpp storage/DataStorage.cpp logging/Logger.cpp \
  -I. -o aircli

echo "Built ./aircli successfully."
