#include <string>   // for string


using namespace std;

class Evaluator {
    private:
        static double performOperation(const string &op, double a, double b);
        static double PerformUnaryExpression(const string &op, double operand);
        static bool isOperator(char op);
    public:
        static float evalexpression(const string &expression);
};