#include "./../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    vector<vector<int>> subsets;

  private:
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

    vector<vector<int>> getAllSubsetsFromSubsetSumDP(vector<vector<bool>> &dp, vector<int> &nums,
                                                     int i, int j) {
        if (i <= 0 || j <= 0) {
            return {{}};
        }

        if (dp[i][j]) {
            vector<vector<int>> subsets;
            vector<vector<int>> not_included;
            vector<vector<int>> included;
            if (dp[i - 1][j]) {
                not_included = getAllSubsetsFromSubsetSumDP(dp, nums, i - 1, j);
            }
            if (j >= nums[i - 1] && dp[i - 1][j - nums[i - 1]]) {
                included = getAllSubsetsFromSubsetSumDP(dp, nums, i - 1, j - nums[i - 1]);
                for (int idx = 0; idx < included.size(); ++idx) {
                    included[idx].push_back(nums[i - 1]);
                }
            }
            for (int idx = 0; idx < included.size(); ++idx) {
                subsets.push_back(included[idx]);
            }
            for (int idx = 0; idx < not_included.size(); ++idx) {
                subsets.push_back(not_included[idx]);
            }
            return subsets;
        }

        return {{}};
    }

  public:
    vector<vector<int>> subsetSumAllSubsets(vector<int> &nums, int target_sum) {
        int n = nums.size();
        vector<vector<bool>> dp = subsetSumExists(nums, target_sum);
        if (!dp[n][target_sum]) {
            return {{}};
        }

        return getAllSubsetsFromSubsetSumDP(dp, nums, n, target_sum);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> res;

    int target = 10;
    vector<int> nums1 = {1, 2, 3, 4, 5, 6};
    res = sol.subsetSumAllSubsets(nums1, target);
    print2Dmatrix(res);

    return 0;
}