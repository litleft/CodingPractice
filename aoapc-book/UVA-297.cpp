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


const int height_max = 5;
int res;
string t1, t2;

void add_pix(int h)
{
    int pix = (int)pow(4, height_max - h);
    res += pix;
}

void trace(string const& t, int& i, int h, bool added)
{
    if (i >= t.size()) return;

    switch (t[i++])
    {
        case 'e': break;
        case 'f': 
        {
            if (added)
            {
                add_pix(h);
            }
            break;
        } 
        case 'p':
        {
            trace(t, i, h + 1, added);
            trace(t, i, h + 1, added);
            trace(t, i, h + 1, added);
            trace(t, i, h + 1, added);
            break;
        }
    }
}

void add_tree(int& i1, int& i2, int h, bool added)
{
    if (t1[i1] == 'f' || t2[i2] == 'f')
    {
        if (added)
        {
            add_pix(h);
        }

        if (t1[i1] != 'f')
        {
            trace(t1, i1, h, false);
        }
        else
        {
            i1++;
        }
        if (t2[i2] != 'f')
        {
            trace(t2, i2, h, false);
        }
        else
        {
            i2++;
        }
        return;
    }

    if (t1[i1] == 'e' && t2[i2] == 'e')
    {
        i1++;
        i2++;
        return;
    }

    if (t1[i1] == 'p' && t2[i2] == 'p')
    {
        i1++;
        i2++;
        add_tree(i1, i2, h+1, added);
        add_tree(i1, i2, h+1, added);
        add_tree(i1, i2, h+1, added);
        add_tree(i1, i2, h+1, added);
        return;
    }

    if (t1[i1] == 'p' && t2[i2] == 'e')
    {
        i2++;
        trace(t1, i1, h, added);
        return;
    }

    if (t2[i2] == 'p' && t1[i1] == 'e')
    {
        i1++;
        trace(t2, i2, h, added);
        return;
    }
}

int main()
{
    int num_case;
    cin >> num_case;
    REP(no_case, num_case)
    {
        cin >> t1 >> t2;

        res = 0;
        int i1 = 0, i2 = 0;
        add_tree(i1, i2, 0, true);

        printf("There are %d black pixels.\n", res);
    }

    return 0;
}