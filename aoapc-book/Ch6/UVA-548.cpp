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
#include <limits.h>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;

using uint_64 = unsigned long long;
using int_64 = long long;
using uint = unsigned int;


struct sub_tree
{
    int l_in, r_in;
    int l_po, r_po;
    int cnt_nodes;
    uint value_path;
};

int main()
{
    const int max_len = 10000;
    int postorder[max_len];
    map<int, int> m_in;
    
    string line;
    while (getline(cin, line))
    {
        m_in.clear();

        stringstream ss(line);
        int n = 0, tmp;
        while (ss >> tmp) 
        {
            m_in[tmp] = n++;
        }

        getline(cin, line);
        ss = stringstream(line);
        REP(i, n) 
        {
            ss >> tmp;
            postorder[i] = tmp;
        }

        int res = -1;
        uint value_min = UINT_MAX; 
        queue<sub_tree> traver;
        traver.push({0, n - 1, 0, n - 1, n, 0});

        while (!traver.empty())
        {
            sub_tree cur = traver.front(); traver.pop();
            int root_val = postorder[cur.r_po];
            uint value_path_child = root_val + cur.value_path;

            if (cur.cnt_nodes == 1)
            {
                if (value_path_child < value_min)
                {
                    value_min = value_path_child;
                    res = root_val;
                }
                else if(value_path_child == value_min)
                {
                    res = min(res, root_val);
                }
                continue;
            }

            int root_in = m_in[root_val];

            int l_cnt = root_in - cur.l_in;
            int r_cnt = cur.r_in - root_in;

            if (l_cnt > 0)
            {
                traver.push({
                    cur.l_in, root_in - 1, 
                    cur.l_po, cur.l_po + l_cnt - 1,
                    l_cnt,    value_path_child
                });
            }
            if (r_cnt > 0)
            {
                traver.push({
                    root_in + 1,       cur.r_in,
                    cur.l_po + l_cnt,  cur.r_po - 1,
                    r_cnt,             value_path_child
                });
            }
        }

        cout << res << endl;
    }


    
    return 0;
}