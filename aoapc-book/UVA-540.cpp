#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<int, int> id2team;
    vector<queue<int>> per_team_que;
    queue<int> team_que;
    set<int> team_set;

    int t, case_num = 1;
    while (cin >> t && t != 0)
    {
        cout << "Scenario #" << case_num++ << endl;

        id2team.clear();
        team_set.clear();
        team_que = queue<int>();
        per_team_que.resize(t);
        for (int i = 0; i < t; i++)
        {
            int n;
            cin >> n;
            for (int j = 0; j < n; j++)
            {
                int id;
                cin >> id;
                id2team[id] = i;
            }
            per_team_que[i] = queue<int>();
        }

        string cmd;
        int id;
        while (cin >> cmd && cmd != "STOP")
        {
            if (cmd == "ENQUEUE")
            {
                cin >> id;
                int team = id2team[id];
                if (team_set.find(team) == team_set.end())
                {
                    team_set.insert(team);
                    team_que.push(team);
                }
                per_team_que[team].push(id);
            }
            else if (cmd == "DEQUEUE")
            {
                int team = team_que.front();
                cout << per_team_que[team].front() << endl;
                per_team_que[team].pop();
                if (per_team_que[team].empty())
                {
                    team_set.erase(team);
                    team_que.pop();
                }
            }
        }
        cout << endl;
    }
}