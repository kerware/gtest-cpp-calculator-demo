#include "calculator/expression_evaluator.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: calculator_cli <left> <operator> <right>\n";
        return 2;
    }

    const std::string expression = std::string(argv[1]) + " " + argv[2] + " " + argv[3];
    try {
        const demo::ExpressionEvaluator evaluator;
        std::cout << evaluator.evaluate(expression) << '\n';
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }
}
