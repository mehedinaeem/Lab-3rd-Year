#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input.txt");

    char ch;
    int count_ch = 0, count_words = 0, count_lines = 0;

    while (file.get(ch))
    {
        count_ch++;

        if (ch == ' ' || ch == '\n')
        {
            count_words++;
        }

        if (ch == '\n')
        {
            count_lines++;
        }
    }

    count_words++;
    count_lines++;

    cout << "Number of characters: " << count_ch << endl;
    cout << "Number of words: " << count_words << endl;
    cout << "Number of lines: " << count_lines << endl;

    return 0;
}
