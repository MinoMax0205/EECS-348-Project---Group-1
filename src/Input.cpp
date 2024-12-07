#include "Input.hpp"
#include <string>
#include <iostream>

using namespace std;

string Input::getInput() {
        string expression;
        cout << "Enter an expression: ";
        getline(cin, expression);
        return expression;
    }
