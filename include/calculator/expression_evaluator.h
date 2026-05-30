#pragma once

#include "calculator/calculator.h"

#include <string>

namespace demo {

class ExpressionEvaluator {
public:
    explicit ExpressionEvaluator(Calculator calculator = Calculator{});
    int evaluate(const std::string& expression) const;

private:
    Calculator calculator_;
};

} // namespace demo
