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



struct task
{
    int id;
    int num;

    int begin_time;
    int time;
    int delta_time;
};

struct staff
{
    int id; // useless. use idx instead
    int idx;
    vector<int> spec_task;

    int last_scheduled_time = 0;
};

enum struct time_type
{
    new_task,
    staff_free,
};

struct time_point
{
    int time;
    time_type type;
    int id;

    time_point(int t, time_type t_type, int id_) : time(t), type(t_type), id(id_) {}

    bool operator<(time_point const& o) const
    {
        return time < o.time;
    }
};

int main()
{
    unordered_map<int, task> tasks;
    vector<staff> staffs;

    auto staff_compare = [&](int idx1, int idx2)
    {
        auto const& s1 = staffs[idx1];
        auto const& s2 = staffs[idx2];
        if (s1.last_scheduled_time != s2.last_scheduled_time)
        {
            return s1.last_scheduled_time < s2.last_scheduled_time;
        }
        return s1.idx < s2.idx;
    };

    unordered_map<int, int> task_pool;
    vector<int> staff_pool;
    vector<time_point> time_queue;

    int cur_time = 0;
    int in_pool_task_cnt = 0;

    auto on_task_arrive = [&](task& t)
    {
        in_pool_task_cnt++;
        task_pool[t.id]++;

        //printf("task %d arrive at %d still have %d \n", t.id, cur_time, t.num);
        
        if (t.num <= 0) return;
        t.num--;
        time_queue.emplace_back(cur_time + t.delta_time, time_type::new_task, t.id);
    };

    auto on_staff_free = [&](int idx)
    {
        //printf("staff %d free at %d \n", staffs[idx].id, cur_time);
        staff_pool.push_back(idx);
    };

    int n, s_no = 0;
    while (cin >> n && n != 0)
    {
        s_no++;
        tasks.clear();
        staffs.clear();
        task_pool.clear();
        staff_pool.clear();
        time_queue.clear();
        cur_time = 0;
        in_pool_task_cnt = 0;

        REP(i, n)
        {
            int id;
            cin >> id;
            task& t = tasks[id];
            t.id = id;
            cin >> t.num >> t.begin_time >> t.time >> t.delta_time;

            if (t.num <= 0) continue;
            t.num--;

            if (t.begin_time == 0)
            {
                on_task_arrive(t);
            }
            else
            {
                time_queue.emplace_back(t.begin_time, time_type::new_task, t.id);
            }
        }
    
        cin >> n;
        REP(i, n)
        {
            staff s;
            cin >> s.id;
            s.idx = staffs.size();
    
            int spec_task_num;
            cin >> spec_task_num;
            REP(j, spec_task_num)
            {
                int id;
                cin >> id;
                s.spec_task.push_back(id);
            }
    
            staff_pool.push_back(s.idx);
            staffs.emplace_back(move(s));
        }
    
        while (true)
        {
            sort(staff_pool.begin(), staff_pool.end(), staff_compare);
            vector<int> free_staff;
            REP(i, staff_pool.size())
            {
                int staff_idx = staff_pool[i];
                staff& s = staffs[staff_idx];
    
                bool get_task = false;
                for (int j = 0; in_pool_task_cnt > 0 && j < s.spec_task.size(); j++)
                {
                    int t_id = s.spec_task[j];
                    if (task_pool[t_id] > 0)
                    {
                        task_pool[t_id]--;
                        in_pool_task_cnt--;
    
                        s.last_scheduled_time = cur_time;
                        get_task = true;
    
                        int finish_time = cur_time + tasks[t_id].time;
                        time_queue.emplace_back(finish_time, time_type::staff_free, staff_idx);
    
                        //printf("staff %d get task %d at time %d will finished at %d\n", staffs[staff_idx].id, t_id, cur_time, finish_time);
    
                        break;
                    }
                }
                if (!get_task)
                {
                    free_staff.push_back(staff_idx);
                }
            }
            staff_pool = move(free_staff);

            // next time point
            if (time_queue.empty()) break;
            sort(time_queue.begin(), time_queue.end());

            int it = 0;
            int time = time_queue[it].time;
            cur_time = time;
            while (time_queue[it].time == time && it <time_queue.size())
            {
                int id = time_queue[it].id;
                switch (time_queue[it].type)
                {
                case time_type::new_task:
                    on_task_arrive(tasks[id]);
                    break;
                case time_type::staff_free:
                    on_staff_free(id);
                    break;
                }
                it++;
            }
            time_queue.erase(time_queue.begin(), time_queue.begin() + it);
        }
    
        printf("Scenario %d: All requests are serviced within %d minutes.\n", s_no, cur_time);
    }

}