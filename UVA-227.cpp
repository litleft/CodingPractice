#include <cstdio>
#include <stdio.h>
#include <iostream>

int main()
{
    char puzzle[5][6];
    int case_no = 0;
    while(true)
    {
        int x = -1, y = -1;

        for (int i = 0; i < 5; i++)
        {
            fgets(puzzle[i], 8, stdin);
            if (puzzle[0][0] == 'Z' && 
                (puzzle[0][1] == '\0' ||
                    puzzle[0][1] == '\n'))
            {
                return 0;
            }

            for (int j = 0; j < 5; j++)
            {
                if (puzzle[i][j] == ' ')
                {
                    x = i;
                    y = j;
                    break;
                }
            }
        }

        char cmd[255];
        bool legal = true;
        bool finish = false;
        while (!finish)
        {
            fgets(cmd, 255, stdin);
            for (int i = 0; cmd[i] != '\0'; i++)
            {
                if (cmd[i] == '0')
                {
                    finish = true;
                    break;
                }

                if (!legal)
                {
                    continue;
                }

                switch (cmd[i])
                {
                case 'A':
                    if (x == 0)
                    {
                        legal = false;
                    }
                    else
                    {
                        puzzle[x][y] = puzzle[x-1][y];
                        puzzle[x-1][y] = ' ';
                        x--;
                    }
                    break;
                case 'B':
                    if (x == 4)
                    {
                        legal = false;
                    }
                    else
                    {
                        puzzle[x][y] = puzzle[x+1][y];
                        puzzle[x+1][y] = ' ';
                        x++;
                    }
                    break;
                case 'L':
                    if (y == 0)
                    {
                        legal = false;
                    }
                    else
                    {
                        puzzle[x][y] = puzzle[x][y-1];
                        puzzle[x][y-1] = ' ';
                        y--;
                    }
                    break;
                case 'R':
                    if (y == 4)
                    {
                        legal = false;
                    }
                    else
                    {
                        puzzle[x][y] = puzzle[x][y+1];
                        puzzle[x][y+1] = ' ';
                        y++;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (case_no > 0) printf("\n");
        printf("Puzzle #%d:\n", ++case_no);
        if (legal)
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", puzzle[i][j]);
                    printf(j == 4 ? "\n" : " ");
                }
            }
        }
        else
        {
            printf("This puzzle has no final configuration.\n");
        }
    }

    return 0;
}