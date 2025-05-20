#include "tools.hpp"

int main()
{
    int num_of_case;
    cin >> num_of_case;
    string str;
    getline(cin, str);
    REP(no_case, num_of_case)
    {
        stack<char> s;
        getline(cin, str);

        bool valid = true;
        REP(i, str.size())
        {
            switch (str[i])
            {
                case '(':
                case '[':
                    s.push(str[i]);
                    break;
                case ')':
                {
                    if (s.empty() || s.top() == '[')
                    {
                        valid = false;
                    }
                    else
                    {
                        s.pop();
                    }
                    break;
                }
                case ']':
                {
                    if (s.empty() || s.top() == '(')
                    {
                        valid = false;
                    }
                    else
                    {
                        s.pop();
                    }
                    break;
                }
            }
            if (!valid) break;
        }
        valid = valid && s.empty();
        cout << (valid ? "Yes" : "No") << endl;
    }

    return 0;
}