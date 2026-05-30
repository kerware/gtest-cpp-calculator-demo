#include "calculator/calculator.h"

#include <gtest/gtest.h>

#include <limits>

using demo::Calculator;

TEST(ExceptionTests, DivideByZeroThrowsWithReadableMessage) {
    Calculator calculator;

    try {
        (void)calculator.divide(10, 0);
        FAIL() << "Une exception std::invalid_argument était attendue";
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "division by zero");
    }
}

TEST(ExceptionTests, AdditionOverflowThrows) {
    Calculator calculator;
    EXPECT_THROW(calculator.add(std::numeric_limits<int>::max(), 1), std::overflow_error);
}

TEST(PostMortemDeathTests, AbortIfNegativeTerminatesTheProcess) {
    Calculator calculator;
    EXPECT_DEATH(calculator.abortIfNegative(-1), "");
}

TEST(PostMortemDeathTests, FatalDivisionByZeroLeavesDiagnosticMessage) {
    Calculator calculator;
    EXPECT_DEATH(calculator.terminateOnDivisionByZero(0), "POST_MORTEM: fatal division by zero");
}

TEST(PostMortemDeathTests, NonFatalInputDoesNotTerminate) {
    Calculator calculator;
    EXPECT_EXIT(
        {
            calculator.abortIfNegative(10);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0),
        ""
    );
}
