#include "Transaction.h"
#include <sstream>

namespace banking {
    std::string Transaction::serialize() const {
        return id + "|" + accountId + "|" + std::to_string(amountCents) + "|" +
               std::to_string(static_cast<int>(type)) + "|" + description + "|" +
               std::to_string(timestampSec);
    }

    Transaction Transaction::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, accId, amtStr, typeStr, desc, tsStr;
        std::getline(ss, id, '|');
        std::getline(ss, accId, '|');
        std::getline(ss, amtStr, '|');
        std::getline(ss, typeStr, '|');
        std::getline(ss, desc, '|');
        std::getline(ss, tsStr, '|');
        long long amt = 0, ts = 0; int t = 0;
        try { amt = std::stoll(amtStr); } catch (...) { amt = 0; }
        try { t = std::stoi(typeStr); } catch (...) { t = 0; }
        try { ts = std::stoll(tsStr); } catch (...) { ts = 0; }
        return Transaction(id, accId, amt, static_cast<TransactionType>(t), desc, ts);
    }
}
