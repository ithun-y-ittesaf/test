#ifndef BANKING_BANKINGCLI_H
#define BANKING_BANKINGCLI_H

#include <string>
#include "BankingManager.h"
#include "../utils/Types.h"

namespace banking {
    /**
     * CLI interface for banking operations and account management.
     */
    class BankingCLI {
    private:
        BankingManager &manager;

    public:
        explicit BankingCLI(BankingManager &m) : manager(m) {}

        // Admin banking interface
        void run(const utils::ID &userId, utils::Role userRole);

        // User banking interface
        void runBanking(const utils::ID &userId, utils::Role userRole);
    };
}

#endif
