#include "tools.hpp"

struct cube
{
    int x0, y0, z0;
    int x1, y1, z1;
};

uint_8 grid[102][102][102];
vector<int> x_dscrt, y_dscrt, z_dscrt;
int x_size, y_size, z_size;
int copper_plate = 0;
int blank_volume = 0;

int x_dir[6] = { 1, -1, 0, 0, 0, 0 };
int y_dir[6] = { 0, 0, 1, -1, 0, 0 };
int z_dir[6] = { 0, 0, 0, 0, 1, -1 };

void flood_fill(int x, int y, int z)
{
    grid[x][y][z] = 1;
    blank_volume += (x_dscrt[x + 1] - x_dscrt[x]) * (y_dscrt[y + 1] - y_dscrt[y]) * (z_dscrt[z + 1] - z_dscrt[z]);
    REP(i, 6)
    {
        int x_ = x + x_dir[i];
        int y_ = y + y_dir[i];
        int z_ = z + z_dir[i];
        if (x_ < 0 || x_ >= x_size - 1 || y_ < 0 || y_ >= y_size - 1|| z_ < 0 || z_ >= z_size - 1)
            continue;
        if (grid[x_][y_][z_] == 0)
        {
            flood_fill(x_, y_, z_);
        }
        else if (grid[x_][y_][z_] == 2)
        {
            if (i < 2)
            {
                copper_plate += (y_dscrt[y_ + 1] - y_dscrt[y_]) * (z_dscrt[z_ + 1] - z_dscrt[z_]);
            }
            else if (i < 4)
            {
                copper_plate += (x_dscrt[x_ + 1] - x_dscrt[x_]) * (z_dscrt[z_ + 1] - z_dscrt[z_]);
            }
            else
            {
                copper_plate += (x_dscrt[x_ + 1] - x_dscrt[x_]) * (y_dscrt[y_ + 1] - y_dscrt[y_]);
            }
        }
    }
}

// TIPS: 1、计算外围的空气面积 2、离散化
int main()
{
    int num_case;
    cin >> num_case;
    REP(no_case, num_case)
    {
        vector<cube> cubes;
        map<int, int> x_map, y_map, z_map;
        x_dscrt.clear();
        y_dscrt.clear();
        z_dscrt.clear();

        int num_cube;
        cin >> num_cube;
        REP(i, num_cube)
        {
            cubes.push_back({});
            cube& c = cubes.back();
            cin >> c.x0 >> c.y0 >> c.z0;
            int x, y, z;
            cin >> x >> y >> z;
            c.x1 = c.x0 + x;
            c.y1 = c.y0 + y;
            c.z1 = c.z0 + z;

            x_dscrt.push_back(c.x0);
            x_dscrt.push_back(c.x1);
            y_dscrt.push_back(c.y0);
            y_dscrt.push_back(c.y1);
            z_dscrt.push_back(c.z0);
            z_dscrt.push_back(c.z1);
        }

        auto discrect = [](vector<int>& dscrt, map<int, int>& val2idx, int& size)
        {
            dscrt.push_back(0);
            sort(dscrt.begin(), dscrt.end());
            dscrt.erase(unique(dscrt.begin(), dscrt.end()), dscrt.end());
            int max = dscrt.back();
            dscrt.push_back(max + 1);
            size = dscrt.size();
            REP(i, dscrt.size())
            {
                val2idx[dscrt[i]] = i;
            }
        };
        discrect(x_dscrt, x_map, x_size);
        discrect(y_dscrt, y_map, y_size);
        discrect(z_dscrt, z_map, z_size);

        // paint the cubes
        memset(grid, 0, 102 * 102 * 102);
        REP(i, num_cube)
        {
            cube& c = cubes[i];
            int x0 = x_map[c.x0];
            int y0 = y_map[c.y0];
            int z0 = z_map[c.z0];
            int x1 = x_map[c.x1];
            int y1 = y_map[c.y1];
            int z1 = z_map[c.z1];

            FOR(xi, x0, x1 - 1)
            {
                FOR(yi, y0, y1 - 1)
                {
                    FOR(zi, z0, z1 - 1)
                    {
                        grid[xi][yi][zi] = 2;
                    }
                }
            }
        }

        // flood fill
        copper_plate = 0;
        blank_volume = 0;
        flood_fill(0, 0, 0);

        int all_volume = x_dscrt.back() * y_dscrt.back() * z_dscrt.back();
        int volume = all_volume - blank_volume;
        cout << copper_plate << " " << volume << endl;
    }


    return 0;
}