#include <iostream>
#include <set>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string buf;
    set<string> s;
    while (cin >> buf)
    {
        int b = 0;
        for (int i = 0; true; i++)
        {
            if (!isalpha(buf[i]))
            {
                if (b < i)
                {
                    s.insert(buf.substr(b, i - b));
                }
                b = i + 1;

                if (!buf[i]) break;
                continue;
            }
            buf[i] = tolower(buf[i]);
        }
    }

    for (auto p = s.begin(); p != s.end(); p++)
    {
        cout << *p << endl;
    }

    return 0;
}