#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct ary
{
    char name;
    int size;
    map<int, int> data;
};

struct access
{
    char name;
    int idx;
};

struct valid_or_data
{
    bool valid;
    int data;
};

string line;
map<char, ary> arys;

void process_declare()
{
    ary& a = arys[line[0]];
    a.name = line[0];
    int size_dig_len = line.size() - 3;
    int size = atoi(line.substr(2, size_dig_len).c_str());
    a.size = size;

    //cout << "Process declare " << line << endl;
};

valid_or_data get_data(access ac)
{
    //printf("GetData %c[%d]\n", ac.name, ac.idx);

    auto& a = arys[ac.name];

    if (ac.idx >= 0 &&
        ac.idx < a.size &&
        a.data.find(ac.idx) != a.data.end()
    )
    {
        return valid_or_data{true, a.data[ac.idx]};
    }

    return valid_or_data{false, 0};
};

valid_or_data process_expression(int b, int len)
{
    if (isalpha(line[b]))
    {
        valid_or_data value = process_expression(b + 2, len - 3);
        //printf("Pprocess_expression_e %s\n", line.substr(b,len).c_str());
        if (value.valid)
        {
            return get_data({line[b], value.data});
        }
        else
        {
            return value;
        }
    }
    else
    {
        //printf("Pprocess_expression_d %s\n", line.substr(b,len).c_str());

        return valid_or_data{true, atoi(line.substr(b, len).c_str())};
    }
};

bool process_assignment(int eq_idx)
{
    valid_or_data value = process_expression(eq_idx + 1, line.size() - eq_idx - 1);
    if (!value.valid) return false;

    valid_or_data idx_value = process_expression(2, eq_idx - 3);
    if (!idx_value.valid) return false;

    ary& a = arys[line[0]];
    if (idx_value.data >= a.size) return false;

    //printf("process_assignment %s\n", line.c_str());

    a.data[idx_value.data] = value.data;
    return true;
};

int main()
{
    while (cin >> line && line != ".")
    {
        int invalid_line = 0, cur_line = 0;
        arys.clear();
        do
        {
            if (invalid_line != 0) continue;

            cur_line++;
            int eq_idx = line.find('=');
            if (eq_idx == string::npos)
            {
                process_declare();
            }
            else
            {
                bool valid = process_assignment(eq_idx);
                if (!valid)
                {
                    invalid_line = cur_line;
                }
            }
        } while (cin >> line && line != ".");

        cout << invalid_line << endl;
    }
    return 0;
}