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

        void runBanking(const utils::ID &userId, utils::Role userRole);
    };
}

#endif
