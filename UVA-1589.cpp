#include <iostream>
#include <utility>
#include <string.h>

using namespace std;

enum struct piece_type
{
    g, // 将
    r, // 车 
    h, // 马
    c, // 炮
};

piece_type get_piece_type(char piece)
{
    switch (piece)
    {
    case 'R':
        return piece_type::r;
    case 'H':
        return piece_type::h;
    case 'C':
        return piece_type::c;
    case 'G':
        return piece_type::g;
    default:
        printf("Error: unknown piece type: %c\n", piece);
        return piece_type::r;
    }
}

struct coord
{
    int x;
    int y;

    coord operator+(const coord &other) const
    {
        return {x + other.x, y + other.y};
    }

    bool operator==(const coord &other) const
    {
        return x == other.x && y == other.y;
    }
};

const coord r_move_step[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

bool is_in_palace(coord c)
{
    return c.x >= 1 && c.x <= 3 && c.y >= 4 && c.y <= 6;
}

struct piece
{
    piece_type type;
    coord c;
    bool eated;
};

int n;
piece pieces[10];
bool used[11][10];

int block_count(coord start, coord end)
{
    if (start == end) return -1;

    bool is_horizontal = start.x == end.x;
    int b, e, axis;
    if (is_horizontal)
    {
        b = (start.y > end.y) ? end.y : start.y;
        e = (start.y > end.y) ? start.y : end.y;
        axis = start.x;
    }
    else
    {
        b = (start.x > end.x) ? end.x : start.x;
        e = (start.x > end.x) ? start.x : end.x;
        axis = start.y;
    }

    int count = 0;
    for (int i = b + 1; i < e; i++)
    {
        if (is_horizontal && used[axis][i])
        {
            count++;
        }
        else if (!is_horizontal && used[i][axis])
        {
            count++;
        }
    }
    return count;
}

bool horse_can_move(coord start, coord end)
{
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    bool can_move = (dx == 2 && dy == 1) || (dy == 2 && dx == 1);
    if (!can_move) return false;

    coord block_cord;
    if (dy == 2)
    {
        block_cord.x = start.x;
        block_cord.y = (start.y + end.y) / 2;
    }
    else
    {
        block_cord.y = start.y;
        block_cord.x = (start.x + end.x) / 2;
    }
    return !used[block_cord.x][block_cord.y];
}

bool is_checkmate(coord red_r)
{
    for (int i = 0; i < n; i++)
    {
        switch (pieces[i].type)
        {
        case piece_type::r:
        {
            if (pieces[i].c.x == red_r.x || pieces[i].c.y == red_r.y)
            {
                bool no_blocked = block_count(red_r, pieces[i].c) == 0;
                if (no_blocked)
                {
                    return true;
                }
            }
            break;
        }
        case piece_type::h:
        {
            if (horse_can_move(pieces[i].c, red_r))
            {
                return true;
            }
            break;
        }
        case piece_type::c:
        {
            if (pieces[i].c.x == red_r.x || pieces[i].c.y == red_r.y)
            {
                bool can_fire = block_count(red_r, pieces[i].c) == 1;
                if (can_fire)
                {
                    return true;
                }
            }
            break;
        }
        case piece_type::g:
        {
            if (pieces[i].c.x == red_r.x || pieces[i].c.y == red_r.y)
            {
                bool can_flying = block_count(red_r, pieces[i].c) == 0;
                if (can_flying)
                {
                    return true;
                }
            }
            break;
        }
        default:
            break;
        }
    }
    return false;
}

bool can_red_flying(coord red_g, coord blue_g)
{
    return (red_g.y == blue_g.y && block_count(red_g, blue_g) == 0);
}

int main()
{
    coord red_g, blue_g;

    while (true)
    {
        cin >> n >> red_g.x >> red_g.y;

        if (n == 0 && red_g.x == 0 && red_g.y == 0)
        {
            break;
        }

        memset(used, 0, 11 * 10);
        for (int i = 0; i < n; i++)
        {
            char type, x, y;
            cin >> type >> pieces[i].c.x >> pieces[i].c.y;
            pieces[i].type = get_piece_type(type);
            pieces[i].eated = false;
            used[pieces[i].c.x][pieces[i].c.y] = true;

            if (type == 'G')
            {
                blue_g = pieces[i].c;
            }
        }

        if (can_red_flying(red_g, blue_g))
        {
            cout << "NO\n";
            continue;
        }

        bool is_safe = false;
        for (int i = 0; i < 4; i++)
        {
            coord next = red_g + r_move_step[i];
            if (!is_in_palace(next))
            {
                continue;
            }
            if (!is_checkmate(next))
            {
                is_safe = true;
                break;
            }
        }
        printf(is_safe ? "NO\n" : "YES\n");
    }

    return 0;
}

// tips:
// 1.注意一开始的时候将对将，可以直接判断为赢
