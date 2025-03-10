#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)

int main()
{
    int kase_cnt;
    cin >> kase_cnt;
    map<int, vector<int>> y2x;
    REP(kase_no, kase_cnt)
    {
        int n;
        cin >> n;
        y2x.clear();

        REP(i, n)
        {
            int x, y;
            cin >> x >> y;
            y2x[y].push_back(x);
        }

        for (auto& p : y2x)
        {
            auto& x_vec = p.second;
            sort(x_vec.begin(), x_vec.end());
        }

        bool flag = true;
        bool fisrt = true;
        int sum = -1;
        for (auto p : y2x)
        {
            auto& x_vec = p.second;
            int b = 0, e = x_vec.size() - 1;
            if (fisrt)
            {
                sum = x_vec[b++] + x_vec[e--];
                fisrt = false;
            }
            while (b <= e)
            {
                if (x_vec[b++] + x_vec[e--] != sum)
                {
                    flag = false;
                    break;
                }
            }
        }
        cout << (flag ? "YES" : "NO") << endl;
    }
    return 0;
}