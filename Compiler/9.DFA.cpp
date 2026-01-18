#include <bits/stdc++.h>
using namespace std;

// Check if string is a valid identifier (DFA)
bool isIdentifier(const string &s) {
    if (s.empty()) return false;
    if (!(isalpha(s[0]) || s[0] == '_')) return false; // q0: first char
    for (char ch : s) {
        if (!(isalnum(ch) || ch == '_')) return false; // q1: rest chars
    }
    return true;
}

// Check if string is a constant (digits only)
bool isConstant(const string &s) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!isdigit(ch)) return false;
    }
    return true;
}

// Check if string is a valid operator
bool isOperator(const string &s) {
    vector<string> ops = {
        "==", "!=", "<=", ">=", "&&", "||", "+=", "-=", "*=", "/=", "%=",
        "+", "-", "*", "/", "%", "=", "<", ">", "!"
    };
    for (string op : ops) {
        if (s == op) return true;
    }
    return false;
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    if (isIdentifier(s))
        cout << s << " is an Identifier" << endl;
    else if (isConstant(s))
        cout << s << " is a Constant" << endl;
    else if (isOperator(s))
        cout << s << " is an Operator" << endl;
    else
        cout << s << " is NOT recognized" << endl;

    return 0;
}
