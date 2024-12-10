#include "Input.hpp"
#include <string>
#include <iostream>

using namespace std;

string Input::getInput() {    // gets and returns the users input to the main
        string expression;
        cout << "Enter an expression: ";    
        getline(cin, expression);
        return expression;
    }
