#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>  // For removing spaces (std::remove)
#include "Input.hpp"
#include "InToPost.hpp"
#include "Evaluator.hpp"

using namespace std;

void remove_spaces(std::string &s) {   // Removes spaces from the string
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
}

bool areParenthesesBalanced(const std::string &expression) {   // Ensures that each opening parentheses has a closing Parentheses
    int balance = 0;   // Number of unmmatched parentheses
    for (char c : expression) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) return false; // More closing than opening
    }
    return balance == 0; // Ensure all are matched
}

int main() {
    string expression = Input::getInput();   //Calls get input
     try {
        remove_spaces(expression);   //removes the spaces from the expression
        if (!areParenthesesBalanced(expression)) {     // Makes sure the parentheses are balanced
            throw std::runtime_error("Mismatched parentheses in the expression");
        }
        string postfix = InToPost::infixToPostfix(expression);     // Converts from infix to postfix
        double result = Evaluator::evalexpression(postfix);     // Evaluates the postfix expression
        cout << "Result: " << result << endl;    // Outputs the result
    } catch (...) {  
        std::cerr << "Error: Invalid Expression\n";   // If an error is caught, Tell the user
    } 
    return 0;
}