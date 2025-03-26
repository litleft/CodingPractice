#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;

using uint_64 = unsigned long long;
using int_64 = long long;
using uint = unsigned int;


struct mobile
{
    int wl, dl;
    int wr, dr;

    bool can_pop()
    {
        return wl != 0 && wr != 0;
    }

    bool is_balance()
    {
        return (wl * dl) == (wr * dr);
    }
};

int main()
{
    int cnt_case;
    cin >> cnt_case;
    REP(no_case, cnt_case)
    {
        if (no_case > 0) cout << endl;

        bool balance = true;
        stack<mobile> s;
        int needed = 1;
        while (needed > 0)
        {
            mobile m;
            cin >> m.wl >> m.dl >> m.wr >> m.dr;
            
            needed--;
            if (m.wl == 0) needed++;
            if (m.wr == 0) needed++;
            s.push(m);

            while (s.top().can_pop())
            {
                m = s.top(); s.pop();
                if (balance)
                {
                    balance = m.is_balance();
                }

                if (!s.empty())
                {
                    int w = m.wl + m.wr;
                    if (s.top().wl == 0) s.top().wl = w;
                    else if (s.top().wr == 0) s.top().wr = w;
                }
                else
                {
                    break;
                }
            }
        }

        cout << (balance ? "YES" : "NO") << endl;

    }

    return 0;
}