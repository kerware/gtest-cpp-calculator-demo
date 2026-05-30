#include "calculator/calculator.h"

#include <gtest/gtest.h>

#include <tuple>

using demo::Calculator;

class MultiplicationCombinatorialTest : public ::testing::TestWithParam<std::tuple<int, int>> {
protected:
    Calculator calculator;
};

TEST_P(MultiplicationCombinatorialTest, MultiplicationMatchesMathematicalProduct) {
    const auto [left, right] = GetParam();
    SCOPED_TRACE("left=" + std::to_string(left) + " right=" + std::to_string(right));
    EXPECT_EQ(calculator.multiply(left, right), left * right);
}

INSTANTIATE_TEST_SUITE_P(
    CartesianProduct,
    MultiplicationCombinatorialTest,
    ::testing::Combine(
        ::testing::Values(-3, -1, 0, 1, 3),
        ::testing::Values(-2, 0, 2)
    )
);

class GcdCombinatorialPropertiesTest : public ::testing::TestWithParam<std::tuple<int, int>> {
protected:
    Calculator calculator;
};

TEST_P(GcdCombinatorialPropertiesTest, GcdIsSymmetricAndPositive) {
    const auto [a, b] = GetParam();
    const int gcd1 = calculator.gcd(a, b);
    const int gcd2 = calculator.gcd(b, a);

    EXPECT_EQ(gcd1, gcd2);
    EXPECT_GE(gcd1, 0);
}

INSTANTIATE_TEST_SUITE_P(
    SymmetryDomain,
    GcdCombinatorialPropertiesTest,
    ::testing::Combine(
        ::testing::Values(-30, -12, 0, 12, 30),
        ::testing::Values(-18, 0, 18)
    )
);
