#include "calculator/calculator.h"

#include <cstdio>
#include <cstdlib>
#include <numeric>

namespace demo {

int Calculator::add(int a, int b) const {
    if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
        (b < 0 && a < std::numeric_limits<int>::min() - b)) {
        throw std::overflow_error("integer addition overflow");
    }
    return a + b;
}

int Calculator::subtract(int a, int b) const {
    if ((b < 0 && a > std::numeric_limits<int>::max() + b) ||
        (b > 0 && a < std::numeric_limits<int>::min() + b)) {
        throw std::overflow_error("integer subtraction overflow");
    }
    return a - b;
}

int Calculator::multiply(int a, int b) const {
    const long long result = static_cast<long long>(a) * static_cast<long long>(b);
    if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min()) {
        throw std::overflow_error("integer multiplication overflow");
    }
    return static_cast<int>(result);
}

int Calculator::divide(int a, int b) const {
    if (b == 0) {
        throw std::invalid_argument("division by zero");
    }
    return a / b;
}

long long Calculator::factorial(int n) const {
    if (n < 0) {
        throw std::invalid_argument("factorial is undefined for negative numbers");
    }
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int Calculator::gcd(int a, int b) const {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        const int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

double Calculator::mean(const std::vector<int>& values) const {
    if (values.empty()) {
        throw std::invalid_argument("mean requires at least one value");
    }
    const int sum = std::accumulate(values.begin(), values.end(), 0);
    return static_cast<double>(sum) / static_cast<double>(values.size());
}

void Calculator::abortIfNegative(int value) const {
    if (value < 0) {
        std::abort();
    }
}

void Calculator::terminateOnDivisionByZero(int denominator) const {
    if (denominator == 0) {
        std::fprintf(stderr, "POST_MORTEM: fatal division by zero\n");
        std::abort();
    }
}

} // namespace demo
