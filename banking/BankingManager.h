#ifndef BANKING_BANKINGMANAGER_H
#define BANKING_BANKINGMANAGER_H

#include <map>
#include <vector>
#include "BankingAccount.h"
#include "Transaction.h"

namespace banking {
    /**
     * Manages all banking operations in the system.
     * Handles accounts, transactions, deposits, and withdrawals.
     */
    class BankingManager {
    private:
        std::map<utils::ID, BankingAccount> accountsById;
        std::map<utils::ID, utils::ID> userToAccountId;

    public:
        // Load accounts and transactions from persistent storage
        bool load();

        // Save all accounts and transactions to persistent storage
        bool save() const;

        // Get or create a bank account for a user
        utils::ID getOrCreateAccountForUser(const utils::ID &userId);

        // Get account by ID
        const BankingAccount* getAccount(const utils::ID &accountId) const;

        // Get account associated with a user
        const BankingAccount* getAccountByUser(const utils::ID &userId) const;

        // Add money to an account
        utils::Result deposit(const utils::ID &accountId, long long amountCents, 
                            const std::string &description);

        // Remove money from an account
        utils::Result withdraw(const utils::ID &accountId, long long amountCents, 
                             const std::string &description);

        // Get all transactions for an account
        std::vector<Transaction> getTransactionsForAccount(const utils::ID &accountId) const;
    };
}

#endif
