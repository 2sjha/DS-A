/*
https://leetcode.com/problems/tallest-billboard/

You are installing a billboard and want it to have the largest height. The billboard will have two
steel supports, one on each side. Each steel support must be an equal height.

You are given a collection of rods that can be welded together. For example, if you have rods of
lengths 1, 2, and 3, you can weld them together to make a support of length 6.

Return the largest possible height of your billboard installation. If you cannot support the
billboard, return 0.


Example 1:

Input: rods = [1,2,3,6]
Output: 6
Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.

Example 2:

Input: rods = [1,2,3,4,5,6]
Output: 10
Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.

Example 3:

Input: rods = [1,2]
Output: 0
Explanation: The billboard cannot be supported, so we return 0.


Constraints:

    1 <= rods.length <= 20
    1 <= rods[i] <= 1000
    sum(rods[i]) <= 5000
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// UNSOLVED - TLE
class Solution {
  private:
    vector<vector<int>> sets_a;
    vector<int> set_b;

    int get_sum(vector<int> &arr) {
        int sum = 0;
        for (int i : arr) {
            sum += i;
        }
        return sum;
    }

    vector<vector<bool>> subsetSumExists(vector<int> &nums, int target_sum) {
        int n = nums.size();
        vector<vector<bool>> dp(n + 1);
        for (int i = 0; i <= n; ++i) {
            dp[i] = vector<bool>(target_sum + 1, false);
        }

        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target_sum; ++j) {
                if (j < nums[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        return dp;
    }

    void getOneSubsetFromSubsetSumDP(vector<vector<bool>> &dp, vector<int> &nums,
                                     vector<int> &to_subset) {
        int i = dp.size() - 1, j = dp[0].size() - 1;
        while (i > 0 && j > 0) {
            if (!dp[i][j]) {
                break;
            }
            if (j < nums[i - 1]) {
                i--;
            } else {
                if (dp[i - 1][j - nums[i - 1]]) {
                    to_subset.push_back(nums[i - 1]);
                    j -= nums[i - 1];
                    i--;
                } else {
                    i--;
                }
            }
        }
    }

    vector<vector<int>> getAllSubsetsFromSubsetSumDP(vector<vector<bool>> &dp, vector<int> &nums,
                                                     int i, int j) {
        if (i <= 0 || j <= 0) {
            return {{}};
        }

        if (dp[i][j]) {
            vector<vector<int>> subsets;
            if (dp[i - 1][j]) {
                vector<vector<int>> not_included = getAllSubsetsFromSubsetSumDP(dp, nums, i - 1, j);
                for (int idx = 0; idx < not_included.size(); ++idx) {
                    subsets.push_back(not_included[idx]);
                }
            }
            if (j >= nums[i - 1] && dp[i - 1][j - nums[i - 1]]) {
                vector<vector<int>> included =
                    getAllSubsetsFromSubsetSumDP(dp, nums, i - 1, j - nums[i - 1]);
                for (int idx = 0; idx < included.size(); ++idx) {
                    included[idx].push_back(nums[i - 1]);
                    subsets.push_back(included[idx]);
                }
            }

            return subsets;
        }

        return {{}};
    }

    vector<vector<int>> getSubsetSumAllSubsets(vector<int> &nums, int target_sum) {
        int n = nums.size();
        vector<vector<bool>> dp = subsetSumExists(nums, target_sum);
        if (!dp[n][target_sum]) {
            return sets_a;
        }

        return getAllSubsetsFromSubsetSumDP(dp, nums, n, target_sum);
    }

    void getSubsetSumOneSubset(vector<int> &nums, int target_sum, vector<int> &to_subset) {
        int n = nums.size();
        vector<vector<bool>> dp = subsetSumExists(nums, target_sum);
        if (!dp[n][target_sum]) {
            return;
        }

        getOneSubsetFromSubsetSumDP(dp, nums, to_subset);
    }

    bool disjointEqualSumSubsetsExist(vector<int> &nums, int sum, vector<vector<int>> &sets_a,
                                      vector<int> &set_b) {
        int target_sum = sum / 2;
        sets_a = getSubsetSumAllSubsets(nums, target_sum);
        if (sets_a.empty()) {
            return false;
        }

        vector<int> set_a;
        for (int i = 0; i < sets_a.size(); ++i) {
            set_a = sets_a[i];
            sort(set_a.begin(), set_a.end());

            vector<int> nums_diff_set_a;
            set_difference(nums.begin(), nums.end(), set_a.begin(), set_a.end(),
                           std::inserter(nums_diff_set_a, nums_diff_set_a.begin()));

            set_b.clear();
            getSubsetSumOneSubset(nums_diff_set_a, target_sum, set_b);
            if (set_b.empty()) {
                continue;
            } else {
                return true;
            }
        }

        return false;
    }

  public:
    int tallestBillboard(vector<int> &rods) {
        int max_sum = get_sum(rods);

        // ensure max_sum is even such that it is divided into 2 subsets
        if (max_sum % 2 != 0) {
            max_sum--;
        }

        sort(rods.begin(), rods.end());
        while (max_sum >= 0) {
            if (disjointEqualSumSubsetsExist(rods, max_sum, sets_a, set_b)) {
                break;
            }

            // ensure max_sum is even such that it is divided into 2 subsets
            max_sum -= 2;
        }

        if (sets_a.empty() || set_b.empty()) {
            return 0;
        }

        return get_sum(set_b);
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> nums1 = {1, 2, 3, 6};
    res = sol.tallestBillboard(nums1);
    cout << res << endl;
    assert(res == 6);

    vector<int> nums2 = {1, 2, 3, 4, 5, 6};
    res = sol.tallestBillboard(nums2);
    cout << res << endl;
    assert(res == 10);

    vector<int> nums3 = {1, 2};
    res = sol.tallestBillboard(nums3);
    cout << res << endl;
    assert(res == 0);

    vector<int> nums4 = {96, 112, 101, 100, 104, 93, 106, 99, 114, 81, 94};
    res = sol.tallestBillboard(nums4);
    cout << res << endl;
    assert(res == 503);

    vector<int> nums5 = {140, 138, 133, 162, 145, 164, 145, 166, 145, 154, 158};
    res = sol.tallestBillboard(nums5);
    cout << res << endl;
    assert(res == 756);

    vector<int> nums6 = {276, 253, 247, 240, 250, 251, 257, 262, 256, 241, 238, 246, 233};
    res = sol.tallestBillboard(nums6);
    cout << res << endl;
    assert(res == 1506);

    // TLE
    vector<int> nums7 = {102, 101, 100, 100, 100, 100, 100, 100, 100, 100,
                         100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    res = sol.tallestBillboard(nums7);
    cout << res << endl;

    return 0;
}