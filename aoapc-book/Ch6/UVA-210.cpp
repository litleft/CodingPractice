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



enum struct t_cmd : int
{
    assign = 0,
    output,
    lock,
    unlock,
    end,
};

struct cmd
{
    t_cmd t;
    char var;
    int value;

    cmd(string const& line)
    {
        if (line[2] == '=')
        {
            t = t_cmd::assign;
            var = line[0];
            value = atoi(line.substr(4).c_str());
            return;
        }

        switch (line[0])
        {
            case 'p' : t = t_cmd::output; var = line[6]; break;
            case 'l' : t = t_cmd::lock; break;
            case 'u' : t = t_cmd::unlock; break;
            case 'e' : t = t_cmd::end; break;
        }
    }
};

struct program
{
    vector<cmd> cmds;
    int next_cmd;

    cmd const& cmd_next()
    {
        return cmds[next_cmd++];
    }

    t_cmd type_next() const
    {
        return cmds[next_cmd].t;
    }

    t_cmd type_last() const
    {
        return cmds.back().t;
    }

    bool is_end() const
    {
        return next_cmd >= cmds.size();
    }
};

int main()
{
    int num_case;
    cin >> num_case;
    REP(no_case, num_case)
    {
        if (no_case > 0) cout << endl;

        int time_ext[5];
        int num_program, time_quant;
        cin >> num_program;
        REP(i, 5) cin >> time_ext[i];
        cin >> time_quant;

        string line;
        getline(cin, line); // get endl
        vector<program> programs(num_program);
        REP(i, num_program)
        {
            auto& p = programs[i];
            while (true)
            {
                getline(cin, line);
                p.cmds.emplace_back(line);
                if (p.type_last() == t_cmd::end) break;
            }
        }

        bool locked = false;
        map<char, int> data;
        queue<int> q_lock;
        deque<int> q_ext;
        REP(i, num_program) q_ext.push_back(i);

        while (!q_ext.empty())
        {
            int i_p = q_ext.front(); q_ext.pop_front();
            auto& p = programs[i_p];

            bool need_ext = true;
            int quant = time_quant;
            while (quant > 0 && !p.is_end())
            {
                auto t = p.type_next();
                if (t == t_cmd::lock && locked)
                {
                    q_lock.push(i_p);
                    need_ext = false;
                    break;
                }

                auto const& cmd = p.cmd_next();
                quant -= time_ext[(int)t];
                switch (t)
                {
                    case t_cmd::assign:
                    {
                        data[cmd.var] = cmd.value;
                        break;
                    }
                    case t_cmd::output:
                    {
                        printf("%d: %d\n", i_p + 1, data[cmd.var]);
                        break;
                    }
                    case t_cmd::lock:
                    {
                        locked = true;
                        break;
                    }
                    case t_cmd::unlock:
                    {
                        locked = false;
                        if (!q_lock.empty())
                        {
                            q_ext.push_front(q_lock.front());
                            q_lock.pop();
                        }
                        break;
                    }
                    case t_cmd::end:
                    {
                        need_ext = false;
                        break;
                    }
                }
            }

            if (need_ext)
            {
                q_ext.push_back(i_p);
            }
        }
    }

    return 0;
}