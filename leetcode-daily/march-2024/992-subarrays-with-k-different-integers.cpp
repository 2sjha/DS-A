/*
https://leetcode.com/problems/subarrays-with-k-different-integers

Given an integer array `nums` and an integer `k`, return *the number of **good subarrays** of
*`nums`.

A **good array** is an array where the number of different integers in that array is exactly `k`.

* For example, `[1,2,3,1,2]` has `3` different integers: `1`, `2`, and `3`.

A **subarray** is a **contiguous** part of an array.


**Example 1:**

**Input:** nums = [1,2,1,2,3], k = 2
**Output:** 7
**Explanation:** Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3],
[1,2,1], [2,1,2], [1,2, 1,2]

**Example 2:**

**Input:** nums = [1,2,1,3,4], k = 3
**Output:** 3
**Explanation:** Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].


**Constraints:**

* `1 <= nums.length <= 2 * 10⁴`
* `1 <= nums[i], k <= nums.length`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int atmost(vector<int> &nums, int k) {
        int res = 0, n = nums.size(), l = 0, r = 0;
        unordered_map<int, int> freq;
        while (r < n) {
            freq[nums[r]]++;

            while (freq.size() > k) {
                freq[nums[l]]--;
                if (freq[nums[l]] == 0) {
                    freq.erase(nums[l]);
                }
                l++;
            }

            res += r - l + 1;
            r++;
        }
        return res;
    }

  public:
    int subarraysWithKDistinct(vector<int> &nums, int k) {
        return atmost(nums, k) - atmost(nums, k - 1);
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {1, 2, 1, 2, 3};
    int k_1 = 2;
    int expected_1 = 7;
    int output_1 = sol.subarraysWithKDistinct(nums_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {1, 2, 1, 3, 4};
    int k_2 = 3;
    int expected_2 = 3;
    int output_2 = sol.subarraysWithKDistinct(nums_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}