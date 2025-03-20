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
    int n;
    while (cin >> n && n != 0)
    {
        bool case_end = false;
        while (true)
        {
            queue<int> A;
            vector<int> B(n);

            REP(i, n)
            {
                A.push(i + 1);

                cin >> B[i];
                if (B[i] == 0)
                {
                    case_end = true;
                    break;
                }
            }
            if (case_end) break;

            bool suc = true;
            stack<int> C;
            REP(i, n)
            {
                while (!A.empty() && B[i] >= A.front())
                {
                    C.push(A.front()); A.pop();
                }

                if (C.empty() || C.top() != B[i])
                {
                    suc = false;
                    break;
                }

                C.pop();
            }
            cout << (suc ? "Yes" : "No") << endl;
        }
        cout << endl;
    }
}