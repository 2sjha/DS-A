/*
https://leetcode.com/problems/partition-equal-subset-sum/

Given an integer array nums, return true if you can partition the array into two subsets such that
the sum of the elements in both subsets is equal or false otherwise.


Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.


Constraints:

    1 <= nums.length <= 200
    1 <= nums[i] <= 100
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    // Use SubsetSum DP.
    // Check if any subset can sum up to half of total sum
    // If Yes, then the {nums set} - {that subset} is the other partition.
    bool canPartition(vector<int> &nums) {
        if (nums.empty()) {
            return true;
        }

        int total_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            total_sum += nums[i];
        }
        if (total_sum % 2 != 0) {
            return false;
        }
        int target_sum = total_sum / 2;

        vector<vector<bool>> dp;
        for (int i = 0; i <= nums.size(); ++i) {
            dp.push_back(vector<bool>(target_sum + 1, false));
        }
        for (int i = 0; i < nums.size(); ++i) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= nums.size(); ++i) {
            for (int j = 1; j <= target_sum; j++) {
                if (nums[i - 1] > j) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        return dp[nums.size()][target_sum];
    }
};

int main() {
    Solution sol;
    bool res;

    vector<int> nums1 = {1, 5, 11, 5};
    res = sol.canPartition(nums1);
    cout << res << endl;
    assert(res == true);

    vector<int> nums2 = {1, 2, 3, 5};
    res = sol.canPartition(nums2);
    cout << res << endl;
    assert(res == false);

    vector<int> nums3 = {14, 9, 8, 4, 3, 2};
    res = sol.canPartition(nums3);
    cout << res << endl;
    assert(res == true);

    return 0;
}