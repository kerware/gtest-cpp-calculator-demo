#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace demo {

struct OperationRecord {
    std::string expression;
    int result{};
};

class HistoryRepository {
public:
    explicit HistoryRepository(std::filesystem::path file);

    void append(const OperationRecord& record);
    std::vector<OperationRecord> loadAll() const;
    std::filesystem::path file() const;

private:
    std::filesystem::path file_;
};

} // namespace demo
