#include <iostream>   // For standard input/output
#include <string>     // For string manipulation
#include <cctype>     // For isdigit
#include <cmath>      // For pow
#include <cassert>    // For testing
#include <stdexcept>  // For exception handling
#include <algorithm>  // For removing spaces (std::remove)
#include <iomanip>    // For std::setprecision

bool errorFlag = false;

void remove_spaces(std::string &s) {
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
}

float evalexpression(const std::string &expression) {
    float result = 0;
    float num = 0;
    char op = '+'; // Initialize operator
    int len = expression.length();

    for (size_t i = 0; i < len; ++i) {
        if (expression[i] == '(') {
            size_t start = i + 1;
            size_t subexpressionLen = start;
            int openParens = 1;

            while (subexpressionLen < len && openParens > 0) {
                if (expression[subexpressionLen] == '(') ++openParens;
                if (expression[subexpressionLen] == ')') --openParens;
                ++subexpressionLen;
            }

            if (openParens != 0) {
                throw std::runtime_error("Error: Mismatched parentheses.");
            }

            std::string substring = expression.substr(start, subexpressionLen - start - 1);
            num = evalexpression(substring);

            i = subexpressionLen - 1;

        } 
	else if (std::isdigit(expression[i]) || expression[i] == '.') {
	    size_t start = i;
	    
	    while (i < len && (std::isdigit(expression[i]) || expression[i] == '.')) ++i;
	    num = std::stof(expression.substr(start, i - start));
	    --i;
	}

	else if (expression[i] == '+' || expression[i] == '-' || 
                   expression[i] == '*' || expression[i] == '/' || 
                   expression[i] == '%') {

            switch (op) {
                case '+': result += num; break;
                case '-': result -= num; break;
                case '*': result *= num; break;
                case '^': result = std::pow(result, num); break;
                case '/':
                    if (num == 0) {
                        throw std::runtime_error("Error: Division by zero.");
                    }
                    result /= num;
                    break;
                case '%':
                    result = static_cast<int>(result) % static_cast<int>(num);
                    break;
            }

            if (expression[i] == '*' && i + 1 < len && expression[i + 1] == '*') {
                op = '^';
                ++i;
            } else {
                op = expression[i];
            }
		num = 0;

        } else {
            throw std::runtime_error("Invalid Character in expression.");
        }
    }

    switch (op) {
        case '+': result += num; break;
        case '-': result -= num; break;
        case '*': result *= num; break;
        case '^': result = std::pow(result, num); break;
        case '/':
            if (num == 0) {
                throw std::runtime_error("Error: Division by zero.");
            }
            result /= num;
            break;
        case '%':
            result = static_cast<int>(result) % static_cast<int>(num);
            break;
	}
    	//Debug
    std::cout << "Final Result: " << result << std::endl;
	return result;
}

void test() {
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

    std::cout << evalexpression("-(+2)*(+3)-(-4)/(-5)") <<std::endl;

    assert(std::fabs(evalexpression("-(+2)*(+3)-(-4)/(-5)") + 6.8) < 0.01);
    std::cout << "Assert 15 passed\n";
    assert(evalexpression("1") == 2);
    std::cout << "Assert 16 passed\n";
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
        float result = evalexpression(expression);
        if (!errorFlag) {
            std::cout << std::fixed << std::setprecision(3) << result << "\n";
        }
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
