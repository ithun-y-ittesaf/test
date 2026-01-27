#include "BankingCLI.h"
#include "../access/AccessControl.h"
#include <iostream>
#include <iomanip>

namespace banking {
    // Helper function to convert BDT to cents
    static long long toCents(long long amount) {
        return amount * 100;
    }

    // Helper function to format balance for display
    static void printFormattedBalance(long long cents) {
        long long taka = cents / 100;
        long long paisa = cents % 100;
        std::cout << "BDT " << taka << "." << std::setfill('0') << std::setw(2) << paisa;
    }

    void BankingCLI::runBanking(const utils::ID &userId, utils::Role userRole) {
        manager.load();
        auto accountId = manager.getOrCreateAccountForUser(userId);
        
        std::cout << "\n--- Banking Services ---\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Funds\n";
        std::cout << "3. Withdraw Funds\n";
        std::cout << "4. View Transactions\n";
        std::cout << "5. Back\n";
        std::cout << "Choice: ";
        
        int choice = 0;
        std::cin >> choice;
        
        if (choice == 1) {
            // View balance
            auto account = manager.getAccount(accountId);
            long long balance = account ? account->getBalanceCents() : 0;
            std::cout << "\nCurrent Balance: ";
            printFormattedBalance(balance);
            std::cout << "\n";
        } else if (choice == 2) {
            // Deposit funds
            if (!access::AccessControl::anyOf(userRole, {utils::Role::Passenger, utils::Role::Admin})) {
                std::cout << "\nAccess denied.\n";
                return;
            }
            
            std::cout << "\nEnter amount to deposit (BDT): ";
            long long amount;
            std::cin >> amount;
            
            auto result = manager.deposit(accountId, toCents(amount), "Manual deposit");
            if (result.ok) {
                std::cout << "\n✓ Deposit successful.\n";
            } else {
                std::cout << "\n" << result.message << "\n";
            }
        } else if (choice == 3) {
            // Withdraw funds
            if (!access::AccessControl::anyOf(userRole, {utils::Role::Passenger, utils::Role::Admin})) {
                std::cout << "\nAccess denied.\n";
                return;
            }
            
            std::cout << "\nEnter amount to withdraw (BDT): ";
            long long amount;
            std::cin >> amount;
            
            auto result = manager.withdraw(accountId, toCents(amount), "Manual withdrawal");
            if (result.ok) {
                std::cout << "\n✓ Withdrawal successful.\n";
            } else {
                std::cout << "\n" << result.message << "\n";
            }
        } else if (choice == 4) {
            // View transactions
            auto transactions = manager.getTransactionsForAccount(accountId);
            
            if (transactions.empty()) {
                std::cout << "\nNo transactions yet.\n";
            } else {
                std::cout << "\nTransaction History:\n";
                for (const auto &transaction : transactions) {
                    std::string typeLabel = (transaction.getType() == TransactionType::Credit) ? "+" : "-";
                    std::cout << typeLabel << " ";
                    printFormattedBalance(transaction.getAmountCents());
                    std::cout << " | " << transaction.getDescription() << "\n";
                }
            }
        }
    }

//     void BankingCLI::runBanking(const utils::ID &userId, utils::Role userRole) {
//         manager.load();
//         auto accountId = manager.getOrCreateAccountForUser(userId);
        
//         std::cout << "\n========== Your Account ==========\n\n";
        
//         auto account = manager.getAccount(accountId);
//         long long balance = account ? account->getBalanceCents() : 0;
        
//         std::cout << "Current Balance : ";
//         printFormattedBalance(balance);
//         std::cout << "\n\n";
        
//         std::cout << "1. View Transaction History\n";
//         std::cout << "2. Add Funds to Account\n";
//         std::cout << "0. Back\n";
//         std::cout << "\nSelect an option > ";
        
//         int choice = 0;
//         std::cin >> choice;
        
//         if (choice == 1) {
//             // View transaction history
//             auto transactions = manager.getTransactionsForAccount(accountId);
            
//             if (transactions.empty()) {
//                 std::cout << "\nNo transactions found.\n";
//             } else {
//                 std::cout << "\n--- Recent Transactions ---\n";
//                 for (const auto &transaction : transactions) {
//                     std::string sign = (transaction.getType() == TransactionType::Credit) ? "+" : "-";
//                     std::cout << sign << " ";
//                     printFormattedBalance(transaction.getAmountCents());
//                     std::cout << " | " << transaction.getDescription() << "\n";
//                 }
//             }
//         } else if (choice == 2) {
//             // Add funds
//             if (!access::AccessControl::anyOf(userRole, {utils::Role::Passenger, utils::Role::Admin})) {
//                 std::cout << "\nAccess denied.\n";
//                 return;
//             }
            
//             std::cout << "\nEnter amount to add (BDT): ";
//             long long amount;
//             std::cin >> amount;
            
//             auto result = manager.deposit(accountId, toCents(amount), "User deposit");
//             if (result.ok) {
//                 std::cout << "\n✓ Funds added successfully.\n";
//             } else {
//                 std::cout << "\n" << result.message << "\n";
//             }
//         }
//     }
}
