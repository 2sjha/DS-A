/*
https://leetcode.com/problems/combination-sum/

Given an array of distinct integers candidates and a target integer target, return a list of all
unique combinations of candidates where the chosen numbers sum to target. You may return the
combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are
unique if the frequency of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to target is
less than 150 combinations for the given input.


Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:

Input: candidates = [2], target = 1
Output: []


Constraints:

    1 <= candidates.length <= 30
    2 <= candidates[i] <= 40
    All elements of candidates are distinct.
    1 <= target <= 40
*/

#include "bits/stdc++.h"
#include "./../../printutils.h"
#include <iostream>
using namespace std;

class Solution {
    vector<vector<int>> getSubsetsFromDP(vector<int> candidates, vector<vector<int>> num_subsets_dp,
                                         int row, int col) {

        vector<vector<int>> ans = vector<vector<int>>();
        if (num_subsets_dp[row][col] == 0) {
            return ans;
        }
        if (row == 0 or col == 0) {
            return ans;
        }

        vector<vector<int>> no_include_subsets =
            getSubsetsFromDP(candidates, num_subsets_dp, row - 1, col);
        for (auto subset : no_include_subsets) {
            ans.push_back(subset);
        }

        if (col >= candidates[row - 1] and num_subsets_dp[row][col - candidates[row - 1]] > 0) {
            vector<vector<int>> include_subsets =
                getSubsetsFromDP(candidates, num_subsets_dp, row, col - candidates[row - 1]);
            if (!include_subsets.empty()) {
                for (auto subset : include_subsets) {
                    subset.push_back(candidates[row - 1]);
                    ans.push_back(subset);
                }
            } else {
                ans.push_back({candidates[row - 1]});
            }
        }

        return ans;
    }

  public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> dp;

        // init no elements in the subset, num_subsets=0
        for (int i = 0; i <= candidates.size(); ++i) {
            dp.push_back(vector<int>(target + 1, 0));
        }

        // init target = 0, num_subsets=1
        for (int i = 0; i <= candidates.size(); ++i) {
            dp[i][0] = 1;
        }

        // i is the number of elements considered for subsets = 1 through i.
        // j is the intermediate target, iterate across 1 through target
        for (int i = 1; i <= candidates.size(); ++i) {
            for (int j = 1; j <= target; ++j) {
                if (candidates[i - 1] <= j) {
                    dp[i][j] = dp[i][j - candidates[i - 1]] // include
                               + dp[i - 1][j];              // don't include
                } else {
                    dp[i][j] = dp[i - 1][j];                // can't include
                }
            }
        }

        print2Dmatrix(dp);

        vector<vector<int>> ans = getSubsetsFromDP(candidates, dp, candidates.size(), target);
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> res;

    vector<int> candidates1 = {2, 3, 6, 7};
    int target1 = 7;
    res = sol.combinationSum(candidates1, target1);
    print2Dmatrix(res);

    vector<int> candidates2 = {2, 3, 5};
    int target2 = 8;
    res = sol.combinationSum(candidates2, target2);
    print2Dmatrix(res);

    vector<int> candidates3 = {2};
    int target3 = 1;
    res = sol.combinationSum(candidates3, target3);
    print2Dmatrix(res);

    return 0;
}