#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>

struct Transaction {
    std::string date;
    std::string category;
    std::string description;
    double amount;
};

std::vector<Transaction> transactions;

std::string currentDate() {
    std::time_t t = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return buf;
}

void addTransaction() {
    std::cout << "| NEW TRANSACTION |\n";

    Transaction t;
    t.date = currentDate();

    std::vector<std::string> categories = {"food", "transport", "rent", "income", "personal expenses", "loan payments", "income", "other"};
    std::cout << "  Categories:\n";
    for(int i = 0; i < (int)categories.size(); ++i)
        std::cout << "      " << i + 1 << ".     " << categories[i] << "\n";
    std::cout << "  Select a category (1 - " << categories.size() << "):";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > categories.size()) {
        std::cout << "  Invalid category selected. \n" ;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    t.category = categories[choice - 1];

    std::cout << "  Enter a description: ";
    std::getline(std::cin, t.description);

    std::cout << "  Enter the amount (negative = income): ";
    if ( !(std::cin >> t.amount) ) {
        std::cout << "  Invalid amount entered. \n";
        return;
    }

    transactions.push_back(t);
    std::cout << "  Transaction saved.\n";
}

void listTransactions() {
        std::cout << " | ALL TRANSACTIONS | \n";
    if (transactions.empty()) { 
        std::cout << "  No transactions yet.\n"; 
        return; 
    }

    std::cout << std::left
              << std::setw(12) << "Date"
              << std::setw(12) << "Category"
              << std::setw(22) << "Description"
              << std::right << std::setw(10) << "Amount" << '\n';
    for (const auto& t : transactions) {
        std::cout << std::left
                  << std::setw(12) << t.date
                  << std::setw(12) << t.category
                  << std::setw(22) << t.description.substr(0, 21)
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << t.amount << '\n';
    }
}

void exportReport() {

}

void listMenu() {
    std::cout << "      | FINANCIAL PLANNER | \n";
    std::cout << "  1. Add transaction\n";
    std::cout << "  2. List all transactions\n";
    std::cout << "  3. Export report to CSV\n";
    std::cout << "  0. Save & exit\n";
    std::cout << "  Choice: ";
}

int main()
{
    int choice = -1;

    while(choice != 0) {
        listMenu();
        std::cin >> choice;

        switch(choice) {
            case 1: addTransaction();   break;
            case 2: listTransactions(); break;
            case 3: exportReport();     break;
            case 0: choice = 0;         break;
            default: std::cout << "  Unknown option.\n";
        }
    }

    std::cout << "All data saved.";
    return 0;
}