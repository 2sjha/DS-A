/*
https://leetcode.com/problems/4sum-ii/

Given four integer arrays `nums1`, `nums2`, `nums3`, and `nums4` all of length `n`, return the
number of tuples `(i, j, k, l)` such that:

* `0 <= i, j, k, l < n`
* `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`


**Example 1:**

**Input:** nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
**Output:** 2
**Explanation:**
The two tuples are:
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

**Example 2:**

**Input:** nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
**Output:** 1


**Constraints:**

* `n == nums1.length`
* `n == nums2.length`
* `n == nums3.length`
* `n == nums4.length`
* `1 <= n <= 200`
* `-2²⁸ <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2²⁸`
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                     vector<int> &nums4) {
        int res = 0;
        unordered_map<int, int> mp;
        for (int i : nums3) {
            for (int j : nums4) {
                mp[i + j]++;
            }
        }

        for (int k : nums1) {
            for (int l : nums2) {
                if (mp.count(-1 * (k + l))) {
                    res += mp[-1 * (k + l)];
                }
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> nums1_1 = {1, 2};
    vector<int> nums2_1 = {-2, -1};
    vector<int> nums3_1 = {-1, 2};
    vector<int> nums4_1 = {0, 2};
    int expected_1 = 2;
    int output_1 = sol.fourSumCount(nums1_1, nums2_1, nums3_1, nums4_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums1_2 = {0};
    vector<int> nums2_2 = {0};
    vector<int> nums3_2 = {0};
    vector<int> nums4_2 = {0};
    int expected_2 = 1;
    int output_2 = sol.fourSumCount(nums1_2, nums2_2, nums3_2, nums4_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}