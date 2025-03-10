#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct coord
{
    int x, y;
    bool operator < (const coord& b) const
    {
        if (x != b.x)
            return x < b.x;
        return y < b.y;
    }
};

int main()
{
    int kase_cnt;
    cin >> kase_cnt;

    for (int kase_no; kase_no < kase_cnt; kase_no++)
    {
        int n;
        cin >> n;
        vector<coord> coords;
        for (int i = 0; i < n; i++)
        {
            coord c;
            cin >> c.x >> c.y;
            coords.emplace_back(move(c));
        }

        sort(coords.begin(), coords.end());
    
        int b = 0, e = n - 1;
        double mid_line = (coords[b].x + coords[e].x) / 2.0;

        int m = floor((b + e) / 2.0);
        int m1 = m, m2 = m;
        if (n % 2 == 0) m2++;

        bool flag = true;
        while (b < e)
        {
            int x1 = coords[b].x, x2 = coords[e].x;

            if ((mid_line - x1) < 1e-6 && (x2 - mid_line) < 1e-6)
                break; 

            if (((x1 + x2) / 2.0 - mid_line) > 1e-6)
            {
                flag = false;
                break;
            }

            int x1_eq_cnt = 1;
            for (int i = b + 1; i <= m1; i++)
            {
                if (coords[i].x == x1)
                    x1_eq_cnt++;
            }
            int x2_eq_cnt = 1;
            for (int i = e - 1; i >= m2; i--)
            {
                if (coords[i].x == x2)
                    x2_eq_cnt++;
            }

            if (x1_eq_cnt != x2_eq_cnt)
            {
                flag = false;
                break;
            }

            for (int i = 0; i < x1_eq_cnt; i++)
            {
                if (coords[b + i].y != coords[e - x1_eq_cnt + 1 + i].y)
                {
                    flag = false;
                    break;
                }
            }

            if (!flag)
                break;
            
            b += x1_eq_cnt;
            e -= x2_eq_cnt;
        }
        if (b == e && abs(mid_line - coords[b].x) > 1e-6)
            flag = false;
        cout << (flag ? "YES" : "NO") << endl;
    }
    return 0;
}