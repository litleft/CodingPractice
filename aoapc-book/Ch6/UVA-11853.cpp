#include "tools.hpp"

const double eps = 1e-6;
const double map_range = 1000;

struct opponent
{
    double x, y, r;
    vector<int> adj;

    bool overlap(opponent const& o) const
    {
        double dis = (x - o.x) * (x - o.x) + (y - o.y) * (y - o.y);
        double rd = (r + o.r) * (r + o.r);
        return rd - dis > eps;
    }

    bool reach_S() const
    {
        return y - r < eps;
    }

    bool reach_N() const
    {
        return map_range - y - r < eps;
    }

    bool reach_E() const
    {
        return map_range - x - r < eps;
    }

    bool reach_W() const
    {
        return x - r < eps;
    }
};

// TIPS 1. 先判断左右是否被割断，火力点是障碍物，如果从上到下有火力点的连通块，则无解。
//      2. 只有同时和上边界、左边界有交点的连通块才能影响进口。出口同理。
int main()
{
    int n;
    while (cin >> n)
    {
        vector<opponent> opps(n);
        vector<int> opps_reach_N;
        
        REP(id, n)
        {
            auto& opp = opps[id];
            cin >> opp.x >> opp.y >> opp.r;
            opp.adj.clear();

            REP(j, id)
            {
                if (opp.overlap(opps[j]))
                {
                    opp.adj.emplace_back(j);
                    opps[j].adj.emplace_back(id);
                }
            }      

            if (opp.reach_N())
            {
                opps_reach_N.emplace_back(id);
            }
        }

        bool reach_S = false;
        vector<int> opps_reach_SE;
        vector<int> opps_reach_SW;

        {
            vector<bool> visited(n, false);
            for (int root : opps_reach_N)
            {
                if (visited[root]) continue;
    
                queue<int> q;
                q.push(root);
                while (!q.empty())
                {
                    int cur = q.front();
                    q.pop();
    
                    if (visited[cur]) continue;
                    visited[cur] = true;
    
                    auto const& opp = opps[cur];
                    if (opp.reach_S())
                    {
                        reach_S = true;
                        break;
                    }
                    else
                    {
                        if (opp.reach_E())
                        {
                            opps_reach_SE.push_back(cur);
                        }
                        if (opp.reach_W())
                        {
                            opps_reach_SW.push_back(cur);
                        }
                        for (int i : opp.adj)
                        {
                            if (!visited[i])
                            {
                                q.push(i);
                            }
                        }
                    }
                }
    
                if (reach_S) break;
            }
        }


        if (reach_S)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            double in_pos = 1000.0;
            for (int i : opps_reach_SW)
            {
                auto const& opp = opps[i];
                double pos = opp.y - sqrt(opp.r * opp.r - opp.x * opp.x);
                if (in_pos - pos > eps)
                {
                    in_pos = pos;
                }
            }

            double out_pos = 1000.0;
            for (int i : opps_reach_SE)
            {
                auto const& opp = opps[i];
                double xd = (map_range - opp.x);
                double pos = opp.y - sqrt(opp.r * opp.r - xd * xd);
                if (out_pos - pos > eps)
                {
                    out_pos = pos;
                }
            }
            printf("0.00 %.2f 1000.00 %.2f\n", in_pos, out_pos);
        }
    }

    return 0;
}