/*
https://leetcode.com/problems/single-number-ii/

Given an integer array nums where every element appears three times except for one, which appears
exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.


Example 1:

Input: nums = [2,2,3,2]
Output: 3

Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99


Constraints:

    1 <= nums.length <= 3 * 104
    -231 <= nums[i] <= 231 - 1
    Each element in nums appears exactly three times except for one element which appears once.
*/

#include "./../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Had to look at the solution.
// Trick is that if all numbers are 32 bit numbers,
// then consider 32 length array where we add bits of all the numbers
// Finally all bits will be added thrice except the one number whose bits will remain if we do % 3
class Solution {
  private:
    void getBits(vector<int> &bits, int num) {
        if (num > 0) {
            bits[0] = 0;
        } else {
            bits[0] = 1;
            unsigned int num2 = num;
            num2 = num2 << 1;
            num2 = num2 >> 1;
            num = num2;
        }
        for (int i = 31; i > 0; --i) {
            bits[i] = num % 2;
            num = num / 2;
        }
    }

    int getNum(vector<int> &bits) {
        long sum = 0;

        if (bits[0] == 1) {
            sum = -1 * pow(2, 31);
        }
        for (int i = 31; i > 0; --i) {
            sum += pow(2, 31 - i) * bits[i];
        }

        return (int)sum;
    }

  public:
    int singleNumber(vector<int> &nums) {
        vector<int> ans(32, 0);
        vector<int> bits(32, 0);

        for (int num : nums) {
            getBits(bits, num);
            for (int i = 0; i < 32; ++i) {
                ans[i] += bits[i];
            }
        }

        for (int i = 0; i < 32; ++i) {
            ans[i] = ans[i] % 3;
        }

        return getNum(ans);
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> nums1 = {2, 2, 3, 2};
    res = sol.singleNumber(nums1);
    cout << res << endl;
    assert(res == 3);

    vector<int> nums2 = {0, 1, 0, 1, 0, 1, 99};
    res = sol.singleNumber(nums2);
    cout << res << endl;
    assert(res == 99);

    return 0;
}