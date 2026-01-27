#ifndef BANKING_BANKINGMANAGER_H
#define BANKING_BANKINGMANAGER_H

#include <map>
#include <vector>
#include "BankingAccount.h"
#include "Transaction.h"

namespace banking {
    class BankingManager {
    private:
        std::map<utils::ID, BankingAccount> accountsById;
        std::map<utils::ID, utils::ID> userToAccountId;
    public:
        bool load();
        bool save() const;

        utils::ID getOrCreateAccountForUser(const utils::ID &userId);
        const BankingAccount* getAccount(const utils::ID &accountId) const;
        const BankingAccount* getAccountByUser(const utils::ID &userId) const;

        utils::Result deposit(const utils::ID &accountId, long long amountCents, const std::string &desc);
        utils::Result withdraw(const utils::ID &accountId, long long amountCents, const std::string &desc);

        std::vector<Transaction> getTransactionsForAccount(const utils::ID &accountId) const;
    };
}

#endif 
