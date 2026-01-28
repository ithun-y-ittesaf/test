#ifndef BANKING_BANKINGMANAGER_H
#define BANKING_BANKINGMANAGER_H

#include <map>
#include <vector>
#include "BankingAccount.h"
#include "Transaction.h"

using namespace std;

namespace banking {
    
    class BankingManager {
    private:
        map<utils::ID, BankingAccount> accountsById;
        map<utils::ID, utils::ID> userToAccountId;

    public:

        bool load();

        bool save() const;

        utils::ID getOrCreateAccountForUser(const utils::ID &userId);

        const BankingAccount* getAccount(const utils::ID &accountId) const;

        const BankingAccount* getAccountByUser(const utils::ID &userId) const;

        utils::Result deposit(const utils::ID &accountId, long long amountCents, 
                            const string &description);

        utils::Result withdraw(const utils::ID &accountId, long long amountCents, 
                             const string &description);

        vector<Transaction> getTransactionsForAccount(const utils::ID &accountId) const;
    };
}

#endif
