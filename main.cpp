#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>

#include "Transaction.h"
#include "BudgetManager.h"
#include "FileManager.h"

const std::string FILE_TRANSACTIONS = "transactions.csv";

std::string currentDate() {
    std::time_t t = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return buf;
}


void addTransaction(BudgetManager& manager, bool isExpense) {
    std::cout << (isExpense ? "| NEW EXPENSE |\n" : "| NEW INCOME |\n");

    Transaction t;
    t.date = currentDate();

    std::vector<std::string> categories = isExpense
        ? std::vector<std::string>{"food", "transport", "rent", "personal expenses", "loan payments", "other"}
        : std::vector<std::string>{"salary", "gifts", "freelance", "other"};

    std::cout << "  Categories:\n";

    for (int i = 0; i < (int)categories.size(); ++i) {
        std::cout << "      " << i + 1 << ".     " << categories[i] << "\n";
    }

    std::cout << "  Select a category (1 - " << categories.size() << "): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > (int)categories.size()) {
        std::cout << "  Invalid category selected.\n";
        return;
    }

    t.category = categories[choice - 1];

    std::cout << "  Enter a description: ";
    std::getline(std::cin, t.description);

    std::cout << "  Enter the amount: ";

    if (!(std::cin >> t.amount)) {
        std::cout << "  Invalid amount entered.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    t.amount = isExpense ? -std::abs(t.amount) : std::abs(t.amount);
    
    manager.addTransaction(t);

    std::cout << "  Transaction saved.\n";
}

void listTransactions(const BudgetManager& manager) {
    std::cout << " | ALL TRANSACTIONS | \n";

    const auto& transactions = manager.getTransactions();

    if (transactions.empty()) {
        std::cout << "  No transactions yet.\n";
        return;
    }

    std::cout << std::left
              << std::setw(12) << "Date"
              << std::setw(20) << "Category"
              << std::setw(22) << "Description"
              << std::right << std::setw(10) << "Amount" << '\n';

    for (const auto& t : transactions) {
        std::cout << std::left
                  << std::setw(12) << t.date
                  << std::setw(20) << t.category
                  << std::setw(22) << t.description.substr(0, 21)
                  << std::right << std::setw(10)
                  << std::fixed << std::setprecision(2)
                  << t.amount << '\n';
    }
}

void showBalance(const BudgetManager& manager) {
    std::cout << "  Current balance: "
              << std::fixed << std::setprecision(2)
              << manager.calculateBalance() << "\n";
}

void showSummary(const BudgetManager& manager) {
    std::cout << "  Current income: "
              << std::fixed << std::setprecision(2)
              << manager.calculateIncome() << "\n";

    std::cout << "  Current expenses: "
              << std::fixed << std::setprecision(2)
              << manager.calculateExpenses() << "\n";

}

void showCategorySummary(const BudgetManager& manager) {
    std::cout << "| CATEGORY SUMMARY |\n";

    const auto totals = manager.getCategoryTotals();

    if (totals.empty()) {
        std::cout << "  No transactions yet.\n";
        return;
    }

    std::string topExpenseCategory, topIncomeCategory;
    double topExpense = 0, topIncome = 0;

    std::cout << "\n  EXPENSES:\n";
    for (const auto& [category, total] : totals) {
        if (total < 0) {
            std::cout << "    " << std::left << std::setw(22) << category
                      << std::right << std::setw(10)
                      << std::fixed << std::setprecision(2)
                      << total << "\n";

            if (std::abs(total) > topExpense) {
                topExpense = std::abs(total);
                topExpenseCategory = category;
            }
        }
    }

    std::cout << "\n  INCOME:\n";
    for (const auto& [category, total] : totals) {
        if (total > 0) {
            std::cout << "    " << std::left << std::setw(22) << category
                      << std::right << std::setw(10)
                      << std::fixed << std::setprecision(2)
                      << total << "\n";

            if (total > topIncome) {
                topIncome = total;
                topIncomeCategory = category;
            }
        }
    }

    std::cout << "\n  --------------------------------\n";

    if (!topExpenseCategory.empty()) {
        std::cout << "  Most spent:   " << topExpenseCategory
                  << " (" << std::fixed << std::setprecision(2)
                  << topExpense << ")\n";
    }

    if (!topIncomeCategory.empty()) {
        std::cout << "  Most earned:  " << topIncomeCategory
                  << " (" << std::fixed << std::setprecision(2)
                  << topIncome << ")\n";
    }

}

void exportReport(const BudgetManager& manager) {
    std::string filename = "report_" + currentDate() + ".csv";

    FileManager::saveTransactions(filename, manager.getTransactions());

    std::cout << "  Report exported to: " << filename << '\n';
}

void clearAllData(BudgetManager& manager) {
    char answer;

    std::cout << "  Are you sure you want to delete all transactions? (y/n): ";
    std::cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        manager.clearTransactions();
        FileManager::saveTransactions(FILE_TRANSACTIONS, manager.getTransactions());
        std::cout << "  All transactions deleted.\n";
    } else {
        std::cout << "  Delete cancelled.\n";
    }
}

void listMenu() {
    std::cout << "      | FINANCIAL PLANNER | \n";
    std::cout << "  1. Add expense\n";
    std::cout << "  2. Add income\n";
    std::cout << "  3. List all transactions\n";
    std::cout << "  4. Export report to CSV\n";
    std::cout << "  5. Show balance\n";
    std::cout << "  6. Show income and expenses\n";
    std::cout << "  7. Show category summary\n";
    std::cout << "  8. Clear all transactions\n";
    std::cout << "  0. Save & exit\n";
    std::cout << "  Choice: ";
}

int main() {
    BudgetManager manager;

    std::vector<Transaction> loadedTransactions =
        FileManager::loadTransactions(FILE_TRANSACTIONS);

    for (const auto& t : loadedTransactions) {
        manager.addTransaction(t);
    }

    std::cout << "  Data loaded. "
              << manager.getTransactionCount()
              << " transaction(s) on record.\n";

    int choice = -1;

    while (choice != 0) {
        listMenu();
        
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Invalid input. Enter a number: ";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addTransaction(manager, true);
                break;
            case 2:
                addTransaction(manager, false);
                break;
            case 3:
                listTransactions(manager);
                break;
            case 4:
                exportReport(manager);
                break;
            case 5:
                showBalance(manager);
                break;
            case 6:
                showSummary(manager);
                break;
            case 7:
                showCategorySummary(manager);
                break;
            case 8:
                clearAllData(manager);
                break;
            case 0:
                choice = 0;
                break;
            default:
                std::cout << "  Unknown option.\n";
        }
    }

    FileManager::saveTransactions(FILE_TRANSACTIONS, manager.getTransactions());

    std::cout << "All data saved.";

    return 0;
}