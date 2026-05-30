#include "calculator/calculator.h"

#include <gtest/gtest.h>

#include <vector>

using demo::Calculator;

TEST(BeginnerAssertions, ExpectEqChecksIntegerResult) {
    Calculator calculator;
    EXPECT_EQ(calculator.add(2, 3), 5);
    EXPECT_EQ(calculator.subtract(10, 4), 6);
}

TEST(BeginnerAssertions, AssertStopsTheCurrentTestWhenPreconditionFails) {
    Calculator calculator;
    const std::vector<int> values{2, 4, 6};

    ASSERT_FALSE(values.empty()) << "La moyenne ne peut pas être testée avec un vecteur vide";
    EXPECT_DOUBLE_EQ(calculator.mean(values), 4.0);
}

TEST(BeginnerAssertions, FailureMessageHelpsDiagnosis) {
    Calculator calculator;
    const int left = 7;
    const int right = 5;

    EXPECT_EQ(calculator.multiply(left, right), 35)
        << "Multiplication incorrecte pour left=" << left << " right=" << right;
}

TEST(BeginnerAssertions, FloatingPointComparisonUsesDoubleNear) {
    Calculator calculator;
    EXPECT_NEAR(calculator.mean({1, 2, 2}), 1.666666, 0.00001);
}
