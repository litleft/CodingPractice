#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <string>

using namespace std;

void do_case()
{
    using set_ = set<int>;
    vector<set_> sets;
    map<set_, int> set2id;
    stack<int> stk;

    set_ empty_set;
    sets.push_back(empty_set);
    set2id[empty_set] = 0;

    auto get_id = [&](set_& u) {
        if (set2id.find(u) == set2id.end())
        {
            sets.push_back(u);
            set2id[u] = sets.size() - 1;
        }
        return set2id[u];
    };

    auto set_union = [&](int a, int b)
    {
        set_ u;
        u.insert(sets[a].begin(), sets[a].end());
        u.insert(sets[b].begin(), sets[b].end());
        return get_id(u);
    };

    auto set_intersect = [&](int a, int b)
    {
        set_ u;
        for (auto it = sets[a].begin(); it != sets[a].end(); it++)
        {
            if (sets[b].find(*it) != sets[b].end())
            {
                u.insert(*it);
            }
        }
        return get_id(u);
    };

    auto set_add = [&](int a, int b)
    {
        set_ u = sets[b];
        u.insert(a);
        return get_id(u);
    };

    int cmd_cnt;
    cin >> cmd_cnt;
    string cmd;
    for (int i = 0; i < cmd_cnt; i++)
    {
        cin >> cmd;
        switch (cmd[0])
        {
        case 'P':
            stk.push(0);
            break;
        case 'D':
            stk.push(stk.top());
            break;
        case 'U':
            {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                stk.push(set_union(a, b));
            }
            break;
        case 'I':
            {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                stk.push(set_intersect(a, b));
            }
            break;
        case 'A':
            {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                stk.push(set_add(a, b));
            }
            break;
        default:
            break;
        }
        cout << sets[stk.top()].size() << endl;
    }
    cout << "***" << endl;
}

int main()
{
    int case_cnt;
    cin >> case_cnt;
    for (int i = 0; i < case_cnt; i++)
    {
        do_case();
    }
    return 0;
}