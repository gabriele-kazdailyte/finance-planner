#include "FileManager.h"
#include <fstream>
#include <sstream>

std::vector<Transaction> FileManager::loadTransactions(const std::string& filename) {
    std::vector<Transaction> transactions;

    std::ifstream f(filename);
    if (!f.is_open()) {
        return transactions;
    }

    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        std::istringstream ss(line);
        Transaction t;

        std::getline(ss, t.date, ',');
        std::getline(ss, t.category, ',');
        std::getline(ss, t.description, ',');

        std::string amt;
        std::getline(ss, amt);

        try {
            t.amount = std::stod(amt);
        } catch (...) {
            continue;
        }

        transactions.push_back(t);
    }

    return transactions;
}

void FileManager::saveTransactions(const std::string& filename, const std::vector<Transaction>& transactions) {
    std::ofstream f(filename);

    f << "date,category,description,amount\n";

    for (const auto& t : transactions) {
        f << t.date << ','
          << t.category << ','
          << t.description << ','
          << t.amount << '\n';
    }
}