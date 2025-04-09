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

const int max_pile = 80;
const int max_pile_2 = 128; // 2^7
const int mid_pile = max_pile_2 / 2;

struct node
{
    int num_child;
    int pile;
};

int main()
{
    int sum[max_pile_2];
    int val, min_p, no_case = 0;
    stack<node> s;

    while (cin >> val && val != -1)
    {
        no_case++;
        min_p = mid_pile;
        memset(sum, 0, 4 * max_pile_2);

        sum[mid_pile] += val;
        s.push({0, mid_pile});

        while (!s.empty())
        {
            cin >> val;
            if (val == -1)
            {
                while (!s.empty() && s.top().num_child++ == 1)
                {
                    s.pop();
                }
            }
            else
            {
                node& n = s.top();
                int p = n.pile + (n.num_child == 0 ? -1 : 1);
                sum[p] += val;
                s.push({0, p});
                min_p = min(min_p, p);
            }
        }

        printf("Case %d:\n", no_case);
        bool first_print = true;
        FOR(i, min_p, max_pile_2 - 1)
        {
            if (sum[i] != 0)
            {
                if (first_print)
                {
                    first_print = false;
                }
                else
                {
                    cout << " ";
                }
                cout << sum[i];
            }
        }
        cout << endl << endl;
    }

    return 0;
}