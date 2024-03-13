/*
https://leetcode.com/problems/maximal-square

Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's
and return its area.


Example 1:

Input: matrix =
[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]] Output: 4

Example 2:

Input: matrix = [["0","1"],["1","0"]]
Output: 1

Example 3:

Input: matrix = [["0"]]
Output: 0


Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is '0' or '1'.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    int maximalSquare(vector<vector<char>> &matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 1000));

        // First row i = 0
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == '1') {
                dp[0][j] = 1;
            } else {
                dp[0][j] = 0;
            }
        }

        // First column j = 0
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == '1') {
                dp[i][0] = 1;
            } else {
                dp[i][0] = 0;
            }
        }

        // Mid matrix from i >= 1 ad j >= 1
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '0') {
                    dp[i][j] = 0;
                } else {
                    if (matrix[i - 1][j] == '1' && matrix[i][j - 1] == '1' &&
                        matrix[i - 1][j - 1] == '1') {
                        if (dp[i - 1][j] == dp[i][j - 1] && dp[i][j - 1] == dp[i - 1][j - 1]) {
                            dp[i][j] = dp[i - 1][j] + 1;
                        } else {
                            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                            dp[i][j] = min(dp[i][j], dp[i][j - 1]);
                            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                            dp[i][j]++;
                        }
                    } else {
                        dp[i][j] = 1;
                    }
                }
            }
        }

        int maxi = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                maxi = max(maxi, dp[i][j]);
            }
        }

        return maxi * maxi;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<char>> matrix1 = {{'1', '0', '1', '0', '0'},
                                    {'1', '0', '1', '1', '1'},
                                    {'1', '1', '1', '1', '1'},
                                    {'1', '0', '0', '1', '0'}};
    res = sol.maximalSquare(matrix1);
    cout << res << endl;
    assert(res == 4);

    vector<vector<char>> matrix2 = {{'0', '1'}, {'1', '0'}};
    res = sol.maximalSquare(matrix2);
    cout << res << endl;
    assert(res == 1);

    vector<vector<char>> matrix3 = {{'0'}};
    res = sol.maximalSquare(matrix3);
    cout << res << endl;
    assert(res == 0);

    vector<vector<char>> matrix4 = {{'1', '1', '1', '1', '0'},
                                    {'1', '1', '1', '1', '0'},
                                    {'1', '1', '1', '1', '1'},
                                    {'1', '1', '1', '1', '1'},
                                    {'0', '0', '1', '1', '1'}};
    res = sol.maximalSquare(matrix4);
    cout << res << endl;
    assert(res == 16);

    return 0;
}