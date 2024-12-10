#include "Evaluator.hpp"
#include <stack>
#include <string>
#include <cmath>
#include <sstream>

bool Evaluator::isOperator(char op) {  // check to see if the character is an operator
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%');
}

double Evaluator::performOperation(const string &op, double a, double b = 0) {   //Takes in an operator, and two doubles
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

double Evaluator::PerformUnaryExpression(const string &op, double operand) {  //converts the numbers to the unary version based on sign
    if (op == "n") return -operand; // Unary minus
    if (op == "+u") return operand;  // Unary plus
    throw std::runtime_error("Invalid unary operator: " + op);
}

float Evaluator::evalexpression(const string &expression) {    //evaluates the postfix function
    for(size_t i = 0; i < expression.length(); i++){   //check for invalid syntax
        if (expression[i] == '.' && expression[i+1] =='.') throw std::runtime_error("Invalid Syntax");
    }
    stack<double> s; //creates a stack to hold operands
    stringstream ss(expression);  //to make the tokens
    string token;   //temporarily holds sections of the expression

    while (ss >> token) {  //go through every token
        if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1)) { //if it is a number or decimal
            s.push(stod(token));     // push it to the stack
        } else if (token == "n" || token == "+u") {    //if it is a unary operator
            if (s.empty()) throw std::runtime_error("Invalid expression: Unary operator without operand");
            double operand = s.top(); s.pop();     //convert it to unary and remove it
            s.push(PerformUnaryExpression(token, operand));   //re-add the unary version of the operand
        } else if (isOperator(token[0])) {     //if it is a operator
            if (s.size() < 2) throw std::runtime_error("Invalid expression: Not enough operands for binary operator");
            double operand2 = s.top(); s.pop();   //get the two values to operate on
            double operand1 = s.top(); s.pop();
            s.push(performOperation(token, operand1, operand2));    // call the perform function with these values and the operator
        } else {
            throw std::runtime_error("Invalid token: " + token);
        }
    }

    if (s.size() != 1) throw std::runtime_error("Invalid expression: Stack error");
    return s.top();    // return the top when there is only one value left in the stack
}
