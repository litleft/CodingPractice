#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm>

using namespace std;

bool cur_no_move = false;
char player;
char board[8][9];
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

inline bool is_valid(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

inline bool can_move(int x, int y)
{
    return is_valid(x, y) && board[x][y] == '-';
}

bool bracket_check(int x, int y, int dx, int dy, bool flip = false)
{
    bool bracket = false;
    while (true)
    {
        x += dx;
        y += dy;
        if (!is_valid(x, y)) break;
        if (board[x][y] == '-') break;
        if (board[x][y] == player)
        {
            bracket = true;
            break;
        }
    }

    if (flip && bracket)
    {
        x -= dx;
        y -= dy;
        while (board[x][y] != player)
        {
            board[x][y] = player;
            x -= dx;
            y -= dy;
        }
    }

    return bracket;
}

void list_option()
{
    static set<pair<int, int>> options;
    options.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = board[i][j];
            if (piece == '-' || piece == player) continue;

            for (int p = 0; p < 8; p++)
            {
                int x = i + dx[p];
                int y = j + dy[p];
                if (!can_move(x, y)) continue;

                if (bracket_check(i, j, -dx[p], -dy[p]))
                {
                    options.insert({ x, y });
                }
            }
        }
    }

    if (options.empty())
    {
        cout << "No legal move." << endl;
        cur_no_move = true;
    }
    else
    {
        // sort(options.begin(), options.end());

        int count = options.size();
        for (auto& p : options)
        {
            cout << "(" << p.first + 1 << "," << p.second + 1 << ")";
            if (--count > 0) cout << " ";
        }
        cout << endl;
    }
}

void change_player()
{
    player = (player == 'W') ? 'B' : 'W';
}

void print_piece_count()
{
    int w_count = 0, b_count = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 'W') w_count++;
            if (board[i][j] == 'B') b_count++;
        }
    }
    cout << "Black -"<< setw(3) << b_count << " White -" << setw(3) << w_count << endl;
}

void move_piece(int x, int y)
{
    if (cur_no_move)
    {
        cur_no_move = false;
        change_player();
    }

    board[x][y] = player;
    for (int i = 0; i < 8; i++)
    {
        bracket_check(x, y, dx[i], dy[i], true);
    }
    print_piece_count();
    change_player();
}

void print_board()
{
    for (int i = 0; i < 8; i++)
    {
        cout << board[i] << endl;
    }
}

int main()
{
    char cmd[4];
    int game_count;
    cin >> game_count;

    for (int g_no = 0; g_no < game_count; g_no++)
    {
        if (g_no > 0) cout << endl;

        for (int i = 0; i < 8; i++)
        {
            cin >> board[i];
        }
        cin >> player;

        bool playing = true;
        while (playing)
        {
            cin >> cmd;
            switch (cmd[0])
            {
            case 'L': list_option(); break;
            case 'M': move_piece(cmd[1] - '1', cmd[2] - '1'); break;
            case 'Q': playing = false; print_board(); break;
            }
        }
    }
    return 0;
}