#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
map<pair<char,char>, string> table;
set<char> nonTerminals, terminals;
char startSymbol;

/* ---------- FIRST ---------- */
void findFirst(char X) {
    if (!FIRST[X].empty()) return;

    for (string prod : grammar[X]) {
        if (prod == "#") {
            FIRST[X].insert('#');
            continue;
        }

        for (char c : prod) {
            if (!isupper(c)) {
                FIRST[X].insert(c);
                break;
            } else {
                findFirst(c);
                for (char f : FIRST[c])
                    if (f != '#') FIRST[X].insert(f);

                if (!FIRST[c].count('#'))
                    break;
            }
        }
    }
}

/* ---------- FOLLOW ---------- */
void findFollow() {
    FOLLOW[startSymbol].insert('$');

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto g : grammar) {
            char A = g.first;
            for (string prod : g.second) {
                for (int i = 0; i < prod.size(); i++) {
                    char B = prod[i];
                    if (isupper(B)) {
                        bool epsilon = true;

                        for (int j = i + 1; j < prod.size(); j++) {
                            char beta = prod[j];
                            if (!isupper(beta)) {
                                changed |= FOLLOW[B].insert(beta).second;
                                epsilon = false;
                                break;
                            } else {
                                for (char f : FIRST[beta])
                                    if (f != '#')
                                        changed |= FOLLOW[B].insert(f).second;

                                if (!FIRST[beta].count('#')) {
                                    epsilon = false;
                                    break;
                                }
                            }
                        }

                        if (epsilon) {
                            for (char f : FOLLOW[A])
                                changed |= FOLLOW[B].insert(f).second;
                        }
                    }
                }
            }
        }
    }
}

/* ---------- MAIN ---------- */
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions:\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        char lhs = s[0];
        if (i == 0) startSymbol = lhs;
        nonTerminals.insert(lhs);

        string rhs = s.substr(2), temp = "";
        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(temp);
                temp.clear();
            } else temp += c;
        }
        grammar[lhs].push_back(temp);
    }

    for (auto g : grammar)
        for (string p : g.second)
            for (char c : p)
                if (!isupper(c) && c != '#')
                    terminals.insert(c);
    terminals.insert('$');

    for (char nt : nonTerminals)
        findFirst(nt);

    findFollow();

    for (auto g : grammar) {
        char A = g.first;
        for (string prod : g.second) {
            set<char> firstAlpha;

            if (prod == "#") firstAlpha.insert('#');
            else {
                for (char c : prod) {
                    if (!isupper(c)) {
                        firstAlpha.insert(c);
                        break;
                    } else {
                        for (char f : FIRST[c])
                            if (f != '#') firstAlpha.insert(f);

                        if (!FIRST[c].count('#')) break;
                    }
                }
            }

            for (char t : firstAlpha)
                if (t != '#')
                    table[{A, t}] = prod;

            if (firstAlpha.count('#'))
                for (char f : FOLLOW[A])
                    table[{A, f}] = "#";
        }
    }

    /* ---------- Display Table ---------- */
    cout << "\nLL(1) Parsing Table:\n\n";

    cout << setw(8) << " ";
    for (char t : terminals)
        cout << setw(8) << t;
    cout << "\n";

    for (char nt : nonTerminals) {
        cout << setw(8) << nt;
        for (char t : terminals) {
            if (table.count({nt, t}))
                cout << setw(8) << (string(1, nt) + "->" + table[{nt, t}]);
            else
                cout << setw(8) << "-";
        }
        cout << "\n";
    }

    return 0;
}


/* Enter number of productions: 5
Enter productions:E=TR
R=+TR|#
T=FY
Y=*FY|#
F=i|(E) */
