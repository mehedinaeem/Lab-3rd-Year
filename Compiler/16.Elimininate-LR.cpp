#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "Enter number of non-terminals: ";
    cin >> n;

    vector<char> NT(n);
    vector<vector<string>> P(n);

    // Input grammar
    for (int i = 0; i < n; i++) {
        cout << "\nEnter non-terminal: ";
        cin >> NT[i];

        int k;
        cout << "Number of productions for " << NT[i] << ": ";
        cin >> k;

        cout << "Enter productions (use ^ for epsilon):\n";
        for (int j = 0; j < k; j++) {
            string s;
            cin >> s;
            P[i].push_back(s);
        }
    }

    cout << "\nGrammar after removing left recursion:\n";

    // Remove left recursion
    for (int i = 0; i < n; i++) {
        vector<string> alpha, beta;

        // Separate left-recursive and non-left-recursive productions
        for (string prod : P[i]) {
            if (prod[0] == NT[i]) {
                alpha.push_back(prod.substr(1)); // A -> Aα
            } else {
                beta.push_back(prod);             // A -> β
            }
        }

        // If no left recursion, print as is
        if (alpha.empty()) {
            cout << NT[i] << " -> ";
            for (int j = 0; j < beta.size(); j++) {
                cout << beta[j];
                if (j != beta.size() - 1) cout << " | ";
            }
            cout << endl;
            continue;
        }

        // Create new non-terminal A'
        char newNT = NT[i] + 1;

        // A -> βA'
        cout << NT[i] << " -> ";
        for (int j = 0; j < beta.size(); j++) {
            cout << beta[j] << newNT;
            if (j != beta.size() - 1) cout << " | ";
        }
        cout << endl;

        // A' -> αA' | ε
        cout << newNT << " -> ";
        for (int j = 0; j < alpha.size(); j++) {
            cout << alpha[j] << newNT << " | ";
        }
        cout << "^" << endl;
    }

    return 0;
}


/* Example Input:
Enter number of non-terminals: 1

Enter non-terminal: A
Number of productions for A: 2
Enter productions (use ^ for epsilon):
Aa
b

Grammar after removing left recursion:
A -> bB
B -> aB | ^ */