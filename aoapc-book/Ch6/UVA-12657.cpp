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


struct linked_list
{
    static const int max_len = 100000 + 2;
    static const int head = 0;
    static const int tail = max_len - 1;

    bool rev = false;
    int next[max_len];
    int prev[max_len];

    void print_all()
    {
        cout << "List: " << rev << "  :";
        {
            int cur = head;
            while (cur != tail)
            {
                cur = next[cur];
                printf("%d ", cur);
            }
        }
        cout << "   REV ";
        {
            int cur = tail;
            while (cur != head)
            {
                cur = prev[cur];
                printf("%d ", cur);
            }
        }
        cout << endl;
    }

    uint_64 add_odd()
    {
        uint_64 res = 0;
        if (rev)
        {
            int node_cnt = 0;
            int cur = tail;
            while (cur != head)
            {
                if ((node_cnt % 2) > 0)
                {
                    res += cur;
                }
                cur = prev[cur];
                node_cnt++;
            }
        }
        else
        {
            int node_cnt = 0;
            int cur = head;
            while (cur != tail)
            {
                if ((node_cnt % 2) > 0)
                {
                    res += cur;
                }
                cur = next[cur];
                node_cnt++;
            }
        }
        return res;
    }

    void link(int a, int b) // a before b
    {
        if (rev)
        {
            prev[a] = b;
            next[b] = a;
        }
        else
        {
            next[a] = b;
            prev[b] = a;
        }
    }

    void break_node(int node)
    {
        int p = prev[node];
        int n = next[node];
        next[p] = n;
        prev[n] = p;
        next[p] = n;
        prev[n] = p;
    }

    int get_next_rev(int i)
    {
        if (rev) return prev[i];
        else return next[i];
    }

    void swap_node(int x, int y)
    {
        int nx = get_next_rev(x);
        if (nx == y)
        {
            insert_after(x, y);
            return;
        }
        int ny = get_next_rev(y);
        if (ny == x)
        {
            insert_after(y, x);
            return;
        }

        insert_before(x, ny);
        insert_before(y, nx);
    }

    void insert_after(int node, int des)
    {
        if (rev)
        {
            int p = prev[des];
            if (p == node) return;
            break_node(node);
            link(des, node);
            link(node, p);
        }
        else
        {
            int n = next[des];
            if (n == node) return;
            break_node(node);
            link(des, node);
            link(node, n);
        }
    }

    void insert_before(int node, int des)
    {
        if (rev)
        {
            int n = next[des];
            if (n == node) return;
            break_node(node);
            link(n, node);
            link(node, des);
        }
        else
        {
            int b = prev[des];
            if (b == node) return;
            break_node(node);
            link(b, node);
            link(node, des);
        }
    }
    
    void init(int n)
    {
        rev = false;
        FOR(i, 1, n)
        {
            next[i] = i + 1;
            prev[i] = i - 1;
        }
        next[head] = 1;
        next[n] = tail;
        prev[tail] = n;
    }
};

int main()
{
    int no_case = 0;
    int n, cnt_cmd;
    int cmd, x, y;
    linked_list l;
    while (cin >> n >> cnt_cmd)
    {
        l.init(n);

        REP(i, cnt_cmd)
        {
            cin >> cmd;
            switch (cmd)
            {
                case 1:
                {
                    cin >> x >> y;
                    l.insert_before(x, y);
                    break;
                }
                case 2:
                {
                    cin >> x >> y;
                    l.insert_after(x, y);
                    break;
                }
                case 3:
                {
                    cin >> x >> y;
                    l.swap_node(x, y);
                    break;
                }
                case 4:
                {
                    l.rev = !l.rev;
                    break;
                }
            }
            // l.print_all();
        }

        no_case++;
        printf("Case %d: %lld\n", no_case, l.add_odd());
    }


    return 0;
}