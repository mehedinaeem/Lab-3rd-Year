/**
 * PROBLEM:
 * Design a lexical analyzer for the given language.
 * The lexical analyzer should ignore redundant spaces,
 * tabs, new lines, comments etc.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
using namespace std;

/* ---------- KEYWORDS ---------- */
vector<string> keywords = {
    "int", "float", "double", "char",
    "if", "else", "for", "while", "do",
    "return", "void","main"};

/* ---------- OPERATORS ---------- */
vector<string> operators = {
    "+", "-", "*", "/", "%", "=",
    "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!", "+=", "-=", "*=", "/="};

/* ---------- SEPARATORS ---------- */
vector<char> separators = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.'};

/* ---------- CHECK FUNCTIONS ---------- */
bool isKeyword(const string &s)
{
    for (auto k : keywords)
        if (k == s)
            return true;
    return false;
}

bool isOperator(const string &s)
{
    for (auto op : operators)
        if (op == s)
            return true;
    return false;
}

bool isSeparator(char c)
{
    for (char s : separators)
        if (s == c)
            return true;
    return false;
}

bool isIdentifier(const string &s)
{
    if (s.empty())
        return false;
    if (!(isalpha(s[0]) || s[0] == '_'))
        return false;

    for (char c : s)
        if (!(isalnum(c) || c == '_'))
            return false;
   
    return true;
}

bool isConstant(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
        if (!isdigit(c))
            return false;
    return true;
}

/* ---------- MAIN ---------- */
int main()
{
    ifstream file("lab10.txt"); // input file
    string line, code = "";

    if (!file.is_open())
    {
        cout << "Error: 10.c file not found!" << endl;
        return 0;
    }

    /* Read entire file */
    while (getline(file, line))
        code += line + '\n';

    file.close();

    /* Lexical Analysis */
    for (size_t i = 0; i < code.size();)
    {
        /* Ignore spaces, tabs, newlines */
        if (isspace(code[i]))
        {
            i++;
            continue;
        }

        /* Ignore single-line comments */
        if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '/')
        {
            while (i < code.size() && code[i] != '\n')
                i++;
            continue;
        }

        /* Ignore multi-line comments */
        if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '*')
        {
            i += 2;
            while (i + 1 < code.size() &&
                   !(code[i] == '*' && code[i + 1] == '/'))
                i++;
            i += 2;
            continue;
        }

        /* Check 2-character operators */
        if (i + 1 < code.size())
        {
            string twoChar = code.substr(i, 2);
            if (isOperator(twoChar))
            {
                cout << "Operator: " << twoChar << endl;
                i += 2;
                continue;
            }
        }

        /* Check 1-character operator */
        string oneChar(1, code[i]);
        if (isOperator(oneChar))
        {
            cout << "Operator: " << oneChar << endl;
            i++;
            continue;
        }

        /* Check separator */
        if (isSeparator(code[i]))
        {
            cout << "Separator: " << code[i] << endl;
            i++;
            continue;
        }

        /* Extract token */
        string token = "";
        while (i < code.size() &&
               !isspace(code[i]) &&
               !isOperator(string(1, code[i])) &&
               !isSeparator(code[i]))
        {
            token += code[i];
            i++;
        }

        /* Classify token */
        if (isKeyword(token))
            cout << "Keyword: " << token << endl;
        else if (isIdentifier(token))
            cout << "Identifier: " << token << endl;
        else if (isConstant(token))
            cout << "Constant: " << token << endl;
        else
            cout << "Invalid token: " << token << endl;
    }

    return 0;
}