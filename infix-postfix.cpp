/**
 * Infix to postfix
 * only '+', '-', '*', and '/' operators
 */
#include <iostream> // allows I/O, cin, cout, etc.
#include <stack>    // can make stack... duh
#include <string>   // can make variables to be strings
#include <vector>


// lets us just write 'string' instead of 'std::string'
using namespace std;

/**
 * Declare functions before main.
 */

// add pound signs after operators
vector<string> parseInput(string expression);

vector<string> infixToPostfix(vector<string> vector);

bool isNumber(string numberExpression);

bool isOperator(string s);

string calc(vector<string> postfix);

/**
 * MAIN
 */
int main() {
    string expresion;
    cout << "enter Infix expression \n";
    getline(cin, expresion);
    vector<string> input = parseInput(expresion);
    vector<string> postfix = infixToPostfix(input);

    for (int x = 0; x != postfix.size(); x++) {
        cout << postfix[x] << ", ";
    }
    cout << "\n";

    string calculated = calc(postfix);


    cout << "output = " << calculated << "\n";
}

string calc(vector<string> postfix) {
    stack<string> S;

    for (int x = 0; x != postfix.size(); x++) {

        /**
         *  if number, push into stack
         *  if operator pop top 2 off stack
         *      - 2nd pop (operator) 1st op
         *      - push result onto stack
         *  if end of operations,
         *      - pop off of stack  = returned answer.
         *
         */

        if (isNumber(postfix[x])) {
            S.push(postfix[x]);
        } else if (isOperator(postfix[x])) {
            int a = stoi(S.top());
            S.pop();
            int b = stoi(S.top());
            S.pop();

            if (postfix[x] == "+") {
                string result = to_string(b + a);
                S.push(result);
            } else if (postfix[x] == "-") {
                string result = to_string(b - a);
                S.push(result);
            } else if (postfix[x] == "*") {
                string result = to_string(b * a);
                S.push(result);
            } else if (postfix[x] == "/") {
                string result = to_string(b / a);
                S.push(result);
            } else {
                cout << "something's wrong...";
            }

        } else {
            cout << "something else is wrong...";
        }
    }
    return S.top();
}


vector<string> infixToPostfix(vector<string> expression) {

    stack<string> S;

    vector<string> output; // initialize the postfix


    for (int x = 0; x != expression.size(); x++) {
        if (isNumber(expression[x])) {
            output.push_back(expression[x]);

//            output += expression[x];
        } else if (isOperator(expression[x])) {
            /**
                * If stack is empty:
                *      - send new op to stack
                * else:
                *      - if new operator is '*' or '/':
                *          - if top of stack is '+' or '-':
                *              - push new op into stack
                *          - if top of stack is '*' or '/'
                *              - pop off top
                *              - push new op onto stack
                *              -- check again.
                *      - if new operator is '+' or '-':
                *
                *          - if top of stack is '+' or '-':
                *              - pop off top
                *              - push new op onto stack
                *      - if end, pop all operators off
                */

            bool checkAgain = true;
            while (checkAgain) {

                if (S.empty()) {
                    S.push(expression[x]);
                    checkAgain = false;
                } else {
                    string top = S.top();
                    string op = expression[x];
                    if (op == "*" || op == "/") {
                        if (top == "+" || top == "-") {
                            S.push(op);
                            checkAgain = false;

                        } else if (top == "*" || top == "/") {
                            output.push_back(top);

//                            output += top;
                            S.pop();
                            S.push(op);
                            checkAgain = false;
                        }

                    } else if (op == "+" || op == "-") {
                        output.push_back(top);
//                        output += top;
                        S.pop();
                    } else {
                        cout << "I made an error somewhere\n";
                        cout << "Top: " << top << " Op: " << expression[x] << "\n";
                        checkAgain = false;
                    }
                }
            }
        }

        if (x == expression.size() - 1) {
            while (!S.empty()) {
                output.push_back(S.top());
//                output += S.top();
                S.pop();
            }
        }
    }
    return output;
}

bool isNumber(string numberExpression) {
    bool isANumber = false;


    for (char i : numberExpression) {
        if (isdigit(i))
            isANumber = true;
    }
    return isANumber;
}


bool isOperator(string input) {
    return input == "+" || input == "-" || input == "*" || input == "/";
}


/*
 *  if current char == number and lookahead is number, push current char to tempstring
 *  if current char == operator: push tempstring, then push current char into inputVector, then wipe tempstring
 */
vector<string> parseInput(string expression) {
    vector<string> inputVector;

    string tempString = "";

    for (int i = 0; i < expression.length(); ++i) {
        char currentChar = expression[i];

        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            inputVector.push_back(tempString);
            inputVector.push_back(string(1, currentChar));
            tempString = "";

        } else if (currentChar == ' ' || currentChar == ',') {
//            do nothing
        } else {
            tempString += currentChar;
        }
        if (i == expression.length() - 1) {
            inputVector.push_back(tempString);

        }

    }
    return inputVector;
}
