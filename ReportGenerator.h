#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>
#include <vector>
#include "Transaction.h"

class ReportGenerator {
public:
    static void exportReport(const std::string& filename, const std::vector<Transaction>& transactions);
};

#endif