/*
https://leetcode.com/problems/subsets/

Given an integer array nums of unique elements, return all possible
subsets
(the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.


Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:

Input: nums = [0]
Output: [[],[0]]


Constraints:

    1 <= nums.length <= 10
    -10 <= nums[i] <= 10
    All the numbers of nums are unique.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void get_subsets_length(vector<int> &nums, int end, vector<vector<int>> &powerset) {
        int n = powerset.size();

        vector<int> new_set;
        for (int i = 0; i < n; ++i) {
            new_set = powerset[i];
            new_set.push_back(nums[end]);
            powerset.push_back(new_set);
        }
    }

  public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> powerset;
        powerset.push_back({});

        for (int i = 0; i < nums.size(); ++i) {
            get_subsets_length(nums, i, powerset);
        }

        return powerset;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> res;

    vector<int> nums1 = {1, 2, 3};
    res = sol.subsets(nums1);
    print2Dmatrix(res);

    vector<int> nums2 = {0};
    res = sol.subsets(nums2);
    print2Dmatrix(res);

    return 0;
}