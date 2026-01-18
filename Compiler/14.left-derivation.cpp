#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<char, vector<string>> grammar;
vector<string> steps;
string target;

/* Check non-terminal */
bool isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

/* Find leftmost non-terminal */
int findLeftmost(const string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (isNonTerminal(s[i]))
            return i;
    }
    return -1;
}

/* Parse grammar input */
void parseGrammar(const string &input) {
    for (int i = 0; i < input.length(); i++) {
        if (isNonTerminal(input[i]) &&
            i + 2 < input.length() &&
            input[i + 1] == '-' &&
            input[i + 2] == '>') {

            char nt = input[i];
            i += 3;

            vector<string> rules;
            string rule = "";

            while (i < input.length() && input[i] != ',') {
                if (input[i] == '|') {
                    rules.push_back(rule);
                    rule.clear();
                } else if (input[i] != ' ') {
                    rule += input[i];
                }
                i++;
            }
            if (!rule.empty())
                rules.push_back(rule);

            grammar[nt] = rules;
        }
    }
}

/* Display grammar */
void showGrammar() {
    cout << "\n=== Grammar ===\n";
    for (auto &p : grammar) {
        cout << p.first << " -> ";
        for (int i = 0; i < p.second.size(); i++) {
            cout << p.second[i];
            if (i < p.second.size() - 1)
                cout << " | ";
        }
        cout << endl;
    }
}

/* Left-most derivation with pruning */
bool derive(string curr) {
    steps.push_back(curr);

    /* Pruning: stop useless growth */
    if (curr.length() > target.length() + 5) {
        steps.pop_back();
        return false;
    }

    int pos = findLeftmost(curr);

    /* No non-terminals left */
    if (pos == -1) {
        if (curr == target)
            return true;
        steps.pop_back();
        return false;
    }

    char nt = curr[pos];

    for (string rule : grammar[nt]) {
        string replacement = (rule == "#") ? "" : rule;
        string next = curr.substr(0, pos) + replacement + curr.substr(pos + 1);

        if (derive(next))
            return true;
    }

    steps.pop_back();
    return false;
}

/* Display derivation */
void showSteps() {
    cout << "\n=== Derivation ===\n";
    for (int i = 0; i < steps.size(); i++) {
        cout << steps[i];
        if (i < steps.size() - 1)
            cout << "\n=> ";
    }
    cout << endl;
}

int main() {
    string grammarInput;
    char start;

    cout << "Grammar: ";
    getline(cin, grammarInput);

    parseGrammar(grammarInput);
    showGrammar();

    cout << "\nStart: ";
    cin >> start;

    cout << "Target: ";
    cin >> target;

    steps.clear();
    string startString(1, start);

    if (derive(startString)) {
        cout << "\nSuccess!\n";
        showSteps();
    } else {
        cout << "\nFailed!\n";
    }

    return 0;
}

/* Example Input:
=== Grammar ===
S -> aS | b

Start: S
Target: aaab

Success!

=== Derivation ===
S
=> aS
=> aaS
=> aaaS
=> aaab */
