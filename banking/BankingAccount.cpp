#include "BankingAccount.h"
#include <sstream>

namespace banking {
    std::string BankingAccount::serialize() const {
        return id + "|" + userId + "|" + std::to_string(balanceCents);
    }

    BankingAccount BankingAccount::deserialize(const std::string &line) {
        std::stringstream ss(line);
        std::string id, userId, balStr;
        std::getline(ss, id, '|');
        std::getline(ss, userId, '|');
        std::getline(ss, balStr, '|');
        long long bal = 0;
        try { bal = std::stoll(balStr); } catch (...) { bal = 0; }
        return BankingAccount(id, userId, bal);
    }
}
