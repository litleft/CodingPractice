#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> blocks[25];
    int n, p1, p2, stack[25], pos[25];
    char cmd[10], op[10];
    
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        blocks[i].push_back(i);
        stack[i] = i;
        pos[i] = 0;
    }

    auto return_blocks = [&](int s, int p)
    {
        bool has_s = false;
        for (int i = p + 1; i < blocks[s].size(); i++)
        {
            int b = blocks[s][i];
            if (b == s)
            {
                has_s == true;
                continue;
            }
            pos[b] = blocks[b].size();
            stack[b] = b;
            blocks[b].push_back(b);
        }
        blocks[s].resize(has_s ? p + 2 : p + 1);
    };

    auto move_stack_to = [&](int s1, int p, int s2)
    {
        for (int i = p; i < blocks[s1].size(); i++)
        {
            int b = blocks[s1][i];
            pos[b] = blocks[s2].size();
            stack[b] = s2;
            blocks[s2].push_back(b);
        }
        blocks[s1].resize(p);
    };

    while (cin >> cmd && cmd[0] != 'q')
    {
        cin >> p1 >> op >> p2;

        bool league = (p1 != p2 && stack[p1] != stack[p2]);
        if (!league)
        {
            // cout << endl << "+++++++++" << cmd << p1 << op << p2 << endl;
            continue;
        }
        
        if (cmd[0] == 'm') return_blocks(stack[p1], pos[p1]);
        if (op[1] == 'n') return_blocks(stack[p2], pos[p2]);
        move_stack_to(stack[p1], pos[p1], stack[p2]);

        // cout << endl << "----------" << cmd << p1 << op << p2 << endl;

    }    

    for (int i = 0; i < n; i++)
    {
        printf("%d:", i);
        for (int b : blocks[i])
        {
            printf(" %d", b);
        }
        cout << endl;
    }

    return 0;
}