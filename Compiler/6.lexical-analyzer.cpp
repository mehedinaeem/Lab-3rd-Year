#include <bits/stdc++.h>
using namespace std;

bool isOperator(const string &op) {
    // List of valid operators
    vector<string> operators = {
        "+", "-", "*", "/", "%",       // Arithmetic
        "=", "+=", "-=", "*=", "/=", "%=", // Assignment
        "==", "!=", "<", ">", "<=", ">=",  // Relational
        "&&", "||", "!"                // Logical
    };

    // Check if input matches any valid operator
    for (string validOp : operators) {
        if (op == validOp) return true;
    }
    return false;
}

int main() {
    string op;
    cout << "Enter an operator: ";
    cin >> op;

    if (isOperator(op))
        cout << op << " is a valid operator";
    else
        cout << op << " is NOT a valid operator";

    return 0;
}
