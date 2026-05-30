#include "calculator/operation_service.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <memory>

using demo::AuditSink;
using demo::ExpressionEvaluator;
using demo::HistoryRepository;
using demo::OperationService;
using ::testing::InSequence;
using ::testing::StrictMock;

class MockAuditSinkForCollaboration : public AuditSink {
public:
    MOCK_METHOD(void, notifySuccess, (const std::string& expression, int result), (override));
    MOCK_METHOD(void, notifyFailure, (const std::string& expression, const std::string& reason), (override));
};

TEST(GMockCollaborationTests, ServiceNotifiesAuditSinkWithExactParameters) {
    const auto historyFile = std::filesystem::temp_directory_path() / "gmock_history_success.csv";
    std::filesystem::remove(historyFile);

    auto audit = std::make_shared<StrictMock<MockAuditSinkForCollaboration>>();
    EXPECT_CALL(*audit, notifySuccess("3 + 4", 7));

    OperationService service(ExpressionEvaluator{}, HistoryRepository{historyFile}, audit);
    EXPECT_EQ(service.evaluateAndStore("3 + 4"), 7);

    std::filesystem::remove(historyFile);
}

TEST(GMockCollaborationTests, SequenceCanBeVerifiedAcrossSeveralCalls) {
    const auto historyFile = std::filesystem::temp_directory_path() / "gmock_history_sequence.csv";
    std::filesystem::remove(historyFile);

    auto audit = std::make_shared<StrictMock<MockAuditSinkForCollaboration>>();
    {
        InSequence sequence;
        EXPECT_CALL(*audit, notifySuccess("1 + 1", 2));
        EXPECT_CALL(*audit, notifySuccess("2 + 2", 4));
    }

    OperationService service(ExpressionEvaluator{}, HistoryRepository{historyFile}, audit);
    EXPECT_EQ(service.evaluateAndStore("1 + 1"), 2);
    EXPECT_EQ(service.evaluateAndStore("2 + 2"), 4);

    std::filesystem::remove(historyFile);
}
