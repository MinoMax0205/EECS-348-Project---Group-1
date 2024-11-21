#include <stdio.h>  // Included for standard input/output functions
#include <ctype.h>   // Included for isdigit()
#include <string.h>  // Included for string manipulation functions
#include <stdbool.h> // used for error handling
#include <math.h> // used for exponents
#include <assert.h> // used for testing

// used to flag errors when found to prevent printing a 0.00
bool errorFlag = false;

void remove_spaces(char* s) {
    char* d = s; // Destination pointer, initially pointing to the same string
    while (*s) {
        if (!isspace((unsigned char)*s)) {
            *d++ = *s; // Copy non-space characters to the destination
        }
        s++; // Always move the source pointer
    }
    *d = '\0'; // Null-terminate the result string
}

float evalexpression(char expression[]) {
    //remove_spaces(expression);

    float result = 0;
    int num = 0;
    char op = '+'; // the first number will be added to result to start doing operations on 

    for (int i = 0; i < strlen(expression); i++) {
        // handle parenthesis by evaluating first
        if (expression[i] == '(') {
            int start = i + 1;  // Start of the substring (after '(')
            int subexpressionLen = start;
            int openParens = 1; // Track nested parentheses

            // Find the matching closing parenthesis
            while (subexpressionLen < strlen(expression) && openParens > 0) {
                if (expression[subexpressionLen] == '(') openParens++;
                if (expression[subexpressionLen] == ')') openParens--;
                subexpressionLen++;
            }

            // If no close parenthesis is found, the expression is invalid
            if (openParens != 0) {
                printf("Error: Mismatched parentheses.\n");
                errorFlag = true;
                return 0;
            }

            // Extract substring between parentheses
            int substringLen = subexpressionLen - start - 1;  // Exclude outer parentheses
            char substring[100];
            strncpy(substring, expression + start, substringLen);
            substring[substringLen] = '\0';  // Null-terminate the substring

            // Evaluate the substring recursively
            num = evalexpression(substring);

            // Move `i` to just after the closing parenthesis
            i = subexpressionLen - 1;

        } else if (isdigit(expression[i])) { // find the next number by adding each next character
            num = num * 10 + (expression[i] - '0');

        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%') { 
            // '^' not included as it is an invalid input
            switch (op) { // for each operator character, evaluate proper operation on result
                case '+': result += num; break;
                case '-': result -= num; break;
                case '*': result *= num; break;
                case '^': result = pow(result, num); break;
                case '/': result /= num; break;
                case '%': result = (int)result % num; break;
            }

            // if the operator is '**' instead of '*' it is a power and needs to be set as such
            if (expression[i] == '*' && expression[i+1] == '*'){
                op = '^'; // '^' operator is not a valid character for input, but is used in switch case for powers
                i++;
            } else { // if the operator is normal, set operator to evaluate with next found number
                op = expression[i];
            }
            num = 0; // reset num

        } else { // if not a number or operator, this handles invalid character
            printf("Invalid Character in expression, please try again\n");
            errorFlag = true;
            return 0;
        }
    }

    switch (op) { // for each operator character, evaluate proper operation on result
        case '+': result += num; break;
        case '-': result -= num; break;
        case '*': result *= num; break;
        case '^': result = pow(result, num); break;
        case '/': result /= num; break;
        case '%': result = (int)result % num; break;
    }

    return result;
}

void test(){
    assert(evalexpression("3+4") == 7);
    printf("Assert 1 passed\n");
    assert(evalexpression("8-(5-2)") == 5);
    printf("Assert 2 passed\n");
    assert(evalexpression("10*2/5") == 4);
    printf("Assert 3 passed\n");
    assert(evalexpression("2**3") == 8);
    printf("Assert 4 passed\n");
    assert(evalexpression("4*(3+2)%7-1") == 5);
    printf("Assert 5 passed\n");
    assert(evalexpression("(((2+3)))+(((1+2)))") == 8);
    printf("Assert 6 passed\n");
    assert(evalexpression("((5*2)-((3/1)+((4%3))))") == 6);
    printf("Assert 7 passed\n");
    assert(evalexpression("(((2**(1+1))+((3-1)**2))/((4/2)%3))") == 4);
    printf("Assert 8 passed\n");
    assert(evalexpression("(((((5-3)))*(((2+1)))+((2*3))))") == 12);
    printf("Assert 9 passed\n");
    assert(evalexpression("((9+6))/((3*1)/(((2+2)))-1)") == -60);
    printf("Assert 10 passed\n");
    assert(evalexpression("+(-2)*(-3)–((-4)/(+5))") == 6.8);
    printf("Assert 11 passed\n");
    assert(evalexpression("-(+1) + (+2)") == 1);
    printf("Assert 12 passed\n");
    assert(evalexpression("-(-(-3)) + (-4) + (+5)") == -2);
    printf("Assert 13 passed\n");
    assert(evalexpression("+2 ** (-3)") == 0.125);
    printf("Assert 14 passed\n");
    assert(evalexpression("-(+2) * (+3) - (-4) / (-5)") == -6.8);
    printf("Assert 15 passed\n");
    assert(evalexpression("1") == 2);
    printf("Assert 16 passed\n");
}

int main() {
    printf("Input please: ");

    char expression[100];
    scanf("%s", expression);  // Correct format specifier for strings

    if (strcmp(expression, "test") == 0) { // if 'test' is entered, run tests
        test();
        return 0;
    }

    float result = evalexpression(expression);

    if (!errorFlag){
        printf("%.3f", result);
    }
}
