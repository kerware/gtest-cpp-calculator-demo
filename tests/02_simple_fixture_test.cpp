#include "calculator/calculator.h"

#include <gtest/gtest.h>

using demo::Calculator;

class CalculatorFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Préparation commune à tous les tests de cette fixture.
        calculator = Calculator{};
    }

    Calculator calculator;
};

TEST_F(CalculatorFixture, DivisionByNonZeroValueReturnsQuotient) {
    EXPECT_EQ(calculator.divide(20, 4), 5);
}

TEST_F(CalculatorFixture, DivisionByZeroThrowsInvalidArgument) {
    EXPECT_THROW(calculator.divide(20, 0), std::invalid_argument);
}

TEST_F(CalculatorFixture, FactorialOfFiveIsOneHundredTwenty) {
    EXPECT_EQ(calculator.factorial(5), 120);
}

TEST_F(CalculatorFixture, GcdAcceptsNegativeValues) {
    EXPECT_EQ(calculator.gcd(-24, 18), 6);
}
