#include "calculator/calculator.h"

#include <gtest/gtest.h>

#include <tuple>

using demo::Calculator;

class AdditionParameterizedTest : public ::testing::TestWithParam<std::tuple<int, int, int>> {
protected:
    Calculator calculator;
};

TEST_P(AdditionParameterizedTest, AddReturnsExpectedResult) {
    const auto [left, right, expected] = GetParam();
    EXPECT_EQ(calculator.add(left, right), expected);
}

INSTANTIATE_TEST_SUITE_P(
    NominalAndBoundaryValues,
    AdditionParameterizedTest,
    ::testing::Values(
        std::make_tuple(1, 2, 3),
        std::make_tuple(0, 0, 0),
        std::make_tuple(-5, 3, -2),
        std::make_tuple(1000, -1000, 0)
    )
);

struct FactorialCase {
    int input;
    long long expected;
};

class FactorialParameterizedTest : public ::testing::TestWithParam<FactorialCase> {
protected:
    Calculator calculator;
};

TEST_P(FactorialParameterizedTest, FactorialReturnsExpectedResult) {
    const FactorialCase testCase = GetParam();
    EXPECT_EQ(calculator.factorial(testCase.input), testCase.expected);
}

INSTANTIATE_TEST_SUITE_P(
    KnownValues,
    FactorialParameterizedTest,
    ::testing::Values(
        FactorialCase{0, 1},
        FactorialCase{1, 1},
        FactorialCase{3, 6},
        FactorialCase{6, 720}
    )
);
