#include "ReportGenerator.h"
#include <fstream>

void ReportGenerator::exportReport(const std::string& filename, const std::vector<Transaction>& transactions) {
    std::ofstream f(filename);

    f << "date,category,description,amount\n";

    for (const auto& t : transactions) {
        f << t.date << ','
          << t.category << ','
          << t.description << ','
          << t.amount << '\n';
    }
}