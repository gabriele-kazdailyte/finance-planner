#include "BudgetManager.h"
#include <cmath>

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

double BudgetManager::calculateIncome() const {
    double income = 0.0;

    for (const auto& t : transactions) {
        if (t.amount > 0) {
            income += t.amount;
        }
    }

    return income;
}

double BudgetManager::calculateExpenses() const {
    double expenses = 0.0;

    for (const auto& t : transactions) {
        if (t.amount < 0) {
            expenses += std::abs(t.amount);
        }
    }

    return expenses;
}

std::map<std::string, double> BudgetManager::getCategoryTotals() const {
    
    std::map<std::string, double> totals;

    for (const auto& t : transactions) {
        totals[t.category] += t.amount;
    }
    
    return totals;
}

void BudgetManager::clearTransactions() {
    transactions.clear();
}