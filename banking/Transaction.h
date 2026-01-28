#ifndef BANKING_TRANSACTION_H
#define BANKING_TRANSACTION_H

#include <string>
#include "../utils/Types.h"

using namespace std;

namespace banking {
    enum class TransactionType { 
        Credit = 0,  // Money added to account
        Debit = 1    // Money removed from account
    };

    class Transaction {
    private:
        utils::ID id;
        utils::ID accountId;
        long long amountCents;
        TransactionType type;
        string description;
        long long timestampSec;

    public:

        Transaction() : amountCents(0), type(TransactionType::Credit), timestampSec(0) {}

        Transaction(const utils::ID &transactionId, const utils::ID &accountId, 
                   long long amountCents, TransactionType type, 
                   const string &description, long long timestamp)
            : id(transactionId), accountId(accountId), amountCents(amountCents), 
              type(type), description(description), timestampSec(timestamp) {}

        const utils::ID &getId() const { return id; }
        const utils::ID &getAccountId() const { return accountId; }
        long long getAmountCents() const { return amountCents; }
        TransactionType getType() const { return type; }
        const string &getDescription() const { return description; }
        long long getTimestampSec() const { return timestampSec; }

        //Storage Utils
        string serialize() const;
        static Transaction deserialize(const string &line);
    };
}

#endif
