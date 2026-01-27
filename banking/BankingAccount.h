#ifndef BANKING_BANKINGACCOUNT_H
#define BANKING_BANKINGACCOUNT_H

#include <string>
#include "../utils/Types.h"

namespace banking {
    /**
     * Represents a user's bank account in the system.
     * Tracks account balance and user association.
     */
    class BankingAccount {
    private:
        utils::ID id;
        utils::ID userId;
        long long balanceCents;

    public:
        // Default constructor for empty account
        BankingAccount() : balanceCents(0) {}

        // Full constructor with account details
        BankingAccount(const utils::ID &accountId, const utils::ID &accountUserId, 
                      long long accountBalanceCents)
            : id(accountId), userId(accountUserId), balanceCents(accountBalanceCents) {}

        // Getters for account properties
        const utils::ID &getId() const { return id; }
        const utils::ID &getUserId() const { return userId; }
        long long getBalanceCents() const { return balanceCents; }

        // Update account balance
        void setBalanceCents(long long newBalance) { balanceCents = newBalance; }

        // Serialization for storage
        std::string serialize() const;
        static BankingAccount deserialize(const std::string &line);
    };
}

#endif
