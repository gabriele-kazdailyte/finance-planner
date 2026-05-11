#include "BudgetManager.h"

void BudgetManager::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

const std::vector<Transaction>& BudgetManager::getTransactions() const {
    return transactions;
}

double BudgetManager::calculateBalance() const {
    double sum = 0.0;

    for (const auto& t : transactions) {
        sum += t.amount;
    }

    return sum;
}

int BudgetManager::getTransactionCount() const {
    return transactions.size();
}