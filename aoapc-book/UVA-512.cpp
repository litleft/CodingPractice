#include <cstdio>
#include <vector>

using namespace std;

struct command
{
    char op[3];
    int param_num;
    int param[10];
};

void insert_op(int& x, int xo, int param)
{
    if (xo >= param)
    {
        x++;
    }
}

bool delete_op(int& x, int xo, int param)
{
    if (xo == param)
    {
        return true;
    }
    else if (xo > param)
    {
        x--;
    }
    return false;
}

bool simulate(vector<command> const& cmds, int& x, int& y)
{
    for(auto const& cmd : cmds)
    {
        int xo = x, yo = y;
        if (cmd.op[0] == 'E')
        {
            if (x == cmd.param[0] && y == cmd.param[1])
            {
                x = cmd.param[2];
                y = cmd.param[3];
            }
            else if (x == cmd.param[2] && y == cmd.param[3])
            {
                x = cmd.param[0];
                y = cmd.param[1];
            }
        }
        else if (cmd.op[0] == 'I')
        {
            for (int i = 0; i < cmd.param_num; i++)
            {
                if (cmd.op[1] == 'R')
                {
                    insert_op(x, xo, cmd.param[i]);
                }
                else
                {
                    insert_op(y, yo, cmd.param[i]);
                }
            }
        }
        else if (cmd.op[0] == 'D')
        {
            for (int i = 0; i < cmd.param_num; i++)
            {
                bool deleted = cmd.op[1] == 'R' 
                                ? delete_op(x, xo, cmd.param[i])
                                : delete_op(y, yo, cmd.param[i]);
                if (deleted)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    vector<command> cmds;
    int r, c, n, m;
    int x, y, sheet_no = 0;
    
    while (true)
    {
        scanf("%d %d", &r, &c);
        if (r == 0 && c == 0)
        {
            break;
        }

        if (sheet_no > 0)
        {
            printf("\n");
        }
        printf("Spreadsheet #%d\n", ++sheet_no);

        scanf("%d", &n);
        cmds.clear();
        cmds.reserve(n);

        for (int i = 0; i < n; i++)
        {
            cmds.push_back(command());
            command& cmd = cmds.back();

            scanf("%s", cmd.op);

            if (cmd.op[0] == 'E')
            {
                scanf("%d %d %d %d", &cmd.param[0], &cmd.param[1], &cmd.param[2], &cmd.param[3]);
            }
            else
            {
                scanf("%d", &cmd.param_num);
                for (int j = 0; j < cmd.param_num; j++)
                {
                    scanf("%d", &cmd.param[j]);
                }
            }
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &x, &y);
            printf("Cell data in (%d,%d) ", x, y);
            bool deleted = simulate(cmds, x, y);

            if (deleted)
            {
                printf("GONE\n");
            }
            else
            {
                printf("moved to (%d,%d)\n", x, y);
            }
        }
    }

    return 0;
}