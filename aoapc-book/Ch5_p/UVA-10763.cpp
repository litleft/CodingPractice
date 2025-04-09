#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    int n;
    unordered_map<int,int> s, d;

    while (cin >> n && n != 0)
    {
        s.clear();
        d.clear();

        int orig, dest;
        for (int i = 0; i < n; i++)
        {
            cin >> orig >> dest;
            if (s.find(dest) != s.end())
            {
                s[dest]--;
                if (s[dest] == 0)
                {
                    s.erase(dest);
                }
            }
            else
            {
                d[dest]++;
            }
            if (d.find(orig) != d.end())
            {
                d[orig]--;
                if (d[orig] == 0)
                {
                    d.erase(orig);
                }
            }
            else
            {
                s[orig]++;
            }
        }

        cout << (s.empty() && d.empty() ? "YES" : "NO") << endl;
    }
    return 0;
}