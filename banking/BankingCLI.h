#ifndef BANKING_BANKINGCLI_H
#define BANKING_BANKINGCLI_H

#include <string>
#include "BankingManager.h"
#include "../utils/Types.h"

namespace banking {
    class BankingCLI {
    private:
        BankingManager &manager;
    public:
        explicit BankingCLI(BankingManager &m) : manager(m) {}
        void run(const utils::ID &currentUserId, utils::Role currentRole);
        void runBanking(const utils::ID &currentUserId, utils::Role currentRole);
    };
}

#endif 
