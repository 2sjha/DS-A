/*
https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times

You are given an integer array `nums` and a **positive** integer `k`.

Return *the number of subarrays where the **maximum** element of *`nums`* appears **at least** *`k`*
times in that subarray.*

A **subarray** is a contiguous sequence of elements within an array.


**Example 1:**

**Input:** nums = [1,3,2,3,3], k = 2
**Output:** 6
**Explanation:** The subarrays that contain the element 3 at least 2 times are: [1,3,2,3],
[1,3,2,3,3], [3,2,3], [3,2,3, 3], [2,3,3] and [3,3].

**Example 2:**

**Input:** nums = [1,4,2,1], k = 3
**Output:** 0
**Explanation:** No subarray contains the element 4 at least 3 times.


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `1 <= nums[i] <= 10⁶`
* `1 <= k <= 10⁵`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    long long atmost(vector<int> &nums, int atmost_target) {
        long long res = 0ll;
        int n = nums.size(), l = 0, r = 0, sum = 0;
        while (r < n) {
            sum += nums[r];
            while (l <= r && sum > atmost_target) {
                sum -= nums[l];
                l++;
            }
            res += (r - l + 1);
            r++;
        }

        return res;
    }

  public:
    long long countSubarrays(vector<int> &nums, int k) {
        int n = nums.size(), maxi = INT_MIN, max_count = 0;
        for (int i : nums)
            maxi = max(maxi, i);
        for (int i = 0; i < n; ++i) {
            if (nums[i] == maxi) {
                nums[i] = 1;
                max_count++;
            } else {
                nums[i] = 0;
            }
        }

        return atmost(nums, max_count) - atmost(nums, k - 1);
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {1, 3, 2, 3, 3};
    int k_1 = 2;
    long long expected_1 = 6;
    long long output_1 = sol.countSubarrays(nums_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {1, 4, 2, 1};
    int k_2 = 3;
    long long expected_2 = 0;
    long long output_2 = sol.countSubarrays(nums_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}