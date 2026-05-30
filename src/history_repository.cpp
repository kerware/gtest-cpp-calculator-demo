#include "calculator/history_repository.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace demo {

HistoryRepository::HistoryRepository(std::filesystem::path file)
    : file_(std::move(file)) {}

void HistoryRepository::append(const OperationRecord& record) {
    std::ofstream output(file_, std::ios::app);
    if (!output) {
        throw std::runtime_error("unable to open history file for writing");
    }
    output << record.expression << ';' << record.result << '\n';
}

std::vector<OperationRecord> HistoryRepository::loadAll() const {
    std::ifstream input(file_);
    if (!input) {
        return {};
    }

    std::vector<OperationRecord> records;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream parser(line);
        std::string expression;
        std::string resultAsText;
        if (std::getline(parser, expression, ';') && std::getline(parser, resultAsText)) {
            records.push_back(OperationRecord{expression, std::stoi(resultAsText)});
        }
    }
    return records;
}

std::filesystem::path HistoryRepository::file() const {
    return file_;
}

} // namespace demo
