#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)

int main()
{
    set<vector<int>> s;
    int kase_cnt, n;

    cin >> kase_cnt;
    REP(kase, kase_cnt)
    {
        cin >> n;
        vector<int> v(n);
        REP(i, n)
        {
            cin >> v[i];
        }

        s.clear();
        while(true)
        {
            if (count(v.begin(), v.end(), 0) == n)
            {
                cout << "ZERO\n";
                break;
            }
            if (s.count(v))
            {
                cout << "LOOP\n";
                break;
            }
            s.insert(v);

            int tmp = v[0];
            REP(i, n - 1)
            {
                v[i] = abs(v[i] - v[i + 1]);
            }
            v[n - 1] = abs(v[n - 1] - tmp);
        }
    }
    return 0;
}