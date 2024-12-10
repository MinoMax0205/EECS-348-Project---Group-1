#include "InToPost.hpp"
#include <queue>
#include <stack>
#include <string>
#include <algorithm>  // For removing spaces (std::remove)

using namespace std;

int InToPost::precedence(char op) {   // defines the precedence of operators
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '^')
        return 3;  
    if (op == 'u' || op == 'n') 
        return 4;
    return 0;
}

bool InToPost::isOperator(char op) {   //determines if the character given is an operator
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%');
}

int InToPost::processExponents(std::string &input){   // converts ** to ^ for postfix calculation
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

string InToPost::infixToPostfix(string infix) {   //converts from infic to postfix
    processExponents(infix);

    stack<string> operators;    //stack to hold operators
    queue<string> output;     //queue of outputs
    string postfix = "";   //final string to return
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
                if (unary == "-u") unary = "n";
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

    while (!operators.empty()) {   // while there are still operators
        output.push(operators.top());    // push the one on top to the output
        operators.pop();  //remove it
    }

    while (!output.empty()) {
        postfix += output.front() + " "; //while there are values left, add it to the final string
        output.pop();
    }

    return postfix;    //return the expression in postfix form
}