/*
https://leetcode.com/problems/last-stone-weight-ii

You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose any two stones and smash them
together. Suppose the stones have weights x and y with x <= y. The result of this smash is:

    If x == y, both stones are destroyed, and
    If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.

At the end of the game, there is at most one stone left.

Return the smallest possible weight of the left stone. If there are no stones left, return 0.


Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation:
We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0, so the array converts to [1], then that's the optimal value.

Example 2:

Input: stones = [31,26,33,21,40]
Output: 5


Constraints:

    1 <= stones.length <= 30
    1 <= stones[i] <= 100
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  private:
    int recursion(vector<int> &stones, int sum, int sumSoFar, int idx) {
        if (sum - (2 * sumSoFar) < 0)
            return INT_MAX;
        if (idx >= stones.size())
            return sum - 2 * sumSoFar;

        return min(recursion(stones, sum, sumSoFar + stones[idx], idx + 1),
                   recursion(stones, sum, sumSoFar, idx + 1));
    }

  public:
    int lastStoneWeightII(vector<int> &stones) {
        int sum = 0;
        for (int s : stones)
            sum += s;

        vector<vector<int>> dp(stones.size() + 1, vector<int>(sum + 1, INT_MAX));
        for (int j = 0; sum - 2 * j >= 0; ++j) {
            dp[stones.size()][j] = sum - 2 * j;
        }

        for (int i = stones.size() - 1; i >= 0; --i) {
            for (int j = sum; j >= 0; --j) {
                if (j + stones[i] <= sum) {
                    dp[i][j] = min(dp[i + 1][j + stones[i]], dp[i + 1][j]);
                } else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }

        return dp[0][0];
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> stones1 = {2, 7, 4, 1, 8, 1};
    res = sol.lastStoneWeightII(stones1);
    cout << res << endl;
    assert(res == 1);

    vector<int> stones2 = {31, 26, 33, 21, 40};
    res = sol.lastStoneWeightII(stones2);
    cout << res << endl;
    assert(res == 5);

    return 0;
}