/*
https://leetcode.com/problems/4sum/submissions/

Given an array `nums` of `n` integers, return *an array of all the **unique** quadruplets*
`[nums[a], nums[b], nums[c], nums[d]]` such that:

* `0 <= a, b, c, d < n`
* `a`, `b`, `c`, and `d` are **distinct**.
* `nums[a] + nums[b] + nums[c] + nums[d] == target`

You may return the answer in **any order**.


**Example 1:**

**Input:** nums = [1,0,-1,0,-2,2], target = 0
**Output:** [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

**Example 2:**

**Input:** nums = [2,2,2,2,2], target = 8
**Output:** [[2,2,2,2]]


**Constraints:**

* `1 <= nums.length <= 200`
* `-10⁹ <= nums[i] <= 10⁹`
* `-10⁹ <= target <= 10⁹`
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        int n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        int a = 0, num_a = 0, b = 0, num_b = 0, c = 0, num_c = 0, d = 0, num_d = 0;
        long tgt_1 = 0, tgt_2 = 0;
        while (a < n) {
            tgt_1 = target - nums[a];
            num_a = nums[a];
            b = a + 1;
            while (b < n) {
                tgt_2 = tgt_1 - nums[b];
                num_b = nums[b];
                c = b + 1;
                d = n - 1;
                while (c < d) {
                    if (nums[c] + nums[d] == tgt_2) {
                        res.push_back({nums[a], nums[b], nums[c], nums[d]});
                        num_c = nums[c];
                        num_d = nums[d];
                        while (c < n && nums[c] == num_c)
                            c++;
                        while (d >= 0 && nums[d] == num_d)
                            d--;
                    } else if (nums[c] + nums[d] > tgt_2) {
                        d--;
                    } else {
                        c++;
                    }
                }

                while (b < n && nums[b] == num_b)
                    b++;
            }

            while (a < n && nums[a] == num_a)
                a++;
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {1, 0, -1, 0, -2, 2};
    int target_1 = 0;
    vector<vector<int>> expected_1 = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
    vector<vector<int>> output_1 = sol.fourSum(nums_1, target_1);
    print2Dmatrix(output_1);
    assert(output_1 == expected_1);

    vector<int> nums_2 = {2, 2, 2, 2, 2};
    int target_2 = 8;
    vector<vector<int>> expected_2 = {{2, 2, 2, 2}};
    vector<vector<int>> output_2 = sol.fourSum(nums_2, target_2);
    print2Dmatrix(output_2);
    assert(output_2 == expected_2);

    return 0;
}