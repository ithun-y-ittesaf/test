#ifndef BANKING_TRANSACTION_H
#define BANKING_TRANSACTION_H

#include <string>
#include "../utils/Types.h"

namespace banking {
    enum class TransactionType { 
        Credit = 0,  // Money added to account
        Debit = 1    // Money removed from account
    };

    /**
     * Represents a single transaction in a bank account.
     * Tracks deposits, withdrawals, and other account activities.
     */
    class Transaction {
    private:
        utils::ID id;
        utils::ID accountId;
        long long amountCents;
        TransactionType type;
        std::string description;
        long long timestampSec;

    public:
        // Default constructor for empty transaction
        Transaction() : amountCents(0), type(TransactionType::Credit), timestampSec(0) {}

        // Full constructor with transaction details
        Transaction(const utils::ID &transactionId, const utils::ID &accountId, 
                   long long amountCents, TransactionType type, 
                   const std::string &description, long long timestamp)
            : id(transactionId), accountId(accountId), amountCents(amountCents), 
              type(type), description(description), timestampSec(timestamp) {}

        // Getters for all transaction properties
        const utils::ID &getId() const { return id; }
        const utils::ID &getAccountId() const { return accountId; }
        long long getAmountCents() const { return amountCents; }
        TransactionType getType() const { return type; }
        const std::string &getDescription() const { return description; }
        long long getTimestampSec() const { return timestampSec; }

        // Serialization for storage
        std::string serialize() const;
        static Transaction deserialize(const std::string &line);
    };
}

#endif
