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
#include <unordered_map>
#include <queue>
#include <stack>

#include <algorithm>
#include <cmath>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;

struct coord
{
    double x, y;

    double dis_sqr(double x_, double y_) const
    {
        return pow(x_ - x, 2.0) + pow(y_ - y, 2.0);
    }

    double dis_sqr(coord const& c) const
    {
        return dis_sqr(c.x, c.y);
    }
};

struct map_
{
    int id;
    string name;

    coord center;
    double x1, x2, y1, y2;
    double aera;
    double aspect_delta; // height / width

    void init()
    {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        aera = (x2 - x1) * (y2 - y1);
        aspect_delta = abs(((y2 - y1) / (x2 - x1)) - 0.75);
        center.x = (x1 + x2) / 2.0;
        center.y = (y1 + y2) / 2.0;
    }

    bool contains(coord c)
    {
        // tips1： 在边界上的时候也算是在地图上
        return c.x >= x1 && c.x <= x2 && c.y >= y1 && c.y <= y2;
    }
};

struct position
{
    string name;
    coord cord;

    vector<int> maps;
    vector<int> level;
};

int main()
{
    vector<map_> maps;
    map<string, position> positions;

    string name;
    cin >> name; // MAPS

    auto map_sort_maker = [&] (position const& pos)
    {
        return [&](int a, int b)
        {
            auto const& m1 = maps[a];
            auto const& m2 = maps[b];
    
            if (!FLOAT_EQ(m1.aera, m2.aera)) return m1.aera > m2.aera;
            
            double dis1 = pos.cord.dis_sqr(m1.center);
            double dis2 = pos.cord.dis_sqr(m2.center);
            if (!FLOAT_EQ(dis1, dis2)) return dis1 < dis2;

            if (!FLOAT_EQ(m1.aspect_delta, m2.aspect_delta)) return m1.aspect_delta < m2.aspect_delta;

            // tips2：右下角算是x大y小
            dis1 = pos.cord.dis_sqr(m1.x2, m1.y1);
            dis2 = pos.cord.dis_sqr(m2.x2, m2.y1);
            if (!FLOAT_EQ(dis1, dis2)) return dis1 < dis2;

            return m1.x1 < m2.x1;
        };
    };

    auto init_related_maps = [&](position& pos)
    {
        static vector<int> maps_cache;
        maps_cache.clear();

        REP(i, maps.size())
        {
            auto& m = maps[i];
            if (m.contains(pos.cord))
            {
                maps_cache.push_back(i);
            }
        }

        sort(maps_cache.begin(), maps_cache.end(), map_sort_maker(pos));

        // tips3：同面积的算一层，每一次只需要考虑最合适的那个地图
        double last_level = -999999.0;
        REP(i, maps_cache.size())
        {
            int map_id = maps_cache[i];
            if (abs(maps[map_id].aera - last_level) > 1e-6)
            {
                pos.maps.push_back(map_id);
                last_level = maps[map_id].aera;
            }
        }
    };

    while(cin >> name && name != "LOCATIONS")
    {
        maps.emplace_back();
        auto& m = maps.back();

        m.name = name;
        m.id = maps.size() - 1;
        cin >> m.x1 >> m.y1 >> m.x2 >> m.y2;
        m.init();
    }

    while (cin >> name && name != "REQUESTS")
    {
        auto& p = positions[name];
        cin >> p.cord.x >> p.cord.y;
        p.name = name;
        init_related_maps(p);
    }

    while (cin >> name && name != "END")
    {
        int in_level;
        cin >> in_level;

        printf("%s at detail level %d ", name.c_str(), in_level);

        auto it = positions.find(name);
        if (it == positions.end())
        {
            printf("unknown location\n");
            continue;
        }

        auto const& pos = positions[name];
        int max_level = pos.maps.size();
        if (max_level == 0)
        {
            printf("no map contains that location\n");
            continue;
        }

        if (max_level < in_level)
        {
            int map_id = pos.maps[max_level - 1];
            printf("no map at that detail level; using %s\n", maps[map_id].name.c_str());
        }
        else
        {
            int map_id = pos.maps[in_level - 1];
            printf("using %s\n", maps[map_id].name.c_str());
        }
    }
    return 0;
}