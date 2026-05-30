#pragma once

#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace demo {

class Calculator {
public:
    int add(int a, int b) const;
    int subtract(int a, int b) const;
    int multiply(int a, int b) const;
    int divide(int a, int b) const;
    long long factorial(int n) const;
    int gcd(int a, int b) const;
    double mean(const std::vector<int>& values) const;

    // Fonctions volontairement dangereuses pour illustrer les death tests.
    void abortIfNegative(int value) const;
    void terminateOnDivisionByZero(int denominator) const;
};

} // namespace demo
