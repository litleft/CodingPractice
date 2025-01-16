#include <string>
#include <utility>
#include <iostream>
#include <cmath>

using namespace std;

string header;
string message;

int get_message()
{
    getline(cin, message);
    return 0;
}

int decode(int& start, int len)
{
    int result = 0;
    for (int i = 0; i < len; i++)
    {
        if (start == message.size()) // tips 3
        {
            start = get_message();
        }

        result = result * 2 + (message[start++] - '0');
    }
    return result;
}

int main()
{
    bool first_case = true;

    while (true)
    {
        getline(cin, header);
        int ptr = get_message();

        if (!first_case)
        {
            cout << endl;
        }
        else
        {
            first_case = false;
        }

        while (true)
        {
            int code_len = decode(ptr, 3);
            if (code_len == 0)
            {
                break;
            }

            int end_code = (int)pow(2, code_len) - 1;
            int data_start = end_code - code_len;

            while (true)
            {
                int data = decode(ptr, code_len);
                if (data == end_code)
                {
                    break;
                }
                cout << header[data_start + data];
            }
        }

        if (cin.eof())
        {
            break;
        }
    }

    return 0;
}

/// tips
///  1. getline和cin >> string混用会出现getline得到空格的问题
///  2. 最后一个输出没有回车，否则pe
///  3. message在一种编码中有可能会被回车中断
