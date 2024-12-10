#include "Evaluator.hpp"
#include <stack>
#include <string>
#include <cmath>
#include <sstream>

bool Evaluator::isOperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%');
}

double Evaluator::performOperation(const string &op, double a, double b = 0) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if (op == "%") {
        if (b == 0) throw std::runtime_error("Modulo by zero");
        double result = std::fmod(a, b);
        if (result < 0) result += b;
        return result;
    }
    if (op == "^") return std::pow(a, b);
    throw std::runtime_error("Invalid operator: " + op);
}

double Evaluator::PerformUnaryExpression(const string &op, double operand) {
    if (op == "n") return -operand; // Unary minus
    if (op == "+u") return operand;  // Unary plus
    throw std::runtime_error("Invalid unary operator: " + op);
}

float Evaluator::evalexpression(const string &expression) {
    for(size_t i = 0; i < expression.length(); i++){
        if (expression[i] == '.' && expression[i+1] =='.') throw std::runtime_error("Invalid Syntax");
    }
    stack<double> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1)) {
            s.push(stod(token));
        } else if (token == "n" || token == "+u") {
            if (s.empty()) throw std::runtime_error("Invalid expression: Unary operator without operand");
            double operand = s.top(); s.pop();
            s.push(PerformUnaryExpression(token, operand));
        } else if (isOperator(token[0])) {
            if (s.size() < 2) throw std::runtime_error("Invalid expression: Not enough operands for binary operator");
            double operand2 = s.top(); s.pop();
            double operand1 = s.top(); s.pop();
            s.push(performOperation(token, operand1, operand2));
        } else {
            throw std::runtime_error("Invalid token: " + token);
        }
    }

    if (s.size() != 1) throw std::runtime_error("Invalid expression: Stack error");
    return s.top();
}
