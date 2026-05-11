#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>

#include "Transaction.h"
#include "BudgetManager.h"
#include "FileManager.h"
#include "ReportGenerator.h"

const std::string FILE_TRANSACTIONS = "transactions.csv";

std::string currentDate() {
    std::time_t t = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return buf;
}

void addTransaction(BudgetManager& manager) {
    std::cout << "| NEW TRANSACTION |\n";

    Transaction t;
    t.date = currentDate();

    std::vector<std::string> categories = {
        "food",
        "transport",
        "rent",
        "income",
        "personal expenses",
        "loan payments",
        "other"
    };

    std::cout << "  Categories:\n";

    for (int i = 0; i < (int)categories.size(); ++i) {
        std::cout << "      " << i + 1 << ".     " << categories[i] << "\n";
    }

    std::cout << "  Select a category (1 - " << categories.size() << "): ";

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > categories.size()) {
        std::cout << "  Invalid category selected.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    t.category = categories[choice - 1];

    std::cout << "  Enter a description: ";
    std::getline(std::cin, t.description);

    std::cout << "  Enter the amount (positive = income, negative = expense): ";

    if (!(std::cin >> t.amount)) {
        std::cout << "  Invalid amount entered.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

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

void exportReport(const BudgetManager& manager) {
    std::string filename = "report_" + currentDate() + ".csv";

    ReportGenerator::exportReport(filename, manager.getTransactions());

    std::cout << "  Report exported to: " << filename << '\n';
}

void listMenu() {
    std::cout << "      | FINANCIAL PLANNER | \n";
    std::cout << "  1. Add transaction\n";
    std::cout << "  2. List all transactions\n";
    std::cout << "  3. Export report to CSV\n";
    std::cout << "  4. Show balance\n";
    std::cout << "  5. Show income and expenses\n";
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
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTransaction(manager);
                break;
            case 2:
                listTransactions(manager);
                break;
            case 3:
                exportReport(manager);
                break;
            case 4:
                showBalance(manager);
                break;
            case 5:
                showSummary(manager);
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