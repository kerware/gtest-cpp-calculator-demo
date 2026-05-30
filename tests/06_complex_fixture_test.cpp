#include "calculator/operation_service.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <memory>
#include <random>
#include <string>

using demo::AuditSink;
using demo::ExpressionEvaluator;
using demo::HistoryRepository;
using demo::OperationRecord;
using demo::OperationService;
using ::testing::_;
using ::testing::HasSubstr;
using ::testing::StrictMock;

namespace {

class MockAuditSink final : public AuditSink {
public:
    MOCK_METHOD(void, notifySuccess, (const std::string& expression, int result), (override));
    MOCK_METHOD(void, notifyFailure, (const std::string& expression, const std::string& reason), (override));
};

std::filesystem::path makeUniqueTempDirectory() {
    const auto base = std::filesystem::temp_directory_path();
    std::random_device randomDevice;
    const auto candidate = base / ("gtest_calculator_" + std::to_string(randomDevice()));
    std::filesystem::create_directories(candidate);
    return candidate;
}

class OperationServiceComplexFixture : public ::testing::Test {
protected:
    void SetUp() override {
        tempDirectory = makeUniqueTempDirectory();
        historyFile = tempDirectory / "history.csv";
        auditSink = std::make_shared<StrictMock<MockAuditSink>>();
    }

    void TearDown() override {
        std::error_code ignored;
        std::filesystem::remove_all(tempDirectory, ignored);
    }

    OperationService createService() {
        return OperationService(
            ExpressionEvaluator{},
            HistoryRepository{historyFile},
            auditSink
        );
    }

    std::vector<OperationRecord> loadHistory() const {
        return HistoryRepository{historyFile}.loadAll();
    }

    std::filesystem::path tempDirectory;
    std::filesystem::path historyFile;
    std::shared_ptr<StrictMock<MockAuditSink>> auditSink;
};

} // namespace

TEST_F(OperationServiceComplexFixture, SuccessfulOperationIsStoredAndAudited) {
    EXPECT_CALL(*auditSink, notifySuccess("7 * 6", 42));

    OperationService service = createService();
    EXPECT_EQ(service.evaluateAndStore("7 * 6"), 42);

    const auto records = loadHistory();
    ASSERT_EQ(records.size(), 1U);
    EXPECT_EQ(records[0].expression, "7 * 6");
    EXPECT_EQ(records[0].result, 42);
}

TEST_F(OperationServiceComplexFixture, FailedOperationIsAuditedAndNotStored) {
    EXPECT_CALL(*auditSink, notifyFailure("10 / 0", HasSubstr("division by zero")));

    OperationService service = createService();
    EXPECT_THROW(service.evaluateAndStore("10 / 0"), std::invalid_argument);

    EXPECT_TRUE(loadHistory().empty());
}

TEST_F(OperationServiceComplexFixture, MultipleOperationsAreStoredInOrder) {
    EXPECT_CALL(*auditSink, notifySuccess(_, _)).Times(2);

    OperationService service = createService();
    service.evaluateAndStore("1 + 2");
    service.evaluateAndStore("9 - 4");

    const auto records = loadHistory();
    ASSERT_EQ(records.size(), 2U);
    EXPECT_EQ(records[0].expression, "1 + 2");
    EXPECT_EQ(records[0].result, 3);
    EXPECT_EQ(records[1].expression, "9 - 4");
    EXPECT_EQ(records[1].result, 5);
}
