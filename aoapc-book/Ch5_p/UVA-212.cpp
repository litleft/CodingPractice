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



struct patient
{
    string name;

    int mins_op;
    int mins_re;

    int time_b_op;
    int time_b_re;

    int op_room;
    int re_bed;
};

enum struct evt_type
{
    op_ready,
    re_ready,
    end_op,
};

struct event
{
    evt_type type;
    int mins;
    int id;

    event(evt_type t, int m, int id_)
        : type(t), mins(m), id(id_)
        {}

    bool operator<(event const& evt) const
    {
        return mins > evt.mins;
    }
};

int main()
{
    int num_op, num_re, hour_start, mins_trans, mins_prep_op, mins_prep_re;
    int num_patients;
    while (cin >> num_op >> num_re >> hour_start 
        >> mins_trans >> mins_prep_op >> mins_prep_re
        >> num_patients)
    {
        vector<patient> patients(num_patients);
        REP(i, num_patients)
        {
            cin >> patients[i].name >> patients[i].mins_op >> patients[i].mins_re;
        }

        vector<int> mins_op_busy(num_op, 0);
        vector<int> mins_re_busy(num_re, 0);
        priority_queue<int, vector<int>, greater<int>> 
            pool_op, pool_re, pool_wait_op;
        REP(i, num_op) pool_op.push(i);
        REP(i, num_re) pool_re.push(i);
        REP(i, num_patients) pool_wait_op.push(i);

        // TIPS 题目中的no值的是手术室的id，不是病人的id
        auto wait_re_compare = [&](int a, int b)
        {
            return patients[a].op_room > patients[b].op_room;
        };
        priority_queue<int, vector<int>, decltype(wait_re_compare)>
            pool_wait_re(wait_re_compare);

        int cur_min = 0;
        priority_queue<event> evt_que;

        auto print_time = [&](int mins)
        {
            int hour = mins / 60 + hour_start;
            mins = mins % 60;
            printf("%2d:%02d", hour, mins);
        };

        auto process_evt = [&]()
        {
            if (evt_que.empty()) return false;

            cur_min = evt_que.top().mins;

            while(!evt_que.empty() && cur_min == evt_que.top().mins)
            {
                auto const& evt = evt_que.top();
                switch(evt.type)
                {
                case evt_type::op_ready:
                    pool_op.push(evt.id);
                    break;
                case evt_type::end_op:
                    pool_wait_re.push(evt.id);
                    break;
                case evt_type::re_ready:
                    pool_re.push(evt.id);
                    break;
                }
                evt_que.pop();
            }
            return true;
        };

        do
        {
            while (!pool_wait_op.empty() && !pool_op.empty())
            {
                int p_id = pool_wait_op.top(); pool_wait_op.pop();
                int r = pool_op.top(); pool_op.pop();

                auto& p = patients[p_id];
                p.op_room = r;
                p.time_b_op = cur_min;
                mins_op_busy[r] += p.mins_op;

                int time_end_op = cur_min + p.mins_op;
                evt_que.emplace(evt_type::end_op, time_end_op, p_id);
                evt_que.emplace(evt_type::op_ready, time_end_op + mins_prep_op, r);
            }

            while (!pool_wait_re.empty() && !pool_re.empty())
            {
                int p_id = pool_wait_re.top(); pool_wait_re.pop();
                int b = pool_re.top(); pool_re.pop();

                auto& p = patients[p_id];
                p.re_bed = b;
                p.time_b_re = cur_min + mins_trans;
                mins_re_busy[b] += p.mins_re;

                int re_ready_time = p.time_b_re + p.mins_re + mins_prep_re;
                evt_que.emplace(evt_type::re_ready, re_ready_time, b);
            }

        } while (process_evt());

        printf(" Patient          Operating Room          Recovery Room\n");
        printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
        printf(" ------------------------------------------------------\n");

        REP(i, num_patients)
        {
            auto const& p = patients[i];
            printf("%2d  %-8s  %2d   ", i + 1, p.name.c_str(), p.op_room + 1);
            print_time(p.time_b_op);
            printf("   ");
            print_time(p.time_b_op + p.mins_op);
            printf("     ");
            printf("%2d", p.re_bed + 1);
            printf("   ");
            print_time(p.time_b_re);
            printf("   ");
            print_time(p.time_b_re + p.mins_re);
            printf("\n");
        }

        double mins_last_pa = cur_min - mins_prep_re;
        printf("\nFacility Utilization\n");
        printf("Type  # Minutes  % Used\n");
        printf("-------------------------\n");
        REP(i, num_op)
        {
            double used = (double)mins_op_busy[i] * 100.0 / mins_last_pa;
            printf("Room %2d %7d   %5.2lf\n", i + 1, mins_op_busy[i], used);
        }
        REP(i, num_re)
        {
            double used = (double)mins_re_busy[i] * 100.0 / mins_last_pa;
            printf("Bed  %2d %7d   %5.2lf\n", i + 1, mins_re_busy[i], used);
        }
        cout << endl;
    }

}