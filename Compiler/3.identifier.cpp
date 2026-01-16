#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cout << "Enter Identifier: ";
    getline(cin, str);

    bool valid = true;

    string keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

    for (string k : keywords)
    {
        if (str == k)
        {
            valid = false;
            break;
        }
    }

    if (!(isalpha(str[0]) || str[0] == '_'))
    {
        valid = false;
    }

    for(char c:str)
    {
        if(!(isalnum(c)|| c=='_'))
        {
            valid = false;
            break;
        }
    }



    if (valid)
        cout << "Valid Identifier" << endl;
    else
        cout << "Invalid Identifier" << endl;

    return 0;
}