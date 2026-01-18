#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cout << "Enter a String: ";
    getline(cin, str);
    int count = 0;

    string operators[] = {
        "==", "!=", "<=", ">=", "&&", "||",
        "+=", "-=", "*=", "/=", "%=",
        "+", "-", "*", "/", "%", "<", ">", "=", "!"
    };

    for (int i = 0; i < str.length(); i++)
    {
        for (string op : operators)
        {
            if (str.substr(i, op.length()) == op)
            {
                count++;
                i += op.length() - 1;
                break;   
            }
        }
    }

    cout << "Total Operators in the string: " << count << endl;
    return 0;
}
