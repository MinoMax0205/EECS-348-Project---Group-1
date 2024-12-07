#include <string>   // for string

using namespace std;

class InToPost {
    private:
        static int processExponents(std::string &input);
        static bool isOperator(char op);
        static int precedence(char op);
public:
    static string infixToPostfix(string infix);
};