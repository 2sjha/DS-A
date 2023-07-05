/*
https://leetcode.com/problems/minimum-cost-to-make-array-equal

You are given two 0-indexed arrays nums and cost consisting each of n positive integers.

You can do the following operation any number of times:

    Increase or decrease any element of the array nums by 1.

The cost of doing one operation on the ith element is cost[i].

Return the minimum total cost such that all the elements of the array nums become equal.


Example 1:

Input: nums = [1,3,5,2], cost = [2,3,1,14]
Output: 8
Explanation: We can make all the elements equal to 2 in the following way:
- Increase the 0th element one time. The cost is 2.
- Decrease the 1st element one time. The cost is 3.
- Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
The total cost is 2 + 3 + 3 = 8.
It can be shown that we cannot make the array equal with a smaller cost.

Example 2:

Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
Output: 0
Explanation: All the elements are already equal, so no operations are needed.


Constraints:

    n == nums.length == cost.length
    1 <= n <= 105
    1 <= nums[i], cost[i] <= 106
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool allEqual(vector<int> &nums) {
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] != nums[i + 1]) {
                return false;
            }
        }

        return true;
    }

  public:
    long long minCost(vector<int> &nums, vector<int> &cost) {
        int n = nums.size();
        long long diff = 0;
        long long min_cost = LONG_LONG_MAX;
        long long cmltv_cost;

        if (allEqual(nums)) {
            return 0;
        }

        vector<pair<int, int>> nums_cost(n);
        for (int i = 0; i < n; ++i) {
            nums_cost[i] = {nums[i], cost[i]};
        }
        sort(nums_cost.begin(), nums_cost.end());

        vector<long long> pre_cost(n, 0);
        vector<long long> suf_cost(n, 0);

        cmltv_cost = 0;
        for (int i = 1; i < n; ++i) {
            diff = abs(nums_cost[i].first - nums_cost[i - 1].first);
            pre_cost[i] = pre_cost[i - 1] + (long long)(diff * cmltv_cost) +
                          (long long)(diff * nums_cost[i - 1].second);
            cmltv_cost += nums_cost[i - 1].second;
        }

        cmltv_cost = 0;
        for (int i = n - 2; i >= 0; --i) {
            diff = abs(nums_cost[i].first - nums_cost[i + 1].first);
            suf_cost[i] = suf_cost[i + 1] + (long long)(diff * cmltv_cost) +
                          (long long)(diff * nums_cost[i + 1].second);
            cmltv_cost += nums_cost[i + 1].second;
        }

        for (int i = 0; i < n; ++i) {
            min_cost = min(min_cost, pre_cost[i] + suf_cost[i]);
        }

        return min_cost;
    }
};

int main() {
    Solution sol;
    long long res;

    vector<int> nums1 = {1, 3, 5, 2};
    vector<int> cost1 = {2, 3, 1, 14};
    res = sol.minCost(nums1, cost1);
    cout << res << endl;
    assert(res == 8);

    vector<int> nums2 = {2, 2, 2, 2, 2};
    vector<int> cost2 = {4, 2, 8, 1, 3};
    res = sol.minCost(nums2, cost2);
    cout << res << endl;
    assert(res == 0);

    vector<int> nums3 = {735103, 366367, 132236, 133334, 808160, 113001, 49051,  735598,
                         686615, 665317, 999793, 426087, 587000, 649989, 509946, 743518};
    vector<int> cost3 = {724182, 447415, 723725, 902336, 600863, 287644, 13836,  665183,
                         448859, 917248, 397790, 898215, 790754, 320604, 468575, 825614};
    res = sol.minCost(nums3, cost3);
    cout << res << endl;
    assert(res == 1907611126748);

    return 0;
}