#include <bits/stdc++.h>
using namespace std;

// Function to simulate NFA for identifier
bool isIdentifier(const string &s) {
    int state = 0; // q0: start

    for (char ch : s) {
        switch(state) {
            case 0: // q0: expecting first char
                if (isalpha(ch) || ch == '_')
                    state = 1; // move to q1
                else
                    return false; // invalid first char
                break;
            case 1: // q1: accepting state, can have letters, digits, _
                if (isalnum(ch) || ch == '_')
                    state = 1; // stay in q1
                else
                    return false; // invalid character
                break;
        }
    }

    return state == 1; // accept if in q1
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    if (isIdentifier(s))
        cout << s << " is a valid identifier";
    else
        cout << s << " is NOT a valid identifier";

    return 0;
}
