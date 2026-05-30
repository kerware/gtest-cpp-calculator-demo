#include "calculator/expression_evaluator.h"

#include <sstream>
#include <stdexcept>

namespace demo {

ExpressionEvaluator::ExpressionEvaluator(Calculator calculator)
    : calculator_(calculator) {}

int ExpressionEvaluator::evaluate(const std::string& expression) const {
    std::istringstream input(expression);
    int left = 0;
    int right = 0;
    char op = '\0';
    if (!(input >> left >> op >> right)) {
        throw std::invalid_argument("invalid expression. Expected format: <int> <op> <int>");
    }

    switch (op) {
        case '+': return calculator_.add(left, right);
        case '-': return calculator_.subtract(left, right);
        case '*': return calculator_.multiply(left, right);
        case '/': return calculator_.divide(left, right);
        default: throw std::invalid_argument("unsupported operator");
    }
}

} // namespace demo
