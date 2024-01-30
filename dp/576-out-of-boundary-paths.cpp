/*
https://leetcode.com/problems/out-of-boundary-paths

There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn].
You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the
grid crossing the grid boundary). You can apply at most maxMove moves to the ball.

Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the
ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.


Example 1:

Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
Output: 6

Example 2:

Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
Output: 12


Constraints:

    1 <= m, n <= 50
    0 <= maxMove <= 50
    0 <= startRow < m
    0 <= startColumn < n
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<vector<vector<int>>> dp;
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int mod = 1e9 + 7;

    int paths(int m, int n, int moves, int maxMove, int currRow, int currCol) {
        if (currRow < 0 || currRow >= m || currCol < 0 || currCol >= n)
            return 1;
        if (moves >= maxMove)
            return 0;

        if (dp[currRow][currCol][moves] != -1)
            return dp[currRow][currCol][moves];

        int res = 0;
        for (pair<int, int> dir : dirs) {
            res =
                (res % mod +
                 paths(m, n, moves + 1, maxMove, currRow + dir.first, currCol + dir.second) % mod) %
                mod;
        }
        dp[currRow][currCol][moves] = res;
        return res;
    }

  public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        dp = vector<vector<vector<int>>>(m + 1,
                                         vector<vector<int>>(n + 1, vector<int>(maxMove + 1, -1)));
        return paths(m, n, 0, maxMove, startRow, startColumn);
    }
};

int main() {
    Solution sol;
    int res;

    int m1 = 2, n1 = 2, maxMove1 = 2, startRow1 = 0, startColumn1 = 0;
    res = sol.findPaths(m1, n1, maxMove1, startRow1, startColumn1);
    cout << res << endl;
    assert(res == 6);

    int m2 = 1, n2 = 3, maxMove2 = 3, startRow2 = 0, startColumn2 = 1;
    res = sol.findPaths(m2, n2, maxMove2, startRow2, startColumn2);
    cout << res << endl;
    assert(res == 12);

    return 0;
}