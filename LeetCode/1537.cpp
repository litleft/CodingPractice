#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    const static int mod_base = 1e9 + 7;

    using ull = long;

    auto static maxSum(vector<int>& nums1, vector<int>& nums2) -> int
    {
        ull sum1 = 0;
        ull sum2 = 0;
        size_t i1 = 0;
        size_t i2 = 0;
        if (!nums1.empty())
        {
            sum1 += nums1[i1];
        }
        if (!nums2.empty())
        {
            sum2 += nums2[i2];
        }

        while (true)
        {
            const bool finish1 = i1 >= nums1.size() - 1;
            const bool finish2 = i2 >= nums2.size() - 1;

            auto move1 = [&]()
            {
                i1++;
                sum1 += nums1[i1];
            };
            auto move2 = [&]()
            {
                i2++;
                sum2 += nums2[i2];
            };

            if (finish1 && finish2)
            {
                break;
            }

            if (finish1)
            {
                move2();
            }
            else if (finish2)
            {
                move1();
            }
            else
            {
                if (nums1[i1] < nums2[i2])
                {
                    move1();
                }
                else if(nums1[i1] > nums2[i2])
                {
                    move2();
                }
                else
                {
                    move1();
                    move2();
                }
            }

            if (nums1[i1] == nums2[i2])
            {
                auto max_sum = max(sum1, sum2);
                sum1 = max_sum;
                sum2 = max_sum;
            }
        }
        return max(sum1, sum2) % mod_base;
    }
};

auto main() -> int
{
    Solution const s;
    vector<int> nums1 = {6,7,12,13,14,17,20};
    vector<int> nums2 = {1,4,5,7};
    cout << s.maxSum(nums1, nums2) << endl;

    nums1 = {1,3,5,7,9};
    nums2 = {3,5,100};
    cout << s.maxSum(nums1, nums2) << endl;

    nums1 = {1,2,3,4,5};
    nums2 = {6,7,8,9,10};
    cout << s.maxSum(nums1, nums2) << endl;

    return 0;
}