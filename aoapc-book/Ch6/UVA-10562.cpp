#include "tools.hpp"

int lines;
vector<string> input(200);
string output;

bool is_node(char c)
{
    return c!= ' ' && c != '|' && c != '-' && c != '#';
}

void build_tree(int x, int y)
{
    output.push_back(input[x][y]);
    output.push_back('(');
    if (x + 3 < lines && input[x + 1][y] == '|')
    {
        int left = y;
        int right = y;
        while (left > 0 && input[x + 2][left] == '-')
            left--;
        while (input[x + 2][right] == '-')
            right++;
        right = min(right, (int)input[x + 3].length());

        FOR(i, left, right - 1)
        {
            if (is_node(input[x + 3][i]))
            {
                build_tree(x + 3, i);
            }
        }
    }
    output.push_back(')');
}

int main()
{
    int num_trees;
    cin >> num_trees;
    getline(cin, input[0]); // consum first line

    REP(no_tree, num_trees)
    {
        lines = 0;
        while (true)
        {
            getline(cin, input[lines]);
            if (input[lines] == "#")
                break;
            lines++;
        }

        if (lines == 0)
        {
            cout << "()" << endl;
            continue;
        }

        output.clear();
        output.push_back('(');
        for (int i = 0; input[0][i] != '\0'; i++)
        {
            if (input[0][i] != ' ')
            {
                build_tree(0, i);
                break;
            }
        }
        output.push_back(')');
        cout << output << endl;
    }

    return 0;
}