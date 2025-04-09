#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;

using uint_64 = unsigned long long;
using int_64 = long long;
using uint = unsigned int;
using uint_8 = unsigned char;
using int_8 = signed char;

inline uint_8 char2uint8(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else
        return 0;
}

int h, w;
uint_8 img[202][202];
uint_8 color[202][202];

const static int dx[4] = {0, 0, -1, 1};
const static int dy[4] = {-1, 1, 0, 0};

void dfs(int i, int j, int_8 id)
{
    color[i][j] = id;
    REP(k, 4)
    {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ni >= 0 && ni < h 
            && nj >=0 && nj < w
            && color[ni][nj] == 0
            && img[ni][nj] == img[i][j]
        )
        {
            dfs(ni, nj, id);
        }
    }
}

void print_img()
{
    REP(i, h)
    {
        REP(j, w)
        {
            cout << (int)img[i][j];
        }
        cout << endl;
    }
}

void print_color()
{
    REP(i, h)
    {
        REP(j, w)
        {
            cout << (int)color[i][j];
        }
        cout << endl;
    }
}

int main()
{
    int no_case = 0;
    string line;

    // 填充白边 
    memset(img[0], 0, 202);
    memset(img[201], 0, 202);

    while (cin >> h >> w && h != 0 && w != 0)
    {
        REP(i, 202)
        {
            memset(img[i], 0, 202);
            memset(color[i], 0, 202);
        }

        REP(i, h)
        {
            cin >> line;
            REP(j, w)
            {
                uint_8 val = char2uint8(line[j]);
                REP(k, 4)
                {
                    img[i + 1][j * 4 + k + 1] = (val >> (3 - k)) & 1;
                }
            }
        }
        h = h + 2;
        w = w * 4 + 2;


        //print_img();

        int id = 1;
        REP(i, h)
        {
            REP(j, w)
            {
                if (color[i][j] == 0)
                {
                    dfs(i, j, id++);
                }
            }
        }

        //print_color();
        
        map<uint_8, set<int_8>> color_sib;
        REP(i, h)
        {
            REP(j, w)
            {
                if (img[i][j] == 1)
                {
                    REP(k, 4)
                    {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < h 
                            && nj >=0 && nj < w
                            && img[ni][nj] == 0
                        )
                        {
                            color_sib[color[i][j]].insert(color[ni][nj]);
                        }
                    }
                }
            }
        }


        const char cnt2alpha[] = "WAKJSD";
        vector<char> res;
        for(auto& it : color_sib)
        {
            res.push_back(cnt2alpha[it.second.size() -1]);
        }
        sort(res.begin(), res.end());
        cout << "Case " << ++no_case << ": ";
        for(char c : res)
        {
            cout << c;
        }
        cout << endl;
    }

    return 0;
}