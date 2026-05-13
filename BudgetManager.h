#ifndef BUDGET_MANAGER_H
#define BUDGET_MANAGER_H

#include <vector>
#include<map>
#include "Transaction.h"

class BudgetManager {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& transaction);
    const std::vector<Transaction>& getTransactions() const;
    double calculateBalance() const;
    int getTransactionCount() const;
    double calculateIncome() const;
    double calculateExpenses() const;
    std::map<std::string, double> getCategoryTotals() const;
    void clearTransactions();
};

#endif