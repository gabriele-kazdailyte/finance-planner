#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>
#include <sstream>

#include "Transaction.h"
#include "BudgetManager.h"
#include "FileManager.h"

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define CYAN        "\033[36m"
#define WHITE       "\033[97m"
#define BG_DARK     "\033[48;5;234m"

const std::string FILE_TRANSACTIONS = "transactions.csv";

std::string currentDate() {
    std::time_t t = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return buf;
}

void printLine(const std::string& color = DIM, char c = '-', int len = 50) {
    std::cout << color << std::string(len, c) << RESET << "\n";
}

void printHeader(const std::string& title) {
    std::cout << "\n" << BLUE << BOLD;
    std::cout << "  ╔══════════════════════════════════════════════╗\n";
    std::cout << "  ║  " << WHITE << std::left << std::setw(44) << title << BLUE << "║\n";
    std::cout << "  ╚══════════════════════════════════════════════╝\n";
    std::cout << RESET;
}

void printSuccess(const std::string& msg) {
    std::cout << GREEN << "  ✔  " << msg << RESET << "\n";
}

void printError(const std::string& msg) {
    std::cout << RED << "  ✖  " << msg << RESET << "\n";
}

void printWarning(const std::string& msg) {
    std::cout << YELLOW << "  ⚠  " << msg << RESET << "\n";
}


void addTransaction(BudgetManager& manager, bool isExpense) {
    printHeader(isExpense ? "NEW EXPENSE" : "NEW INCOME");

    Transaction t;
    t.date = currentDate();

    std::vector<std::string> categories = isExpense
        ? std::vector<std::string>{"food", "transport", "rent", "personal expenses", "loan payments", "other"}
        : std::vector<std::string>{"salary", "gifts", "freelance", "other"};

    std::cout << "\n" << DIM << "  Categories:\n" << RESET;

    for (int i = 0; i < (int)categories.size(); ++i)
        std::cout << "    " << CYAN << BOLD << (i+1) << RESET << "  " << WHITE << categories[i] << "\n" << RESET;

    std::cout << "  Select a category (1 - " << categories.size() << "): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > (int)categories.size()) {
        printError("Invalid category selected.");
        return;
    }

    t.category = categories[choice - 1];

    std::cout << "  Enter a description: ";
    std::getline(std::cin, t.description);

    std::cout << "  Enter the amount: ";

    if (!(std::cin >> t.amount)) {
        printError("Invalid amount entered.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    t.amount = isExpense ? -std::abs(t.amount) : std::abs(t.amount);
    
    manager.addTransaction(t);

    printSuccess("Transaction saved.");
}

void listTransactions(const BudgetManager& manager) {
    printHeader("ALL TRANSACTIONS");

    const auto& transactions = manager.getTransactions();

    if (transactions.empty()) {
        std::cout << "  No transactions yet.\n";
        return;
    }

    std::cout << "\n" << DIM << "  " << std::left
          << std::setw(12) << "Date"
          << std::setw(20) << "Category"
          << std::setw(22) << "Description"
          << std::right << std::setw(10) << "Amount"
          << "\n" << RESET;
    printLine(DIM, '-', 66);

    for (const auto& t : transactions) {
        std::string amtColor = (t.amount >= 0) ? GREEN : RED;
        std::string sign     = (t.amount >= 0) ? "+" : "";

        std::ostringstream amtStream;
        amtStream << sign << std::fixed << std::setprecision(2) << t.amount;
        std::string amtStr = amtStream.str();

        std::cout << "  ";
        std::cout << std::left << std::setw(14) << t.date;
        std::cout << std::left << std::setw(20) << t.category;
        std::cout << std::left << std::setw(24) << t.description.substr(0, 23);
        std::cout << amtColor << BOLD << std::right << std::setw(10) << amtStr << RESET << "\n";
    }
}

void showBalance(const BudgetManager& manager) {
    printHeader("BALANCE");

    double balance = manager.calculateBalance();
    std::string balColor = (balance >= 0) ? GREEN : RED;
    std::string balSign  = (balance >= 0) ? "+" : "";

    std::cout << "\n  " << balColor << BOLD
              << balSign << std::fixed << std::setprecision(2) << balance
              << " EUR" << RESET << "\n\n";
}

void showSummary(const BudgetManager& manager) {
    printHeader("INCOME & EXPENSES");

    std::cout << "\n  " << DIM << "Income:   " << RESET
              << GREEN << BOLD << "+" << std::fixed << std::setprecision(2)
              << manager.calculateIncome() << " EUR" << RESET << "\n";

    std::cout << "  " << DIM << "Expenses: " << RESET
              << RED << BOLD << "-" << std::fixed << std::setprecision(2)
              << manager.calculateExpenses() << " EUR" << RESET << "\n\n";
}

void showCategorySummary(const BudgetManager& manager) {
    printHeader("CATEGORY SUMMARY");

    const auto totals = manager.getCategoryTotals();

    if (totals.empty()) {
        printWarning("No transactions yet.");
        return;
    }

    std::string topExpenseCategory, topIncomeCategory;
    double topExpense = 0, topIncome = 0;

    std::cout << "\n  " << RED << BOLD << "EXPENSES:\n" << RESET;
    for (const auto& [category, total] : totals) {
        if (total < 0) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << total;
            std::string totalStr = oss.str();

            std::cout << "    " << std::left << std::setw(22) << category
                      << RED << std::right << std::setw(10) << totalStr << RESET << "\n";

            if (std::abs(total) > topExpense) {
                topExpense = std::abs(total);
                topExpenseCategory = category;
            }
        }
    }

    std::cout << "\n  " << GREEN << BOLD << "INCOME:\n" << RESET;
    for (const auto& [category, total] : totals) {
        if (total > 0) {
            std::ostringstream oss;
            oss << "+" << std::fixed << std::setprecision(2) << total;
            std::string totalStr = oss.str();

            std::cout << "    " << std::left << std::setw(22) << category
                      << GREEN << std::right << std::setw(10) << totalStr << RESET << "\n";

            if (total > topIncome) {
                topIncome = total;
                topIncomeCategory = category;
            }
        }
    }

    std::cout << "\n  " << DIM << std::string(34, '-') << RESET << "\n";

    if (!topExpenseCategory.empty()) {
        std::cout << "  " << CYAN << BOLD << "Most spent:   " << RESET
                  << CYAN << topExpenseCategory
                  << "  (" << std::fixed << std::setprecision(2) << topExpense << ")"
                  << RESET << "\n";
    }

    if (!topIncomeCategory.empty()) {
        std::cout << "  " << CYAN << BOLD << "Most earned:  " << RESET
                  << CYAN << topIncomeCategory
                  << "  (+" << std::fixed << std::setprecision(2) << topIncome << ")"
                  << RESET << "\n\n";
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
 
    std::cout << "\n" << BLUE << BOLD;
    std::cout << "  ╔══════════════════════════════════════════════╗\n";
    std::cout << "  ║          💰  FINANCIAL PLANNER  💰           ║\n";
    std::cout << "  ╠══════════════════════════════════════════════╣\n" << RESET;
 
    auto item = [](const std::string& num, const std::string& label) {
        std::cout << BLUE << BOLD << "  ║  " << RESET
                  << CYAN << BOLD << num << RESET
                  << "  " << WHITE << std::left << std::setw(38) << label
                  << BLUE << BOLD << "   ║\n" << RESET;
    };
 
    item("1", "Add expense");
    item("2", "Add income");
    item("3", "List all transactions");
    item("4", "Export report to CSV");
    item("5", "Show balance");
    item("6", "Income & expenses");
    item("7", "Category summary");
    item("8", "Clear all transactions");
 
    std::cout << BLUE << BOLD << "  ╠══════════════════════════════════════════════╣\n" << RESET;
    item("0", "Save & exit");
    std::cout << BLUE << BOLD << "  ╚══════════════════════════════════════════════╝\n" << RESET;
 
    std::cout << "\n  " << CYAN << "❯ " << RESET;
}

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

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
            printError("Invalid input. Enter a number:");
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
                printError("Unknown option.");
        }
    }

    FileManager::saveTransactions(FILE_TRANSACTIONS, manager.getTransactions());

    printSuccess("All data saved.");

    return 0;
}