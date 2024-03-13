/*
https://leetcode.com/problems/rotate-array/

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.


Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]


Constraints:

    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1
    0 <= k <= 10^5


Follow up:

    Try to come up with as many solutions as you can. There are at least three different ways to
solve this problem. Could you do it in-place with O(1) extra space?
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    void rotate(vector<int> &nums, int k) {
        int n = nums.size();

        if (k == 0) {
            return;
        }

        int gcd = __gcd(n, k);
        if (gcd != 1) {
            int flips = n / gcd;
            int j = 0;

            for (int h = 0; h < gcd; ++h) {
                int flipCount = 0;
                int tmp = nums[h];
                int i = h;
                while (flipCount <= flips) {
                    j = (i + k) % n;
                    swap(tmp, nums[j]);
                    i = j;
                    flipCount++;
                }
            }
        } else {
            int shifts = 0;
            int i = 0, j = 0;
            int tmp = nums[i];

            while (shifts <= n) {
                j = (i + k) % n;
                swap(tmp, nums[j]);
                i = j;
                shifts++;
            }
        }
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int k1 = 9;
    sol.rotate(nums1, k1);
    printArray(nums1);

    return 0;
}