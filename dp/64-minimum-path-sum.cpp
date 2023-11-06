/*
https://leetcode.com/problems/minimum-path-sum/

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right,
which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.


Example 1:

Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:

Input: grid = [[1,2,3],[4,5,6]]
Output: 12


Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 200
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>>dp = vector<vector<int>>(m, vector<int>(n, 201));
        dp[0][0] = grid[0][0];

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == 0 and j == 0) {
                    continue;
                }
                if(i-1 < 0) {
                    dp[i][j] = min(dp[i][j], dp[i][j-1] + grid[i][j]);
                } else if(j-1 < 0) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j] + grid[i][j]);
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
                }
            }
        }

        return dp[m-1][n-1];
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> grid1 = {{1,3,1},{1,5,1},{4,2,1}};
    res = sol.minPathSum(grid1);
    cout << res << endl;
    assert(res == 7);

    vector<vector<int>> grid2 = {{1,2,3},{4,5,6}};
    res = sol.minPathSum(grid2);
    cout << res << endl;
    assert(res == 12);

    vector<vector<int>> grid3 = {{0}};
    res = sol.minPathSum(grid3);
    cout << res << endl;
    assert(res == 0);

    return 0;
}