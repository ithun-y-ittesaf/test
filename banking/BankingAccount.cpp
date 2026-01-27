#include "BankingAccount.h"
#include <sstream>

namespace banking {
    std::string BankingAccount::serialize() const {
        // Format: id|userId|balanceCents
        return id + "|" + userId + "|" + std::to_string(balanceCents);
    }

    BankingAccount BankingAccount::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, userId, balanceStr;
        
        // Parse pipe-delimited values
        std::getline(ss, id, '|');
        std::getline(ss, userId, '|');
        std::getline(ss, balanceStr, '|');
        
        // Convert balance to long long
        long long balance = 0;
        try {
            balance = std::stoll(balanceStr);
        } catch (...) {
            balance = 0;
        }
        
        return BankingAccount(id, userId, balance);
    }
}
