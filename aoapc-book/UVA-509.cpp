    #include <iostream>
    #include <sstream>
    #include <string.h>

    using namespace std;

    /// d <= 6 s <= 64 b <= 100 

    int main()
    {
        char parity;
        int d, s, b;
        char disk[6][64 * 100 + 2];
        int case_no = 0;
        while (cin >> d >> s >> b)
        {
            if (d == 0) break;
            cin >> parity;
            for (int i = 0; i < d; i++)
            {
                cin >> disk[i];
            }

            bool valid = true;
            for (int i = 0; i < b * s && valid; i++)
            {
                int error_d = -1;
                int checksum = parity == 'E' ? 0 : 1;
                for (int j = 0; j < d && valid; j++)
                {
                    char data = disk[j][i];
                    if (data == 'x')
                    {
                        if (error_d != -1)
                        {
                            valid = false;
                            break;
                        }
                        else
                        {
                            error_d = j;
                        }
                    }
                    else
                    {
                        checksum ^= (data - '0');
                    }
                }
                if (valid)
                {
                    if (error_d != -1)
                    {
                        disk[error_d][i] = checksum + '0';
                    }
                    else if (checksum != 0)
                    {
                        valid = false;
                    }
                }
            }

            if (!valid)
            {
                cout << "Disk set " << ++case_no << " is invalid.\n";
                continue;
            }

            const char hex_map[17] = "0123456789ABCDEF";
            int bit_count = 0;
            int bit_sum = 0;
            int block_count = 0;
            int parity_d = 0;
            stringstream ss;
            for (int i = 0; i < b; i++)
            {
                for (int j = 0; j < d; j++)
                {
                    if (parity_d == j) continue;
                    for (int k = 0; k < s; k++)
                    {
                        bit_sum = (bit_sum * 2) + (disk[j][i*s+k] - '0');
                        if (++bit_count == 4)
                        {
                            ss << hex_map[bit_sum];
                            bit_count = 0;
                            bit_sum = 0;
                        }
                    }
                }
                parity_d = (parity_d + 1) % d;
            }

            if (bit_count != 0)
            {
                for (int i = bit_count; i < 4; i++)
                {
                    bit_sum = bit_sum * 2;
                }
                ss << hex_map[bit_sum];
            }

            cout << "Disk set " << ++case_no 
                << " is valid, contents are: " << ss.str() << endl;
        }
        return 0;
    }