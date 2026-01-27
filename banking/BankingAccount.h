#ifndef BANKING_BANKINGACCOUNT_H
#define BANKING_BANKINGACCOUNT_H

#include <string>
#include "../utils/Types.h"

namespace banking {
    class BankingAccount {
    private:
        utils::ID id;
        utils::ID userId;
        long long balanceCents;
    public:
        BankingAccount() : balanceCents(0) {}
        BankingAccount(const utils::ID &id, const utils::ID &userId, long long balanceCents)
            : id(id), userId(userId), balanceCents(balanceCents) {}

        const utils::ID &getId() const { return id; }
        const utils::ID &getUserId() const { return userId; }
        long long getBalanceCents() const { return balanceCents; }
        void setBalanceCents(long long v) { balanceCents = v; }

        std::string serialize() const;
        static BankingAccount deserialize(const std::string &line);
    };
}

#endif 
