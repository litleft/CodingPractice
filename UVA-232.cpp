#include <cstdio>
#include <map>
#include <vector>
#include <utility>

using std::vector;
using std::map;
using std::pair;

int main()
{
    int row, col;
    char matrix[11][11];

    vector<pair<int, int>> start_pos;
    map<int, int> acr, down;

    int puzzle_no = 0;

    while (true)
    {
        scanf("%d", &row);
        if (row == 0) break;
        scanf("%d", &col);

        puzzle_no++;
        start_pos.clear();
        acr.clear();
        down.clear();

        for (int r = 0; r < row; r++)
        {
            scanf("%s", matrix[r]);
        }

        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                if (matrix[r][c] == '*')
                {
                    continue;
                }

                bool is_start_row = (c == 0) || (matrix[r][c - 1] == '*');
                bool is_start_col = (r == 0) || (matrix[r - 1][c] == '*');

                if (is_start_col || is_start_row)
                {
                    start_pos.emplace_back(r, c);
                }
                else
                {
                    continue;;
                }

                int start_no = start_pos.size();
                if (is_start_col)
                {
                    int end = r + 1;
                    for (; end < row; end++)
                    {
                        if (matrix[end][c] == '*')
                        {
                            down[start_no] = end;
                            break;
                        }
                    }
                    if (end == row)
                    {
                        down[start_no] = row;
                    }
                }

                if (is_start_row)
                {
                    int end = c + 1;
                    for (; end < col; end++)
                    {
                        if (matrix[r][end] == '*')
                        {
                            acr[start_no] = end;
                            break;
                        }
                    }
                    if (end == col)
                    {
                        acr[start_no] = end;
                    }
                }
            }
        }
    

        if (puzzle_no != 1)
        {
            printf("\n");
        }
        printf("puzzle #%d:\n", puzzle_no);

        printf("Across\n");
        for (auto& p : acr)
        {
            int start_no = p.first;
            int start_end = p.second;
            printf("%3d.", start_no);

            auto start = start_pos[start_no - 1];
            int r = start.first;
            int c = start.second;

            for (; c < start_end; c++)
            {
                printf("%c", matrix[r][c]);
            }
            printf("\n");
        }

        printf("Down\n");
        for (auto& p : down)
        {
            int start_no = p.first;
            int start_end = p.second;
            printf("%3d.", start_no);

            auto start = start_pos[start_no - 1];
            int r = start.first;
            int c = start.second;

            for (; r < start_end; r++)
            {
                printf("%c", matrix[r][c]);
            }
            printf("\n");
        }
    }

    return 0;
}
