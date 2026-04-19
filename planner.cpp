#include <iostream>
#include <vector>

struct Transaction {
    std::string date;
    std::string category;
    std::string description;
    double amount;
};

std::vector<Transaction> transactions;

void addTransaction() {
    std::cout << "| NEW TRANSACTION |\n";

    Transaction t;

    std::vector<std::string> categories = {"food", "transport", "rent", "income", "personal expenses", "loan payments", "income", "other"};
    std::cout << "  Categories:\n";
    for(int i = 0; i < (int)categories.size(); ++i)
        std::cout << "      " << i + 1 << ".     " << categories[i] << "\n";
    std::cout << "  Select a category (1 - " << categories.size() << "):\n";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > categories.size()) {
        std::cout << "  Invalid category selected \n" ;
        return;
    }

    t.category = categories[choice - 1];

    std::cout << "  Enter a description: \n";
    std::getline(std::cin, t.description);

    std::cout << "  Enter the amount (negative = income): \n";
    if ( !(std::cin >> t.amount) ) {
        std::cout << "  Invalid amount entered \n";
        return;
    }

    transactions.push_back(t);
    std::cout << "  Transaction saved.\n";
}

int main()
{
    addTransaction();
    return 0;
}