/*
https://leetcode.com/problems/minimum-falling-path-sum

Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that
is either directly below or diagonally left/right. Specifically, the next element from position
(row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).


Example 1:

Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.

Example 2:

Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.


Constraints:

    n == matrix.length == matrix[i].length
    1 <= n <= 100
    -100 <= matrix[i][j] <= 100
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<vector<int>> directions = {{1, -1}, {1, 0}, {1, 1}};
    vector<vector<int>> dp;

    int getFallSum(vector<vector<int>> &matrix, int row, int col) {
        int n = matrix.size();
        int minSum = INT_MAX;

        if (row >= n)
            return 0;
        if (col < 0 or col >= n)
            return 1e7;
        if (dp[row][col] != 1e7)
            return dp[row][col];

        for (auto dir : directions) {
            minSum = min(minSum, getFallSum(matrix, row + dir[0], col + dir[1]));
        }
        dp[row][col] = matrix[row][col] + minSum;
        return dp[row][col];
    }

  public:
    int minFallingPathSum(vector<vector<int>> &matrix) {
        int n = matrix.size();
        int fallSum = 1e7;
        dp = vector<vector<int>>(n, vector<int>(n, 1e7));

        for (int j = 0; j < n; ++j) {
            fallSum = min(fallSum, getFallSum(matrix, 0, j));
        }
        return fallSum;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> matrix1 = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    res = sol.minFallingPathSum(matrix1);
    cout << res << endl;
    assert(res == 13);

    vector<vector<int>> matrix2 = {{-19, 57}, {-40, -5}};
    res = sol.minFallingPathSum(matrix2);
    cout << res << endl;
    assert(res == -59);

    return 0;
}