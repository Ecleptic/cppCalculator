/**
 * Infix to postfix
 * only '+', '-', '*', and '/' operators
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

vector<string> parseInput(string expression);
vector<string> infixToPostfix(vector<string> vector);
bool isNumber(string numberExpression);
bool isOperator(string s);
string calc(vector<string> postfix);

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

    vector<string> output;


    for (int x = 0; x != expression.size(); x++) {
        if (isNumber(expression[x])) {
            output.push_back(expression[x]);
        } else if (isOperator(expression[x])) {
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
                            S.pop();
                            S.push(op);
                            checkAgain = false;
                        }
                    } else if (op == "+" || op == "-") {
                        output.push_back(top);
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
            // do nothing
        } else {
            tempString += currentChar;
        }
        if (i == expression.length() - 1) {
            inputVector.push_back(tempString);
        }
    }
    return inputVector;
}
