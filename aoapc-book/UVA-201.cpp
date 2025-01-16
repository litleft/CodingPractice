#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    bool h_lines[10][10];
    bool v_lines[10][10];
    int case_count = 0;
    int res[10];
    int n, m;

    while ((cin >> n >> m).eof() == false)
    {
        memset(h_lines, 0, 10 * 10);
        memset(v_lines, 0, 10 * 10);
        memset(res, 0, 10);
        case_count++;

        for (int i = 0; i < m; i++)
        {
            char type;
            int x, y;
            cin >> type >> x >> y;
            if (type == 'H')
            {
                h_lines[x-1][y-1] = true;
            }
            else
            {
                v_lines[y-1][x-1] = true;
            }
        }

        int all_count = 0;
        for (int i = 1; i < n; i++)
        {
            int quad_count = 0;
            for (int j = 0; j < n - i; j++)
            {
                for (int k = 0; k < n - i; k++)
                {
                    bool is_quad = true;
                    for (int p = 0; p < i; p++)
                    {
                        if (h_lines[j][k+p] == false
                            || v_lines[j+p][k] == false
                            || h_lines[j+i][k+i-1-p] == false
                            || v_lines[j+i-1-p][k+i] == false)
                            {
                                is_quad = false;
                                break;
                            }
                    }
                    if (is_quad)
                    {
                        quad_count++;
                    }
                }
            }
            res[i] = quad_count;
            all_count += quad_count;
        }


        if (case_count > 1)
        {
            cout << endl;
            cout << "**********************************" << endl;
            cout << endl;
        }

        cout << "Problem #" << case_count << endl << endl;
        if (all_count == 0)
        {
            cout << "No completed squares can be found." << endl;
        }
        else
        {
            for (int i = 1; i < n; i++)
            {
                if (res[i] > 0)
                {
                    cout << res[i] << " square (s) of size " << i << endl;
                }
            }
        }
    }

    return 0;
}