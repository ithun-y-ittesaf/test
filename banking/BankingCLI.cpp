#include "BankingCLI.h"
#include "../access/AccessControl.h"
#include <iostream>
#include <iomanip>

namespace banking {
    static long long dollarsToCents(long long dollars) { return dollars * 100; }

    void BankingCLI::run(const utils::ID &currentUserId, utils::Role currentRole) {
        manager.load();
        auto accId = manager.getOrCreateAccountForUser(currentUserId);
        std::cout << "\n-- Banking --\n";
        std::cout << "1) View Balance\n2) Deposit\n3) Withdraw\n4) View Transactions\n5) Back\nChoice: ";
        int ch = 0; std::cin >> ch;
        if (ch == 1) {
            auto acc = manager.getAccount(accId);
            long long cents = acc ? acc->getBalanceCents() : 0;
            std::cout << "Balance: $" << (cents/100) << "." << (cents%100) << "\n";
        } else if (ch == 2) {
            if (!access::AccessControl::anyOf(currentRole, {utils::Role::Passenger, utils::Role::Admin})) {
                std::cout << "Access denied.\n"; return;
            }
            std::cout << "Amount (whole dollars): ";
            long long amt; std::cin >> amt;
            auto res = manager.deposit(accId, dollarsToCents(amt), "User deposit");
            std::cout << (res.ok ? "OK: " : "ERR: ") << res.message << "\n";
        } else if (ch == 3) {
            if (!access::AccessControl::anyOf(currentRole, {utils::Role::Passenger, utils::Role::Admin})) {
                std::cout << "Access denied.\n"; return;
            }
            std::cout << "Amount (whole dollars): ";
            long long amt; std::cin >> amt;
            auto res = manager.withdraw(accId, dollarsToCents(amt), "User withdraw");
            std::cout << (res.ok ? "OK: " : "ERR: ") << res.message << "\n";
        } else if (ch == 4) {
            auto txs = manager.getTransactionsForAccount(accId);
            std::cout << "Transactions (" << txs.size() << "):\n";
            for (const auto &t : txs) {
                std::cout << "- " << (t.getType()==TransactionType::Credit?"CREDIT":"DEBIT")
                          << " $" << (t.getAmountCents()/100) << "." << (t.getAmountCents()%100)
                          << " | " << t.getDescription() << "\n";
            }
        }
    }

    void BankingCLI::runBanking(const utils::ID &currentUserId, utils::Role currentRole) {
        manager.load();
        auto accId = manager.getOrCreateAccountForUser(currentUserId);
        
        std::cout << "\n========== Banking ==========" << "\n";
        
        auto acc = manager.getAccount(accId);
        long long cents = acc ? acc->getBalanceCents() : 0;
        long long dollars = cents / 100;
        long long paise = (cents % 100);
        
        std::cout << "Balance       : BDT " << dollars << "," << std::setfill('0') << std::setw(2) << paise << "\n\n";
        std::cout << "1. View Transactions\n";
        std::cout << "2. Add Funds (Simulated)\n";
        std::cout << "0. Back\n";
        std::cout << "\nSelect an option > ";
        
        int choice = 0;
        std::cin >> choice;
        
        if (choice == 1) {
            auto txs = manager.getTransactionsForAccount(accId);
            if (txs.empty()) {
                std::cout << "\nNo transactions.\n";
            } else {
                std::cout << "\nRecent Transactions:\n";
                for (const auto &t : txs) {
                    long long amt = t.getAmountCents() / 100;
                    std::cout << (t.getType()==TransactionType::Credit?" + ": " - ")
                              << "BDT " << amt << " | " << t.getDescription() << "\n";
                }
            }
        } else if (choice == 2) {
            if (!access::AccessControl::anyOf(currentRole, {utils::Role::Passenger, utils::Role::Admin})) {
                std::cout << "\nAccess denied.\n";
                return;
            }
            std::cout << "\nEnter amount (BDT) to add : ";
            long long amt;
            std::cin >> amt;
            
            auto res = manager.deposit(accId, dollarsToCents(amt), "User deposit");
            if (res.ok) {
                std::cout << "\n✅ Deposit successful.\n";
            } else {
                std::cout << "\n❌ " << res.message << "\n";
            }
        }
    }
}
