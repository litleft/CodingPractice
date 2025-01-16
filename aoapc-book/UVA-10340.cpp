#include <cstdio>
#include <iostream>
#include <string>

int main()
{
    std::string a, b;

    while (!(std::cin >> a >> b).eof())
    {
        int i = 0, j = 0;

        while (i < a.size() && j < b.size())
        {
            if (a[i] == b[j])
            {
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }
        
        bool res = i == a.size();

        std::cout << (res ? "Yes" : "No") << std::endl;
    }

    return 0;
}