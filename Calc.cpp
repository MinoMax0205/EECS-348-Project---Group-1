#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <algorithm>  // For removing spaces (std::remove)
#include <regex>

using namespace std;

void remove_spaces(std::string &s) {
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
}

int processExponents(std::string &input) {
    // Check for the presence of '^'
    if (input.find('^') != std::string::npos) {
        throw std::runtime_error("Invalid character");
    }

    // Replace all occurrences of "**" with "^"
    size_t pos = 0;
    while ((pos = input.find("**", pos)) != std::string::npos) {
        input.replace(pos, 2, "^");
        pos += 1; // Move past the newly replaced character
    }

    return 0;
}

// Function to check if a character is an operator
bool isOperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%');
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '^')
        return 3;
    if (op == 'u') 
        return 4; // Unary operators have the highest precedence
    return 0;
}

double PerformUnaryExpression(const string &op, double operand) {
    if (op == "-u") return -operand; // Unary minus
    if (op == "+u") return operand;  // Unary plus
    throw std::runtime_error("Invalid unary operator: " + op);
}

double performOperation(const string &op, double a, double b = 0) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if (op == "%") {
        if (b == 0) throw std::runtime_error("Modulo by zero");
        return std::fmod(a, b);
    }
    if (op == "^") return std::pow(a, b);
    throw std::runtime_error("Invalid operator: " + op);
}

// Validate characters in a string
void validateExpression(const std::string &expression) {
    // Regex to find invalid characters
    std::regex invalidCharRegex("[^0-9+\\-*/%^(). ]");

    // Search for invalid characters
    if (std::regex_search(expression, invalidCharRegex)) {
        throw std::runtime_error("Invalid characters in expression.");
    }
}

// Shunting-yard algorithm
string infixToPostfix(string infix) {
    processExponents(infix);

    stack<string> operators;
    queue<string> output;
    string postfix = "";
    bool expectUnary = true; // Start by expecting a unary operator

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isdigit(c) || c == '.') {
            // Accumulate multi-digit or decimal numbers
            string number(1, c);
            while (i + 1 < infix.size() && (isdigit(infix[i + 1]) || infix[i + 1] == '.')) {
                number += infix[++i];
            }
            output.push(number);
            expectUnary = false; // After a number, expect a binary operator
        } else if (c == '+' || c == '-') {
            if (expectUnary) {
                // Treat as unary
                string unary = string(1, c) + "u"; // Convert to "+u" or "-u"
                operators.push(unary);
            } else {
                // Treat as binary
                while (!operators.empty() && precedence(operators.top()[0]) >= precedence(c)) {
                    output.push(operators.top());
                    operators.pop();
                }
                operators.push(string(1, c));
            }
            expectUnary = true; // After an operator, expect another unary
        } else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()[0]) >= precedence(c)) {
                output.push(operators.top());
                operators.pop();
            }
            operators.push(string(1, c));
            expectUnary = true; // After an operator, expect another unary
        } else if (c == '(') {
            operators.push(string(1, c));
            expectUnary = true; // After '(', expect a unary operator
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != "(") {
                output.push(operators.top());
                operators.pop();
            }
            operators.pop(); // Remove the '('
            expectUnary = false; // After ')', expect a binary operator
        }
    }

    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    while (!output.empty()) {
        postfix += output.front() + " ";
        output.pop();
    }

    return postfix;
}

double evalexpression(string infix) {
    string expression = infixToPostfix(infix);

    stack<double> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1)) {
            s.push(stod(token));
        } else if (token == "-u" || token == "+u") {
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

// test all cases presented in the given example project file
void test() {
    // assert correct statements are correct
    assert(evalexpression("3+4") == 7);
    std::cout << "Assert 1 passed\n";
    assert(evalexpression("8-(5-2)") == 5);
    std::cout << "Assert 2 passed\n";
    assert(evalexpression("10*2/5") == 4);
    std::cout << "Assert 3 passed\n";
    assert(evalexpression("2**3") == 8);
    std::cout << "Assert 4 passed\n";
    assert(evalexpression("4*(3+2)%7-1") == 5);
    std::cout << "Assert 5 passed\n";
    assert(evalexpression("(((2+3)))+(((1+2)))") == 8);
    std::cout << "Assert 6 passed\n";
    assert(evalexpression("((5*2)-((3/1)+((4%3))))") == 6);
    std::cout << "Assert 7 passed\n";
    assert(evalexpression("(((2**(1+1))+((3-1)**2))/((4/2)%3))") == 4);
    std::cout << "Assert 8 passed\n";
    assert(evalexpression("(((((5-3)))*(((2+1)))+((2*3))))") == 12);
    std::cout << "Assert 9 passed\n";
    assert(evalexpression("((9+6))/((3*1)/(((2+2)))-1)") == -60);
    std::cout << "Assert 10 passed\n";
    assert(std::fabs(evalexpression("+(-2)*(-3)-((-4)/(+5))") - 6.800) < 0.001);
    std::cout << "Assert 11 passed\n";
    assert(evalexpression("-(+1)+(+2)") == 1);
    std::cout << "Assert 12 passed\n";
    assert(evalexpression("-(-(-3))+(-4)+(+5)") == -2);
    std::cout << "Assert 13 passed\n";
    assert(std::fabs(evalexpression("+2**(-3)") - 0.125) < 0.001);
    std::cout << "Assert 14 passed\n";
    assert(std::fabs(evalexpression("-(+2)*(+3)-(-4)/(-5)") + 6.8) < 0.01);
    std::cout << "Assert 15 passed\n";

    // Assert that incorect statements are incorrect
    bool exceptionThrown = false;
    try { evalexpression("2 * (4 + 3 - 1"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 16 passed\n";
    try { evalexpression("* 5 + 2"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 17 passed\n";
    try { evalexpression("4 / 0"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 18 passed\n";
    try { evalexpression("5 (2 + 3)"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 19 passed\n";
    try { evalexpression("7 & 3"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 20 passed\n";
    try { evalexpression("(((3 + 4) - 2) + (1)"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 21 passed\n";
    try { evalexpression("((5 + 2) / (3 * 0))"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 22 passed\n";
    try { evalexpression("((2 -) 1 + 3)"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 23 passed\n";
    try { evalexpression("((4 * 2) + ( - ))"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 24 passed\n";
    try { evalexpression("((7 * 3) ^ 2)"); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 25 passed\n";
}

int main() {
    std::cout << "Input please: ";
    std::string expression;
    std::getline(std::cin, expression);
    if (expression == "test") {
        test();
        return 0;
    }

    try {
        remove_spaces(expression);
        validateExpression(expression); 
        double result = evalexpression(expression);

    } catch (...) {
        std::cerr << "Error: Invalid expression\n";
    } 
    return 0;
}
