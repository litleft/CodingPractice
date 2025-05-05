#include "tools.hpp"

const int n_max = 100000;
const int m_max = 200000;

struct passage
{
    int v;
    int color;
    passage() : v(0), color(0) {}
    passage(int v_, int color_) : v(v_), color(color_) {}
};

vector<vector<passage>> adj;
passage path_next[n_max + 1];
int path_length[n_max + 1];

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        adj.clear();
        adj.resize(n + 1);
        memset(path_next, 0, (n_max + 1) * sizeof(passage));
        memset(path_length, 0, (n_max + 1) * sizeof(int));

        REP(i, m)
        {
            int u, v, color;
            cin >> u >> v >> color;
            adj[u].emplace_back(v, color);
            adj[v].emplace_back(u, color);
        }

        // TIPS: 从后向前dfs
        queue<int> q;
        q.push(n);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (passage e : adj[u])
            {
                int v = e.v;
                if (v == n) continue;

                if (path_length[v] == 0)
                {
                    path_length[v] = path_length[u] + 1;
                    path_next[v] = {u, e.color};
                    q.push(v);
                }
                // 遇到和当前path length相同的路径，回溯去比较顺序
                else if (path_length[v] == path_length[u] + 1)
                {
                    int c1 = path_next[v].color;
                    int v1 = path_next[v].v;

                    int c2 = e.color;
                    int v2 = u;

                    bool path1_better = c1 <= c2;
                    while (v1 != v2 && c1 == c2)
                    {
                        c1 = path_next[v1].color;
                        v1 = path_next[v1].v;
                        c2 = path_next[v2].color;
                        v2 = path_next[v2].v;
                        path1_better = c1 <= c2;
                    }

                    if (!path1_better)
                    {
                        path_next[v] = {u, e.color};
                    }
                }
            }
        }

        cout << path_length[1] << endl;
        int v = 1;
        while (true)
        {
            cout << path_next[v].color;
            v = path_next[v].v;
            if (v == n) break;
            else cout << " ";
        }
        cout << endl;
    }

    return 0;
}