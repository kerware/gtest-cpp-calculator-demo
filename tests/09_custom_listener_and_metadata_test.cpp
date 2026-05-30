#include "calculator/calculator.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

using demo::Calculator;

class MetadataEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        ::testing::Test::RecordProperty("training.level", "advanced");
        ::testing::Test::RecordProperty("component", "calculator");
    }
};

class MinimalProgressListener : public ::testing::EmptyTestEventListener {
public:
    void OnTestStart(const ::testing::TestInfo& testInfo) override {
        std::cout << "[demo-listener] start "
                  << testInfo.test_suite_name() << "." << testInfo.name() << '\n';
    }
};

TEST(CustomListenerAndMetadataTests, RecordPropertyAddsInformationToXmlReport) {
    ::testing::Test::RecordProperty("requirement", "CALC-ADD-001");
    Calculator calculator;
    EXPECT_EQ(calculator.add(40, 2), 42);
}

TEST(CustomListenerAndMetadataTests, ScopedTraceImprovesFailureContext) {
    Calculator calculator;
    for (const int value : {1, 2, 3}) {
        SCOPED_TRACE("value=" + std::to_string(value));
        EXPECT_EQ(calculator.multiply(value, 2), value + value);
    }
}

int register_demo_environment = []() {
    ::testing::AddGlobalTestEnvironment(new MetadataEnvironment{});
    auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new MinimalProgressListener{});
    return 0;
}();
