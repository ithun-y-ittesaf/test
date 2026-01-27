#ifndef BANKING_TRANSACTION_H
#define BANKING_TRANSACTION_H

#include <string>
#include "../utils/Types.h"

namespace banking {
    enum class TransactionType { Credit = 0, Debit = 1 };

    class Transaction {
    private:
        utils::ID id;
        utils::ID accountId;
        long long amountCents;
        TransactionType type;
        std::string description;
        long long timestampSec;
    public:
        Transaction() : amountCents(0), type(TransactionType::Credit), timestampSec(0) {}
        Transaction(const utils::ID &id, const utils::ID &accId, long long amountCents,
                    TransactionType type, const std::string &desc, long long ts)
            : id(id), accountId(accId), amountCents(amountCents), type(type), description(desc), timestampSec(ts) {}

        const utils::ID &getId() const { return id; }
        const utils::ID &getAccountId() const { return accountId; }
        long long getAmountCents() const { return amountCents; }
        TransactionType getType() const { return type; }
        const std::string &getDescription() const { return description; }
        long long getTimestampSec() const { return timestampSec; }

        std::string serialize() const;
        static Transaction deserialize(const std::string &line);
    };
}

#endif 
