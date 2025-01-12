#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <cctype>
#define EPS 1e-5

using namespace std;

const string welcome_msg = 
{
R"(Welcome to Student Performance Management System (SPMS).

1 - Add
2 - Remove
3 - Query
4 - Show ranking
5 - Show Statistics
0 - Exit

)"
};
const string add_msg = "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n";
const string qry_msg = "Please enter SID or name. Enter 0 to finish.\n";
const string rank_msg = "Showing the ranklist hurts students' self-esteem. Don't do that.\n";
const string stat_msg = "Please enter class ID, 0 for the whole statistics.\n";

using sid_t = unsigned long long;
struct student
{
    sid_t sid;
    int cid;
    char name[11];
    int score[4];
    int total_score;
    int rank;
};
vector<student> students;
bool need_update_rank = false;

void add_op()
{
    student stu;
    do
    {
        cout << add_msg;

        cin >> stu.sid;
        if (stu.sid == 0)
        {
            break;
        }
        cin >> stu.cid >> stu.name >> stu.score[0] >> stu.score[1] >> stu.score[2] >> stu.score[3];

        bool is_valid = true;
        for (auto& s : students)
        {
            if (s.sid == stu.sid)
            {
                cout << "Duplicated SID.\n";
                is_valid = false;
                continue;
            }
        }
        if (!is_valid)
        {
            continue;
        }

        stu.total_score = stu.score[0] + stu.score[1] + stu.score[2] + stu.score[3];
        students.push_back(stu);
        need_update_rank = true;
    } while (true);
}

char query_buf[11];
bool get_input(bool& is_name)
{
    cin >> query_buf;
    if (query_buf[0] == '0' && query_buf[1] == '\0')
    {
        return false;
    }
    is_name = isalpha(query_buf[0]);
    return true;
}

void del_op()
{
    do
    {
        cout << qry_msg;
        bool is_name;
        if (!get_input(is_name))
        {
            break;
        }

        int remove_count = 0;
        if (is_name)
        {
            int num = students.size();
            for (int i = 0; i < num; i++)
            {
                if (strcmp(students[i].name, query_buf) == 0)
                {
                    students.erase(students.begin() + i);
                    need_update_rank = true;
                    remove_count++;
                    i--;
                    num--;
                }
            }
        }
        else
        {
            sid_t sid = atoll(query_buf);
            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].sid == sid)
                {
                    students.erase(students.begin() + i);
                    need_update_rank = true;
                    remove_count++;
                    break;
                }
            }
        }

        printf("%d student(s) removed.\n", remove_count);
    } while (true);
}

void update_rank()
{
    if (!need_update_rank)
    {
        return;
    }
    need_update_rank = false;

    vector<student*> stu_list;
    for (auto& s : students)
    {
        stu_list.push_back(&s);
    }

    sort(stu_list.begin(), stu_list.end(), [](student* a, student* b)
    {
        if (a->total_score != b->total_score)
        {
            return a->total_score > b->total_score;
        }
        return a->sid < b->sid;
    });

    for (int i = 0; i < stu_list.size(); i++)
    {
        if (i == 0 || stu_list[i]->total_score != stu_list[i - 1]->total_score)
        {
            stu_list[i]->rank = i + 1;
        }
        else
        {
            stu_list[i]->rank = stu_list[i - 1]->rank;
        }
    }
}

void qry_op()
{
    update_rank();
    do
    {
        cout << qry_msg;
        bool is_name;
        if (!get_input(is_name))
        {
            break;
        }

        bool has_result = false;
        if (is_name)
        {
            for (auto const& s : students)
            {
                if (strcmp(s.name, query_buf) == 0)
                {
                    printf("%d %010llu %d %s %d %d %d %d %d %.2f\n", s.rank, s.sid, s.cid, s.name, s.score[0], s.score[1], s.score[2], s.score[3], s.total_score, s.total_score / 4.0 + EPS);
                    has_result = true;
                }
            }
        }
        else
        {
            sid_t sid = atoll(query_buf);
            for (auto const& s : students)
            {
                if (s.sid == sid)
                {
                    printf("%d %010llu %d %s %d %d %d %d %d %.2f\n", s.rank, s.sid, s.cid, s.name, s.score[0], s.score[1], s.score[2], s.score[3], s.total_score, s.total_score / 4.0 + EPS);
                    has_result = true;
                    break;
                }
            }
        }
    } while (true);
}

void rank_op()
{
    cout << rank_msg;
}

void stat_op()
{
    cout << stat_msg;
    int cid;
    cin >> cid;
    
    auto same_class = [&](student const& a)
    {
        if (cid == 0)
        {
            return true;
        }
        return a.cid == cid;
    };

    int stu_count = 0;
    int pass_count[] = { 0, 0, 0, 0};
    int score_sum[] = { 0, 0, 0, 0};
    const string score_name[4] = { "Chinese", "Mathematics", "English", "Programming" };
    int passnum_sum[] = { 0, 0, 0, 0, 0 };

    for (auto const& s : students)
    {
        if (same_class(s))
        {
            int pass_num = 0;
            stu_count++;
            for (int i = 0; i < 4; i++)
            {
                score_sum[i] += s.score[i];
                if (s.score[i] >= 60)
                {
                    pass_count[i]++;
                    pass_num++;
                }
            }
            passnum_sum[pass_num]++;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        double avg = (double)score_sum[i] / (double)stu_count;
        printf("%s\n", score_name[i].c_str());
        printf("Average Score: %.2f\n", avg+EPS);
        printf("Number of passed students: %d\n", pass_count[i]);
        printf("Number of failed students: %d\n", stu_count - pass_count[i]);
        printf("\n");
    }
    printf("Overall:\nNumber of students who passed all subjects: %d\nNumber of students who passed 3 or more subjects: %d\nNumber of students who passed 2 or more subjects: %d\nNumber of students who passed 1 or more subjects: %d\nNumber of students who failed all subjects: %d\n\n",
        passnum_sum[4], passnum_sum[3] + passnum_sum[4], passnum_sum[2] + passnum_sum[3] + passnum_sum[4], passnum_sum[1] + passnum_sum[2] + passnum_sum[3] + passnum_sum[4], passnum_sum[0]);
}

int main()
{
    int cmd;
    while (true)
    {
        cout << welcome_msg;
        cin >> cmd;
        switch (cmd)
        {
        case 1: add_op(); break;
        case 2: del_op(); break;
        case 3: qry_op(); break;
        case 4: rank_op(); break;
        case 5: stat_op(); break;
        case 0: return 0;
        }
    }
    return 0;
}

/// tips:
/// 1. 不能用sid为key的map来存储学生，map会自动排序，用名字查询的时候，输出的顺序无法保证
/// 2. 浮点精度问题，输出的时候要加上EPS 1e-5
