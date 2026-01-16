#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream file("input.txt");   // Open file
    string line;
    int characters = 0, words = 0, lines = 0;

    if (!file)
    {
        cout << "File not found!" << endl;
        return 0;
    }

    while (getline(file, line))
    {
        lines++;                       // Count lines
        characters += line.length();  // Count characters

        bool inWord = false;
        for (char c : line)
        {
            if (c != ' ' && !inWord)
            {
                words++;
                inWord = true;
            }
            else if (c == ' ')
            {
                inWord = false;
            }
        }
    }

    file.close();

    cout << "Lines: " << lines << endl;
    cout << "Words: " << words << endl;
    cout << "Characters: " << characters << endl;

    return 0;
}
