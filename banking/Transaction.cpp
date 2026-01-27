#include "Transaction.h"
#include <sstream>

namespace banking {
    std::string Transaction::serialize() const {
        // Format: id|accountId|amountCents|type|description|timestampSec
        return id + "|" + accountId + "|" + std::to_string(amountCents) + "|" +
               std::to_string(static_cast<int>(type)) + "|" + description + "|" +
               std::to_string(timestampSec);
    }

    Transaction Transaction::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, accountId, amountStr, typeStr, description, timestampStr;
        
        // Parse pipe-delimited values
        std::getline(ss, id, '|');
        std::getline(ss, accountId, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, typeStr, '|');
        std::getline(ss, description, '|');
        std::getline(ss, timestampStr, '|');
        
        // Convert values to appropriate types
        long long amount = 0, timestamp = 0;
        int typeValue = 0;
        
        try { amount = std::stoll(amountStr); } catch (...) { amount = 0; }
        try { typeValue = std::stoi(typeStr); } catch (...) { typeValue = 0; }
        try { timestamp = std::stoll(timestampStr); } catch (...) { timestamp = 0; }
        
        return Transaction(id, accountId, amount, static_cast<TransactionType>(typeValue), 
                         description, timestamp);
    }
}
