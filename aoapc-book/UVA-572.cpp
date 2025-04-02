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

int r, c;
char m[103][103];
int flag[103][103];

void dfs(int i, int j, int f)
{
    if (i < 0 || i >= r) return;
    if (j < 0 || j >= c) return;
    if (m[i][j] != '@') return;
    if (flag[i][j] != 0) return;

    flag[i][j] = f;
    FOR(dr, -1, 1)
    {
        FOR(dc, -1, 1)
        {
            if (dr != 0 || dc != 0)
            {
                dfs(i + dr, j + dc, f);
            }
        }
    }
}

int main()
{
    while (cin >> r >> c)
    {
        if (r == 0 && c == 0) break;
        
        REP(i, r)
        {
            scanf("%s", m[i]);
        }
        memset(flag, 0, 4 * 103 * 103);

        int cnt = 0;
        REP(i, r)
        {
            REP(j, c)
            {
                if (m[i][j] == '@' && flag[i][j] == 0)
                {
                    dfs(i, j, ++cnt);
                } 
            }
        }
        cout << cnt << endl;
    }


    return 0;
}