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

enum struct dir : char
{
    up = 0, right = 1, down = 2, left = 3,
    start = 4,
};

dir char2dir(char c)
{
    switch (c)
    {
    case 'N':
        return dir::up;
    case 'S':
        return dir::down;
    case 'E':
        return dir::right;
    case 'W':
        return dir::left;
    }
    return dir::up;
}

dir turn(dir d, char turn)
{
    switch (turn)
    {
    case 'L':
        return (dir)(((int)d + 3) % 4);
    case 'R':
        return (dir)(((int)d + 1) % 4);
    case 'F':
        return d;
    }
    return d;
}

struct state
{
    int x, y;
    dir d;

    void move(dir d_)
    {
        switch (d_)
        {
        case dir::up:
            x--;
            break;
        case dir::down:
            x++;
            break;
        case dir::left:
            y--;
            break;
        case dir::right:
            y++;
            break;
        }
        d = d_;
    }

    void back(dir d_)
    {
        switch (d_)
        {
        case dir::up:
            x++;
            break;
        case dir::down:
            x--;
            break;
        case dir::left:
            y++;
            break;
        case dir::right:
            y--;
            break;
        }
    }

    bool valid()
    {
        return (x >= 0 && x < 9 && y >= 0 && y < 9);
    }
};

struct intersection
{
    int x, y;
    bool valid;
    bool valid_dir[4][4];

    bool visited[4];
    dir out2in[4];

    void init()
    {
        valid = false;
        REP(i, 4)
        {
            memset(valid_dir[i], 0, 4 * sizeof(bool));
            visited[i] = false;
        }
    }

    void add_valid_dir(string const& s)
    {
        dir in_dir = char2dir(s[0]);
        FOR(i, 1, s.size() - 1)
        {
            dir out_dir = turn(in_dir, s[i]);
            valid_dir[(int)in_dir][(int)out_dir] = true;
        }
    }

    bool can_pass(dir in_dir, dir out_dir)
    {
        return valid_dir[(int)in_dir][(int)out_dir];
    }
};

int main()
{
    string name_maze;
    int x_start, y_start, x_end, y_end;
    char c_dir;
    dir d_start;

    intersection maze[9][9];
    REP(i, 9)
    {
        REP(j, 9)
        {
            maze[i][j].x = i;
            maze[i][j].y = j;
        }
    }

    while (cin >> name_maze && name_maze != "END")
    {
        // init
        REP(i, 9)
        {
            REP(j, 9)
            {
                maze[i][j].init();
            }
        }

        // input
        {
            cin >> x_start >> y_start >> c_dir >> x_end >> y_end;
            x_start--;
            y_start--;
            x_end--;
            y_end--;
            d_start = char2dir(c_dir);

            string s;
            int x, y;
            while (cin >> x && x != 0)
            {
                cin >> y;
                intersection& inter = maze[x - 1][y - 1];
                while (cin >> s && s != "*")
                {
                    inter.add_valid_dir(s);
                    inter.valid = true;
                }
            }
        }


        dir dir_end;
        bool found = false;
        // BFS
        {
            state s;
            s.x = x_start;
            s.y = y_start;
            s.move(d_start);
            maze[s.x][s.y].visited[(int)d_start] = true;
            maze[x_start][y_start].out2in[(int)d_start] = dir::start;

            queue<state> q;
            q.push(s);
            while (!q.empty())
            {
                state cur = q.front();
                q.pop();

                if (cur.x == x_end && cur.y == y_end)
                {
                    found = true;
                    dir_end = cur.d;
                    break;
                }

                auto& inter = maze[cur.x][cur.y];
                if (!inter.valid)
                {
                    continue;
                }
                REP(i, 4)
                {
                    dir diri = (dir)i;
                    if (!inter.can_pass(cur.d, diri))
                    {
                        continue;
                    }

                    state sta_next = cur;
                    sta_next.move(diri);
                    if (!sta_next.valid())
                    {
                        continue;
                    }

                    auto& inter_next = maze[sta_next.x][sta_next.y];
                    if (inter_next.visited[i])
                    {
                        continue;
                    }
                    inter_next.visited[i] = true;
                    inter.out2in[i] = cur.d;
                    q.push(sta_next);
                }
            }
        }

        cout << name_maze << endl;
        if (found)
        {
            stack<state> path;
            state cur;
            cur.x = x_end;
            cur.y = y_end;
            cur.d = dir_end;
            path.push(cur);

            do
            {
                cur.back(cur.d);
                cur.d = maze[cur.x][cur.y].out2in[(int)cur.d];
                path.push(cur);
            } while (cur.x != x_start || cur.y != y_start || cur.d != dir::start);

            int cnt_line = 0;
            while(!path.empty())
            {
                if (cnt_line == 0)
                {
                    cout << " ";
                }

                cnt_line++;
                cur = path.top();
                path.pop();
                printf(" (%d,%d)", cur.x + 1, cur.y + 1);

                if (cnt_line == 10)
                {
                    cnt_line = 0;
                    cout << endl;
                }
            }
            if (cnt_line != 0)
            {
                cout << endl;
            }
        }
        else
        {
            cout << "  No Solution Possible" << endl;
        }
    }


    return 0;
}