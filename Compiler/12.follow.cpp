#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
set<char> nonTerminals;
char startSymbol;

// Function to compute FIRST sets (needed for FOLLOW)
void findFirst(char symbol) {
    if (!FIRST[symbol].empty())
        return;

    for (string prod : grammar[symbol]) {
        if (prod == "#") {
            FIRST[symbol].insert('#');
            continue;
        }

        for (int i = 0; i < prod.length(); i++) {
            char ch = prod[i];

            if (!isupper(ch)) {
                FIRST[symbol].insert(ch);
                break;
            } else {
                findFirst(ch);

                for (char c : FIRST[ch])
                    if (c != '#')
                        FIRST[symbol].insert(c);

                if (FIRST[ch].find('#') == FIRST[ch].end())
                    break;

                if (i == prod.length() - 1)
                    FIRST[symbol].insert('#');
            }
        }
    }
}

// Function to compute FOLLOW sets
void findFollow() {
    // Rule 1: Add $ to FOLLOW(start symbol)
    FOLLOW[startSymbol].insert('$');

    bool updated = true;

    while (updated) {
        updated = false;

        for (auto g : grammar) {
            char lhs = g.first;

            for (string prod : g.second) {
                for (int i = 0; i < prod.length(); i++) {
                    char B = prod[i];

                    if (isupper(B)) {
                        bool epsilonNext = true;

                        // Rule 2: A → αBβ
                        for (int j = i + 1; j < prod.length(); j++) {
                            char beta = prod[j];

                            if (!isupper(beta)) {
                                if (FOLLOW[B].insert(beta).second)
                                    updated = true;
                                epsilonNext = false;
                                break;
                            } else {
                                for (char c : FIRST[beta])
                                    if (c != '#' && FOLLOW[B].insert(c).second)
                                        updated = true;

                                if (FIRST[beta].find('#') == FIRST[beta].end()) {
                                    epsilonNext = false;
                                    break;
                                }
                            }
                        }

                        // Rule 3: A → αB or A → αBβ where FIRST(β) contains ε
                        if (epsilonNext) {
                            for (char c : FOLLOW[lhs])
                                if (FOLLOW[B].insert(c).second)
                                    updated = true;
                        }
                    }
                }
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
        if (i == 0) startSymbol = lhs;

        nonTerminals.insert(lhs);
        string rhs = prod.substr(2), temp = "";

        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(temp);
                temp.clear();
            } else {
                temp += c;
            }
        }
        grammar[lhs].push_back(temp);
    }

    // Compute FIRST sets first
    for (char nt : nonTerminals)
        findFirst(nt);

    // Compute FOLLOW sets
    findFollow();

    // Display FOLLOW sets
    cout << "\nFOLLOW Sets:\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char c : FOLLOW[nt])
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
F=i|(E) */
