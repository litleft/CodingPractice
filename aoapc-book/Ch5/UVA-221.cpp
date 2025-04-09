#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)

struct building
{
    int id;
    int x1, y, x2, h;

    building(int id, int x, int y, int w, int h) : id(id), x1(x), y(y), x2(x + w), h(h) {}

    bool operator<(const building &b) const
    {
        return x1 < b.x1 || (x1 == b.x1 && y < b.y);
    }
};

struct y_compare
{
    bool operator()(const building &a, const building &b) const
    {
        return a.y < b.y;
    }
};

int main()
{
    int kase = 0, n = 0;
    int x, y, w, d, h;

    vector<building> buildings;
    set<int> x_coords;
    while (cin >> n && n != 0)
    {
        kase++;
        if (kase > 1)
            cout << endl;

        buildings.clear();
        x_coords.clear();

        REP(i, n)
        {
            cin >> x >> y >> w >> d >> h;
            buildings.emplace_back(i + 1, x, y, w, h); 
            x_coords.insert(x);
            x_coords.insert(x + w);
        }
        sort(buildings.begin(), buildings.end());

        vector<building> result;
        set<int> result_set;

        int blk_cnt = x_coords.size() - 1;
        auto it = x_coords.begin();
        REP(i, blk_cnt)
        {
            int x1 = *it, x2 = *(++it);

            vector<building> tmp;
            for (auto& b : buildings)
            {
                if (b.x1 >= x2)
                    break;
                if (b.x2 <= x1)
                    continue;
                tmp.push_back(b);
            }

            sort(tmp.begin(), tmp.end(), y_compare());

            int max_h = 0;
            for (auto& b : tmp)
            {
                if (b.h > max_h)
                {
                    if (result_set.find(b.id) == result_set.end())
                    {
                        result.push_back(b);
                        result_set.insert(b.id);
                    }
                    max_h = b.h;
                }
            }
        }

        printf("For map #%d, the visible buildings are numbered as follows:\n", kase);
        sort(result.begin(), result.end());
        REP(i, result.size())
        {
            if (i > 0)
                cout << " ";
            cout << result[i].id;
        }
        cout << endl;
    }

    return 0;
}