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

// test all cases presented in the given example project file
void test() {
    // assert correct statements are correct
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("3+4")) == 7);
    std::cout << "Assert 1 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("8-(5-2)")) == 5);
    std::cout << "Assert 2 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("10*2/5")) == 4);
    std::cout << "Assert 3 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("2**3")) == 8);
    std::cout << "Assert 4 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("4*(3+2)%7-1")) == 5);
    std::cout << "Assert 5 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("(((2+3)))+(((1+2)))")) == 8);
    std::cout << "Assert 6 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("((5*2)-((3/1)+((4%3))))")) == 6);
    std::cout << "Assert 7 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("(((2**(1+1))+((3-1)**2))/((4/2)%3))")) == 4);
    std::cout << "Assert 8 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("(((((5-3)))*(((2+1)))+((2*3))))")) == 12);
    std::cout << "Assert 9 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("((9+6))/((3*1)/(((2+2)))-1)")) == -60);
    std::cout << "Assert 10 passed\n";
    assert(std::fabs(Evaluator::evalexpression(InToPost::infixToPostfix("+(-2)*(-3)-((-4)/(+5))")) - 6.800) < 0.001);
    std::cout << "Assert 11 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("-(+1)+(+2)")) == 1);
    std::cout << "Assert 12 passed\n";
    assert(Evaluator::evalexpression(InToPost::infixToPostfix("-(-(-3))+(-4)+(+5)")) == -2);
    std::cout << "Assert 13 passed\n";
    assert(std::fabs(Evaluator::evalexpression(InToPost::infixToPostfix("+2**(-3)")) - 0.125) < 0.001);
    std::cout << "Assert 14 passed\n";
    assert(std::fabs(Evaluator::evalexpression(InToPost::infixToPostfix("-(+2)*(+3)-(-4)/(-5)")) + 6.8) < 0.01);
    std::cout << "Assert 15 passed\n";
    // Assert that incorrect statements are incorrect
    bool exceptionThrown = false;
    try { Evaluator::evalexpression(InToPost::infixToPostfix("2 * (4 + 3 - 1")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 16 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("* 5 + 2")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 17 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("4 / 0")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 18 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("5 (2 + 3)")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 19 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("7 & 3")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 20 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("(((3 + 4) - 2) + (1)")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 21 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("((5 + 2) / (3 * 0))")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 22 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("((2 -) 1 + 3)")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 23 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("((4 * 2) + ( - ))")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 24 passed\n";
    try { Evaluator::evalexpression(InToPost::infixToPostfix("((7 * 3) ^ 2)")); } catch(...) { exceptionThrown = true; }
    assert(exceptionThrown);
    std::cout << "Assert 25 passed\n";
}

int main() {
    string expression = Input::getInput();
    if (expression == "test") {
        test();
        return 0;
    }

     try {
        remove_spaces(expression);
        string convert = InToPost::infixToPostfix(expression);
        double result = Evaluator::Evaluator::evalexpression(convert);
        cout << "result: " << result << endl;
    } catch (...) {
        std::cerr << "Error: Invalid expression\n";
    } 
    
    return 0;
}