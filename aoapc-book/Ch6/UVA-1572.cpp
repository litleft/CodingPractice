#include "tools.hpp"

bool edge[52][52];
set<int> verts;

bool circle;
bool visited[52];

void dfs(int v)
{
    if (circle)
    {
        return;
    }

    visited[v] = true;
    // +变成-，-变成+
    int link_edge = v > 25 ? v - 26 : v + 26;
    for (int i = 0; i < 52; i++)
    {
        if (edge[link_edge][i])
        {
            if (visited[i])
            {
                circle = true;
                return;
            }
            else
            {
                dfs(i);
            }
        }
    }
    visited[v] = false;
}

// TIPS: 1. 正方形的边抽象成点，正方形抽象成连接点的边
//       2. 如果图中有环，说明可以无限循环
int main()
{
    int num_cube;
    while (cin >> num_cube)
    {
        auto char2int = [](char c, char s)
        {
            return (c - 'A') + (s == '+' ? 1 : 0) * 26;
        };

        memset(edge, 0, 52 * 52);
        memset(visited, 0, 52);
        circle = false;
        REP(i, num_cube)
        {
            int e[4];
            int valid_edge = 0;

            string cube;
            cin >> cube;
            REP(j, 4)
            {
                char c1 = cube[j * 2];
                char s1 = cube[j * 2 + 1];
                if (c1 == '0')
                    continue;
                e[valid_edge] = char2int(c1, s1);

                REP(k, valid_edge)
                {
                    edge[e[k]][e[valid_edge]] = true;
                    edge[e[valid_edge]][e[k]] = true;
                }
                verts.insert(e[valid_edge]);
                valid_edge++;
            }
        }
        

        for (int i : verts)
        {
            if (circle) break;
            dfs(i);
        }

        if (circle)
        {
            cout << "unbounded" << endl;
        }
        else
        {
            cout << "bounded" << endl;
        }
    }

    return 0;
}