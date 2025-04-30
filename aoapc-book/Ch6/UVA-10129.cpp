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

int main()
{

    int num_case;
    cin >> num_case;
    REP(no_case, num_case)
    {
        int n;
        cin >> n;

        vector<string> words(n);
        REP(i, n)
        {
            cin >> words[i];
        }

        set<char> verts;
        map<char, int> indegree, outdegree;
        REP(i, n)
        {
            char first = words[i][0];
            char last = words[i].back();
            verts.insert(first);
            verts.insert(last);
            indegree[last]++;
            outdegree[first]++;
        }

        map<char, char> parent;
        int cnt_root = 0;
        for (char c : verts)
        {
            parent[c] = c;
            cnt_root++;
        }

        // union
        REP(i, n)
        {
            char first = words[i][0];
            char last = words[i].back();
            while (parent[last] != last)
            {
                last = parent[last];
            }
            while (parent[first] != first)
            {
                char p = parent[first];
                parent[first] = last;
                first = p;
            }
            if (first != last)
            {
                parent[first] = last;
                cnt_root--;
            }
        }

        bool is_connected = cnt_root == 1;
        bool has_euler_path = true;
        if (is_connected)
        {
            bool start_found = false;
            bool end_found = false;
            for (char c : verts)
            {
                int indeg = indegree[c];
                int outdeg = outdegree[c];
                if (indeg == outdeg)
                {
                    continue;
                }
                else if (indeg + 1 == outdeg)
                {
                    if (start_found)
                    {
                        has_euler_path = false;
                        break;
                    }
                    start_found = true;
                }
                else if (indeg == outdeg + 1)
                {
                    if (end_found)
                    {
                        has_euler_path = false;
                        break;
                    }
                    end_found = true;
                }
                else
                {
                    has_euler_path = false;
                    break;
                }

                if (!has_euler_path)
                {
                    break;
                }
            }
        }

        if (is_connected && has_euler_path)
        {
            cout << "Ordering is possible." << endl;
        }
        else 
        {
            cout << "The door cannot be opened." << endl;
        }
    }

    return 0;
}