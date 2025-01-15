#include <iostream>
#include <cstring>

using namespace std;

const char rot[24][7]
{
    "123456", "135246", "154326", "142536",
    "214365", "246135", "263415", "231645",
    "312564", "326154", "365214", "351624",
    "415263", "456123", "462513", "421653",
    "513462", "536142", "564312", "541632",
    "624351", "645231", "653421", "632541",
};

bool rotate(char* s, int rot_i)
{
    static char buf[6];
    for (int i = 0; i < 6; i++)
    {
        buf[i] = s[rot[rot_i][i] - '1'];
    }
    return strcmp(buf, s + 6) == 0;
}

int main()
{
    char buf[14];
    while (true)
    {
        cin >> buf;
        if (cin.eof()) break;

        bool is_same = false;
        for (int i = 0; i < 24; i++)
        {
            if (rotate(buf, i))
            {
                is_same = true;
                break;
            }
        }
        cout << (is_same ? "TRUE" : "FALSE") << endl;
    }

    return 0;
}