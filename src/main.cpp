#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>  // For removing spaces (std::remove)
#include "Input.hpp"
#include "InToPost.hpp"
#include "Evaluator.hpp"

using namespace std;

void remove_spaces(std::string &s) {
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
}

bool areParenthesesBalanced(const std::string &expression) {
    int balance = 0;
    for (char c : expression) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) return false; // More closing than opening
    }
    return balance == 0; // Ensure all are matched
}

int main() {
    while (1){
    string expression = Input::getInput();

     try {
        remove_spaces(expression);
        if (!areParenthesesBalanced(expression)) {
            throw std::runtime_error("Mismatched parentheses in the expression");
        }
        string postfix = InToPost::infixToPostfix(expression);
        double result = Evaluator::evalexpression(postfix);
        cout << "Result: " << result << endl;
    } catch (...) {
        std::cerr << "Error: Invalid Expression\n";
    } 
    
    }
    return 0;
}