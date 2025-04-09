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



int main()
{
    string line;
    while (getline(cin, line))
    {
        vector<int> next(line.size() + 3);
        const int head = line.size();
        const int tail = head + 1;
        next[head] = tail;
        next[tail] = head; // next[tail]存储最后一个元素的idx，即prev[tail]
        int cur = head;

        REP(i, line.size())
        {
            if (line[i] == '[')
            {
                cur = head;
            }
            else if (line[i] == ']')
            {
                cur = next[tail];
            }
            else
            {
                next[i] = next[cur];
                next[cur] = i;
                if (next[i] == tail) next[tail] = i;
                cur = i;
            }
        }

        for (int i = next[head]; i != tail; i = next[i])
        {
            cout << line[i];
        }
        cout << endl;
    }

    return 0;
}