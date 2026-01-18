/**
 * PROBLEM: 15. Write a C++ program to perform left factoring for a given grammar
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;

/* ---------- Helper: Longest Common Prefix ---------- */
string longestCommonPrefix(vector<string> &v)
{
    if (v.empty())
        return "";
    string prefix = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        int j = 0;
        while (j < prefix.length() && j < v[i].length() && prefix[j] == v[i][j])
            j++;
        prefix = prefix.substr(0, j);
        if (prefix == "")
            break;
    }
    return prefix;
}

int main()
{
    ifstream file("lab15.txt"); // read from file
    if (!file)
    {
        cout << "Error: input.txt not found\n";
        return 0;
    }

    int n;
    file >> n; // number of non-terminals

    map<char, vector<string>> grammar;

    for (int i = 0; i < n; i++)
    {
        char nt;
        int p;
        file >> nt >> p; // non-terminal and number of productions
        vector<string> prods;
        for (int j = 0; j < p; j++)
        {
            string prod;
            file >> prod;
            prods.push_back(prod);
        }
        grammar[nt] = prods;
    }

    file.close();

    map<char, vector<string>> newGrammar;
    char nextNT = 'Z';

    for (auto g : grammar)
    {
        char nt = g.first;
        vector<string> prods = g.second;

        string prefix = longestCommonPrefix(prods);

        if (prefix != "" && prods.size() > 1)
        {
            // Create new non-terminal
            char newNT = nextNT--;
            vector<string> suffixes;

            for (auto s : prods)
            {
                string suf = s.substr(prefix.length());
                if (suf == "")
                    suf = "e"; // epsilon
                suffixes.push_back(suf);
            }

            newGrammar[nt].push_back(prefix + newNT);
            newGrammar[newNT] = suffixes;
        }
        else
        {
            newGrammar[nt] = prods;
        }
    }

    /* ---------- Print Left-Factored Grammar ---------- */
    cout << "\nLeft-Factored Grammar:\n";
    for (auto g : newGrammar)
    {
        cout << g.first << " -> ";
        for (int i = 0; i < g.second.size(); i++)
        {
            cout << g.second[i];
            if (i != g.second.size() - 1)
                cout << " | ";
        }
        cout << endl;
    }

    return 0;
}



/* Example input in lab15.txt:
<number_of_nonterminals>
<Non-terminal_1> <num_productions> <prod1> <prod2> ... <prodN>
<Non-terminal_2> <num_productions> <prod1> <prod2> ... <prodN>
...


2
A 3 ab ac ad
B 2 x y


Left-Factored Grammar:
A -> aZ
B -> x | y
Z -> b | c | d*/