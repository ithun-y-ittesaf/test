#ifndef BANKING_BANKINGACCOUNT_H
#define BANKING_BANKINGACCOUNT_H

#include <string>
#include "../utils/Types.h"

using namespace std;

namespace banking {
    
    class BankingAccount {
    private:
        utils::ID id;
        utils::ID userId;
        long long balanceCents;

    public:

        BankingAccount() : balanceCents(0) {}

        BankingAccount(const utils::ID &accountId, const utils::ID &accountUserId, 
                      long long accountBalanceCents)
            : id(accountId), userId(accountUserId), balanceCents(accountBalanceCents) {}

        const utils::ID &getId() const { return id; }
        const utils::ID &getUserId() const { return userId; }
        long long getBalanceCents() const { return balanceCents; }

        void setBalanceCents(long long newBalance) { balanceCents = newBalance; }

        string serialize() const;
        static BankingAccount deserialize(const string &line);
    };
}

#endif
