#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int m, n, case_no = 0, ary[10000];

    while (cin >> m >> n)
    {
        if (m == 0 && n == 0) break;

        for (int i = 0; i < m; i++)
        {
            cin >> ary[i];
        }

        cout << "CASE# " << ++case_no << ":\n";
        sort(ary, ary + m);

        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            int p = lower_bound(ary, ary + m, x) - ary;
            if (p == m || ary[p] != x)
            {
                cout << x << " not found\n";
            }
            else
            {
                cout << x << " found at " << p + 1 << endl;
            }
        }

    }
}