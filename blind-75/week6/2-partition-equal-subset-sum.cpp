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
    bool canPartition(vector<int> &nums) {
        if (nums.empty()) {
            return true;
        }

        int total_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            total_sum += nums[i];
        }

        vector<vector<int>> partial_sum;
        for (int i = 0; i < nums.size(); ++i) {
            partial_sum.push_back(vector<int>(nums.size(), 0));
        }

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                for (int k = i; k <= j; ++k) {
                    partial_sum[i][j] += nums[k];
                }
            }
        }

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (total_sum - partial_sum[i][j] == partial_sum[i][j]) {
                    return true;
                }
            }
        }

        return false;
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