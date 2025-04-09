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



struct mat
{
    int m, n;
};

int main()
{
    int num_mat;
    cin >> num_mat;

    map<char, mat> mats;
    REP(i, num_mat)
    {
        char c;
        cin >> c;
        int m, n;
        cin >> m >> n;
        mats[c] = {m, n};
    }

    string line;
    getline(cin, line);
    while (getline(cin, line))
    {
        stack<mat> s;
        int results = 0;
        auto calc_top_mats = [&]()
        {
            mat m2 = s.top(); s.pop();
            mat m1 = s.top(); s.pop();
            if (m1.n != m2.m)
            {
                results = -1;
                return false;
            }
            results += (m1.m * m1.n * m2.n);
            s.push({m1.m, m2.n});
            return true;
        };

        REP(i, line.size())
        {
            while (line[i] == '(')
            {
                i++;
            }
            if (line[i] != ')')
            {
                s.push(mats[line[i]]);
            }
            else
            {
                if (!calc_top_mats())
                {
                    break;
                }
            }
        }
        while (results != -1 && s.size() > 1)
        {
            calc_top_mats();
        }
        if (results == -1) cout << "error" << endl;
        else cout << results << endl;
    }

    return 0;
}