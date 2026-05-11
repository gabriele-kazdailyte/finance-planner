#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction {
    std::string date;
    std::string category;
    std::string description;
    double amount;
};

#endif