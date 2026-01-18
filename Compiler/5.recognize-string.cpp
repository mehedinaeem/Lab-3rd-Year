#include <bits/stdc++.h>
using namespace std;

// Function to check pattern "a"
bool isA(const string &s) {
    return s == "a";
}

// Function to check pattern "a*b+"
bool isAStarBPlus(const string &s) {
    int i = 0;
    int n = s.length();

    // Count leading 'a's
    while (i < n && s[i] == 'a') i++;

    // There must be at least one 'b' after 'a's
    if (i == n) return false;

    // Check remaining characters are all 'b'
    for (; i < n; i++) {
        if (s[i] != 'b') return false;
    }

    return true;
}

// Function to check pattern "abb"
bool isABB(const string &s) {
    return s == "abb";
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    if (isA(s))
        cout << "String matches pattern 'a'";
    else if (isAStarBPlus(s))
        cout << "String matches pattern 'a*b+'";
    else if (isABB(s))
        cout << "String matches pattern 'abb'";
    else
        cout << "String does not match any pattern";

    return 0;
}
