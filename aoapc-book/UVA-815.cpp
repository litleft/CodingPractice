#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int m, n, case_no = 0;
    vector<int> regions;
    while (cin >> m >> n)
    {
        if (m == 0 && n == 0) break;
        case_no++;

        regions.clear();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int reg;
                cin >> reg;
                regions.emplace_back(reg);
            }
        }

        int waters;
        cin >> waters;

        sort(regions.begin(), regions.end());

        int flooded_cnt = 0;
        double level = regions[flooded_cnt++];
        double water_left = (double)waters / 100.0;
        while(true)
        {
            if (water_left <= 0) break;
            if (flooded_cnt >= regions.size())
            {
                level += water_left / (double)(flooded_cnt);
                break;
            }

            double reg = regions[flooded_cnt];
            double reg_waters = (reg - level) * flooded_cnt;
            
            if (reg_waters > water_left)
            {
                double level_added = water_left / (double)(flooded_cnt);
                level += level_added;
                break;
            }
            else
            {
                level = reg;
                water_left -= reg_waters;
                flooded_cnt++;
            }
        }

        double percent = (double)flooded_cnt * 100.0 / (m * n);

        cout << fixed << setprecision(2)
             << "Region " << case_no << endl
             << "Water level is " << level + 1e-5 << " meters." << endl
             << percent << " percent of the region is under water." << endl << endl;
    }
    
    return 0;
}