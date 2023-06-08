/*
https://leetcode.com/problems/unique-paths/

There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e.,
grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The
robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take
to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2 * 109.


Example 1:

Input: m = 3, n = 7
Output: 28

Example 2:

Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down


Constraints:

    1 <= m, n <= 100
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp;
        for (int i = 0; i <= m; ++i) {
            dp.push_back(vector<int>(n + 1, 0));
        }

        for (int i = 1; i <= n; ++i) {
            dp[1][i] = 1;
        }

        for (int i = 1; i <= m; ++i) {
            dp[i][1] = 1;
        }

        for (int i = 2; i <= m; ++i) {
            for (int j = 2; j <= n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution sol;
    int res;

    res = sol.uniquePaths(3, 7);
    cout << res << endl;
    assert(res == 28);

    res = sol.uniquePaths(3, 2);
    cout << res << endl;
    assert(res == 3);

    return 0;
}