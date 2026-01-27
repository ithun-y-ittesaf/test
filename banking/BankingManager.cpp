#include "BankingManager.h"
#include "../storage/DataStorage.h"
#include "../logging/Logger.h"
#include <chrono>

namespace banking {
    bool BankingManager::load() {
        accountsById.clear();
        userToAccountId.clear();
        auto lines = storage::DataStorage::readAll("accounts.txt");
        for (const auto &l : lines) {
            if (l.empty()) continue;
            BankingAccount acc = BankingAccount::deserialize(l);
            accountsById[acc.getId()] = acc;
            userToAccountId[acc.getUserId()] = acc.getId();
        }
        return true;
    }

    bool BankingManager::save() const {
        std::vector<std::string> lines;
        lines.reserve(accountsById.size());
        for (const auto &p : accountsById) {
            lines.push_back(p.second.serialize());
        }
        return storage::DataStorage::writeAll("accounts.txt", lines);
    }

    utils::ID BankingManager::getOrCreateAccountForUser(const utils::ID &userId) {
        auto it = userToAccountId.find(userId);
        if (it != userToAccountId.end()) return it->second;
        using namespace std::chrono;
        auto ts = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID id = "A" + std::to_string(ts);
        while (accountsById.find(id) != accountsById.end()) { ++ts; id = "A" + std::to_string(ts); }
        BankingAccount acc(id, userId, 0);
        accountsById[id] = acc;
        userToAccountId[userId] = id;
        storage::DataStorage::appendLine("accounts.txt", acc.serialize());
        return id;
    }

    const BankingAccount* BankingManager::getAccount(const utils::ID &accountId) const {
        auto it = accountsById.find(accountId);
        if (it == accountsById.end()) return nullptr;
        return &it->second;
    }

    const BankingAccount* BankingManager::getAccountByUser(const utils::ID &userId) const {
        auto it = userToAccountId.find(userId);
        if (it == userToAccountId.end()) return nullptr;
        return getAccount(it->second);
    }

    std::vector<Transaction> BankingManager::getTransactionsForAccount(const utils::ID &accountId) const {
        std::vector<Transaction> out;
        auto lines = storage::DataStorage::readAll("transactions.txt");
        for (const auto &l : lines) {
            if (l.empty()) continue;
            Transaction t = Transaction::deserialize(l);
            if (t.getAccountId() == accountId) out.push_back(t);
        }
        return out;
    }

    utils::Result BankingManager::deposit(const utils::ID &accountId, long long amountCents, const std::string &desc) {
        if (amountCents <= 0) return utils::Result::Err("Invalid deposit amount");
        auto it = accountsById.find(accountId);
        if (it == accountsById.end()) return utils::Result::Err("Account not found");
        long long newBal = it->second.getBalanceCents() + amountCents;
        it->second.setBalanceCents(newBal);
        save();
        using namespace std::chrono;
        auto ts = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID tid = "T" + std::to_string(ts);
        Transaction tx(tid, accountId, amountCents, TransactionType::Credit, desc, ts);
        storage::DataStorage::appendLine("transactions.txt", tx.serialize());
        logging::Logger::logCritical("Payment", "ACC=" + accountId + "|CREDIT=" + std::to_string(amountCents));
        return utils::Result::Ok("Deposit successful");
    }

    utils::Result BankingManager::withdraw(const utils::ID &accountId, long long amountCents, const std::string &desc) {
        if (amountCents <= 0) return utils::Result::Err("Invalid withdraw amount");
        auto it = accountsById.find(accountId);
        if (it == accountsById.end()) return utils::Result::Err("Account not found");
        if (it->second.getBalanceCents() < amountCents) return utils::Result::Err("Insufficient funds");
        long long newBal = it->second.getBalanceCents() - amountCents;
        it->second.setBalanceCents(newBal);
        save();
        using namespace std::chrono;
        auto ts = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        utils::ID tid = "T" + std::to_string(ts);
        Transaction tx(tid, accountId, amountCents, TransactionType::Debit, desc, ts);
        storage::DataStorage::appendLine("transactions.txt", tx.serialize());
        logging::Logger::logCritical("Payment", "ACC=" + accountId + "|DEBIT=" + std::to_string(amountCents));
        return utils::Result::Ok("Withdraw successful");
    }
}
