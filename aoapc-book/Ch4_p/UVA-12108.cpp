#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int n, case_no = 0;
    int a[10], b[10], c[10];
    while (cin >> n && n != 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> a[i] >> b[i] >> c[i];
        }

        int cur_min = 1;
        vector<int> try_sleep_stu;
        set<unsigned long> status_cache;
        while (true)
        {
            try_sleep_stu.clear();
            int wake_stu = 0, sleep_stu = 0;
            int next_min = 100;
            unsigned long status = 0;
            for (int i = 0; i < n; i++)
            {
                status = status * 10 + c[i] - 1;
                int s = c[i] - a[i];
                if (s <= 0)
                {
                    wake_stu++;
                    if (s == 0)
                    {
                        try_sleep_stu.push_back(i);
                    }
                    else
                    {
                        next_min = min(next_min, -s);
                    }
                }
                else
                {
                    sleep_stu++;
                    next_min = min(next_min, a[i] + b[i] - c[i] + 1);
                }
            }

            if (sleep_stu == 0)
            {
                break;
            }

            if (status_cache.count(status) > 0)
            {
                cur_min = -1;
                break;
            }

            status_cache.insert(status);

            bool can_sleep = sleep_stu > wake_stu;
            if (!can_sleep)
            {
                for (int i : try_sleep_stu)
                {
                    c[i] = 0;
                    next_min = min(next_min, a[i]);
                }
            }
            
            cur_min += next_min;
            for (int i = 0; i < n; i++)
            {
                c[i] = (c[i] + next_min - 1) % (a[i] + b[i]) + 1;
            }
            // printf("Nextmin %d stu status %d %d %d \n", cur_min, c[0], c[1], c[2]);
        }
        printf("Case %d: %d\n", ++case_no, cur_min);
    }

    return 0;
}