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
#include <deque>
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

int n, m;
vector<vector<int>> edge;

bool circle;
deque<int> res;
vector<bool> visited;
vector<bool> in_stack;

void dfs(int i)
{
    if (circle) return;

    if (in_stack[i])
    {
        circle = true;
        return;
    }

    in_stack[i] = true;
    REP(e, edge[i].size())
    {
        int j = edge[i][e];
        if (visited[j])
            continue;
        dfs(j);
    }
    in_stack[i] = false;
    visited[i] = true;
    res.push_front(i);
}

int main()
{
    while (cin >> n >> m && (n != 0 || m != 0))
    {
        edge.clear();
        edge.resize(n);
        REP(i, m)
        {
            int a, b;
            cin >> a >> b;
            edge[a - 1].push_back(b - 1);
        }

        res.clear();
        circle = false;
        visited.clear();
        visited.resize(n, false);
        in_stack.clear();
        in_stack.resize(n, false);
        REP(i, n)
        {
            if (visited[i])
                continue;
            dfs(i);
        }

        while (true)
        {
            int i = res.front(); res.pop_front();
            cout << i + 1;
            if (!res.empty())
                cout << " ";
            else
            {
                cout << endl;
                break;
            }
        }
    }

    return 0;
}