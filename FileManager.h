#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "Transaction.h"

class FileManager {
public:
    static std::vector<Transaction> loadTransactions(const std::string& filename);
    static void saveTransactions(const std::string& filename, const std::vector<Transaction>& transactions);
};

#endif