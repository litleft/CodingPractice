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

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;

using uint_64 = unsigned long long;
using int_64 = long long;
using uint = unsigned int;


int main()
{
    int cnt_case;
    cin >> cnt_case;

    int depth, i;
    REP(no_case, cnt_case)
    {
        cin >> depth >> i;

        int cur_depth = 1;
        int position = 0; // 这里是叶子节点从左到右的位置

        // TIPS 如果经过某个节点时，是该节点的奇数次个小球，则向左；否则向右
        //      据此直接模拟第I次的下落路径
        while (cur_depth < depth)
        {
            int depth_child = depth - cur_depth;
            if (i % 2 == 1)
            {
                // 向左落下
                i = (i + 1) / 2;
            }
            else
            {
                // 向右落下
                i = i / 2;
                position += (1 << (depth_child - 1));
            }
            cur_depth++;
        }

        int id_fisrt_leaf = ((1 << (depth - 1)) - 1) + 1;
        int p = position + id_fisrt_leaf;
        cout << p << endl;
    }
}