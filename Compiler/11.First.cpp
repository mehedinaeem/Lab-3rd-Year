#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST;
set<char> nonTerminals;

// Function to calculate FIRST of a symbol
void findFirst(char symbol) {
    // If FIRST already computed, return
    if (!FIRST[symbol].empty())
        return;

    for (string production : grammar[symbol]) {
        // If production starts with epsilon
        if (production == "#") {
            FIRST[symbol].insert('#');
            continue;
        }

        for (int i = 0; i < production.length(); i++) {
            char ch = production[i];

            // If terminal
            if (!isupper(ch)) {
                FIRST[symbol].insert(ch);
                break;
            }
            // If non-terminal
            else {
                findFirst(ch);

                // Add FIRST(ch) except epsilon
                for (char c : FIRST[ch]) {
                    if (c != '#')
                        FIRST[symbol].insert(c);
                }

                // If epsilon not in FIRST(ch), stop
                if (FIRST[ch].find('#') == FIRST[ch].end())
                    break;

                // If last symbol and epsilon exists
                if (i == production.length() - 1)
                    FIRST[symbol].insert('#');
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use # for epsilon):\n";

    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;

        char lhs = prod[0];
        nonTerminals.insert(lhs);

        string rhs = prod.substr(2);
        string temp = "";

        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        grammar[lhs].push_back(temp);
    }

    // Compute FIRST for each non-terminal
    for (char nt : nonTerminals)
        findFirst(nt);

    // Display FIRST sets
    cout << "\nFIRST Sets:\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (char c : FIRST[nt])
            cout << c << " ";
        cout << "}\n";
    }

    return 0;
}


/* Enter number of productions: 5
Enter productions (use # for epsilon):
E=TR
R=+TR|#
T=FY
Y=*FY|#
F=i|(E)

FIRST Sets:
FIRST(E) = { ( i }
FIRST(F) = { ( i }
FIRST(R) = { # + }
FIRST(T) = { ( i }
FIRST(Y) = { # * } */