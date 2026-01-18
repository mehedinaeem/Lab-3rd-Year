#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
map<pair<char,char>, string> table;
set<char> nonTerminals, terminals;
char startSymbol;

/* ---------- FIRST ---------- */
void findFirst(char X) {
    for (string prod : grammar[X]) {
        if (prod == "#") {
            FIRST[X].insert('#');
            continue;
        }

        bool allEpsilon = true;
        for (char c : prod) {
            if (!isupper(c)) {
                FIRST[X].insert(c);
                allEpsilon = false;
                break;
            } else {
                if (FIRST[c].empty()) findFirst(c);
                for (char f : FIRST[c])
                    if (f != '#') FIRST[X].insert(f);

                if (!FIRST[c].count('#')) {
                    allEpsilon = false;
                    break;
                }
            }
        }
        if (allEpsilon) FIRST[X].insert('#');
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

/* ---------- Parsing Table ---------- */
void buildParsingTable() {
    for (auto g : grammar) {
        char A = g.first;
        for (string prod : g.second) {
            set<char> firstAlpha;
            
            if (prod == "#") {
                firstAlpha.insert('#');
            } else {
                bool allEpsilon = true;
                for (char c : prod) {
                    if (!isupper(c)) {
                        firstAlpha.insert(c);
                        allEpsilon = false;
                        break;
                    } else {
                        for (char f : FIRST[c])
                            if (f != '#') firstAlpha.insert(f);
                        if (!FIRST[c].count('#')) {
                            allEpsilon = false;
                            break;
                        }
                    }
                }
                if (allEpsilon) firstAlpha.insert('#');
            }

            for (char t : firstAlpha) {
                if (t != '#') {
                    if (!table.count({A, t})) {
                        table[{A, t}] = prod;
                    }
                }
            }

            if (firstAlpha.count('#')) {
                for (char f : FOLLOW[A]) {
                    if (!table.count({A, f})) {
                        table[{A, f}] = prod;
                    }
                }
            }
        }
    }
}

/* ---------- LL(1) Parser ---------- */
bool parseInput(string input) {
    stack<char> st;
    st.push('$');
    st.push(startSymbol);
    input += "$";

    int ptr = 0;

    cout << "\nParsing Steps:\n";
    cout << "Stack\t\tInput\t\tAction\n";

    while (!st.empty()) {
        string stackContent = "";
        stack<char> temp = st;
        while (!temp.empty()) {
            stackContent += temp.top();
            temp.pop();
        }

        string inputLeft = input.substr(ptr);

        char top = st.top();
        char current = input[ptr];

        if (top == current && top == '$') {
            cout << stackContent << "\t\t" << inputLeft << "\t\tAccept\n";
            return true;
        }

        if (!isupper(top)) { // terminal
            if (top == current) {
                cout << stackContent << "\t\t" << inputLeft << "\t\tMatch " << top << "\n";
                st.pop();
                ptr++;
            } else {
                cout << stackContent << "\t\t" << inputLeft << "\t\tError! Expected " << top << "\n";
                return false;
            }
        } else { // non-terminal
            if (table.count({top, current})) {
                string prod = table[{top, current}];
                cout << stackContent << "\t\t" << inputLeft << "\t\t" << top << "->" << prod << "\n";
                st.pop();
                if (prod != "#") {
                    for (int i = prod.size()-1; i >= 0; i--)
                        st.push(prod[i]);
                }
            } else {
                cout << stackContent << "\t\t" << inputLeft << "\t\tError! No rule\n";
                return false;
            }
        }
    }
    return false;
}

/* ---------- MAIN ---------- */
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use # for epsilon):\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        
        // Parse: A->alpha|beta|gamma
        int arrowPos = s.find("->");
        char lhs = s[arrowPos - 1];  // Get the character before ->
        
        if (i == 0) startSymbol = lhs;
        nonTerminals.insert(lhs);

        string rhs = s.substr(arrowPos + 2);  // Everything after ->
        string temp = "";
        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(temp);
                temp.clear();
            } else temp += c;
        }
        grammar[lhs].push_back(temp);
    }

    // Collect terminals
    for (auto g : grammar)
        for (string p : g.second)
            for (char c : p)
                if (!isupper(c) && c != '#')
                    terminals.insert(c);
    terminals.insert('$');

    // Compute FIRST and FOLLOW
    for (char nt : nonTerminals) findFirst(nt);
    findFollow();
    
    // Debug: Print FIRST and FOLLOW sets
    cout << "\n=== FIRST Sets ===\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = {";
        for (char f : FIRST[nt]) cout << f << " ";
        cout << "}\n";
    }
    
    cout << "\n=== FOLLOW Sets ===\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = {";
        for (char f : FOLLOW[nt]) cout << f << " ";
        cout << "}\n";
    }
    
    buildParsingTable();
    
    cout << "\n=== Parsing Table ===\n";
    for (auto entry : table) {
        cout << "[" << entry.first.first << ", " << entry.first.second << "] = " << entry.second << "\n";
    }

    cout << "\nEnter input string to parse: ";
    string input;
    cin >> input;

    bool success = parseInput(input);
    if (success)
        cout << "\nInput string is Accepted by the Grammar.\n";
    else
        cout << "\nInput string is Rejected by the Grammar.\n";

    return 0;
}

/*Enter number of productions: 5
Enter productions (use # for epsilon):
E->TX
X->+TX|#
T->FY
Y->*FY|#
F->(E)|i

=== FIRST Sets ===
FIRST(E) = {( i }
FIRST(F) = {( i }
FIRST(T) = {( i }
FIRST(X) = {# + }
FIRST(Y) = {# * }

=== FOLLOW Sets ===
FOLLOW(E) = {$ ) }
FOLLOW(F) = {$ ) * + }
FOLLOW(T) = {$ ) + }
FOLLOW(X) = {$ ) }
FOLLOW(Y) = {$ ) + }

=== Parsing Table ===
[E, (] = TX
[E, i] = TX
[F, (] = (E)
[F, i] = i
[T, (] = FY
[T, i] = FY
[X, $] = #
[X, )] = #
[X, +] = +TX
[Y, $] = #
[Y, )] = #
[Y, *] = *FY
[Y, +] = #

Enter input string to parse: i+i*i

Parsing Steps:
Stack           Input           Action
E$              i+i*i$          E->TX
TX$             i+i*i$          T->FY
FYX$            i+i*i$          F->i
iYX$            i+i*i$          Match i
YX$             +i*i$           Y->#
X$              +i*i$           X->+TX
+TX$            +i*i$           Match +
TX$             i*i$            T->FY
FYX$            i*i$            F->i
iYX$            i*i$            Match i
YX$             *i$             Y->*FY
*FYX$           *i$             Match *
FYX$            i$              F->i
iYX$            i$              Match i
YX$             $               Y->#
X$              $               X->#
$               $               Accept

Input string is Accepted by the Grammar.*/
