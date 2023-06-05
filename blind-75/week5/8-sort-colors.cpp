/*
https://leetcode.com/problems/sort-colors/description/

Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects
of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.


Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]


Constraints:

    n == nums.length
    1 <= n <= 300
    nums[i] is either 0, 1, or 2.


Follow up: Could you come up with a one-pass algorithm using only constant extra space?

*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void i_swap(vector<int> &nums, int low, int high) {
        int tmp = nums[low];
        nums[low] = nums[high];
        nums[high] = tmp;
    }

  public:
    void easySortColors(vector<int> &nums) {
        int nums_0 = 0, nums_1 = 0, nums_2 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                nums_0++;
            } else if (nums[i] == 1) {
                nums_1++;
            } else {
                nums_2++;
            }
        }

        int i = 0;
        for (; i < nums_0; ++i) {
            nums[i] = 0;
        }
        for (; i < nums_0 + nums_1; ++i) {
            nums[i] = 1;
        }
        for (; i < nums_0 + nums_1 + nums_2; ++i) {
            nums[i] = 2;
        }
    }

    // Baed on Dutch National Flag Problem
    // https://en.wikipedia.org/wiki/Dutch_national_flag_problem
    // Idea is that middle should always be 1.
    // If middle is 0, then swap low and mid so that low = 0.
    // If middle is 2, then swap mid and high so that high = 2.
    // Initially Low and mid start at the same point, then as 0 starts coming in at low,
    // low and mid drift apart, until mid crosses high.
    void sortColors(vector<int> &nums) {
        int low = 0, high = nums.size() - 1, mid = 0;

        while (mid <= high) {
            if (nums[mid] == 0) {
                i_swap(nums, low, mid);
                low++;
                mid++;
            } else if (nums[mid] == 2) {
                i_swap(nums, mid, high);
                high--;
            } else {
                mid++;
            }
        }
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    printArray(nums1);
    sol.sortColors(nums1);
    printArray(nums1);

    vector<int> nums2 = {2, 0, 1};
    printArray(nums2);
    sol.sortColors(nums2);
    printArray(nums2);

    vector<int> nums3 = {1, 2, 2, 2, 2, 0, 0, 0, 1, 1};
    printArray(nums3);
    sol.sortColors(nums3);
    printArray(nums3);
    return 0;
}