/*
https://leetcode.com/problems/longest-arithmetic-subsequence

Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.

Note that:

    A subsequence is an array that can be derived from another array by deleting some or no elements
without changing the order of the remaining elements. A sequence seq is arithmetic if seq[i + 1] -
seq[i] are all the same value (for 0 <= i < seq.length - 1).


Example 1:

Input: nums = [3,6,9,12]
Output: 4
Explanation:  The whole array is an arithmetic sequence with steps of length = 3.

Example 2:

Input: nums = [9,4,7,2,10]
Output: 3
Explanation:  The longest arithmetic subsequence is [4,7,10].

Example 3:

Input: nums = [20,1,15,3,10,5,8]
Output: 4
Explanation:  The longest arithmetic subsequence is [20,15,10,5].


Constraints:

    2 <= nums.length <= 1000
    0 <= nums[i] <= 500
*/

#include "./../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int longestArithSeqLength(vector<int> &nums) {
        int n = nums.size();
        int diff;
        int max_length_ap = 2;
        vector<unordered_map<int, int>> dp(n);

        dp[1][nums[1] - nums[0]] = 2;
        for (int i = 2; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                diff = nums[i] - nums[j];
                if (dp[j].find(diff) == dp[j].end()) {
                    dp[i][diff] = 2;
                } else {
                    dp[i][diff] = 1 + dp[j][diff];
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (auto entry : dp[i]) {
                max_length_ap = max(max_length_ap, entry.second);
            }
        }
        return max_length_ap;
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> nums1 = {3, 6, 9, 12};
    res = sol.longestArithSeqLength(nums1);
    cout << res << endl;
    assert(res == 4);

    vector<int> nums2 = {9, 4, 7, 2, 10};
    res = sol.longestArithSeqLength(nums2);
    cout << res << endl;
    assert(res == 3);

    vector<int> nums3 = {20, 1, 15, 3, 10, 5, 8};
    res = sol.longestArithSeqLength(nums3);
    cout << res << endl;
    assert(res == 4);

    return 0;
}