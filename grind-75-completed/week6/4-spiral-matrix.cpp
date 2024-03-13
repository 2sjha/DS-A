/*
https://leetcode.com/problems/spiral-matrix/

Given an m x n matrix, return all elements of the matrix in spiral order.


Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]


Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        vector<int> res;
        int m = matrix.size();
        int n = matrix[0].size();
        int row_up = 0, row_down = m - 1;
        int col_left = 0, col_right = n - 1;

        while (row_up <= row_down || col_left <= col_right) {
            if (row_up <= row_down) {
                for (int j = col_left; j <= col_right; ++j) {
                    res.push_back(matrix[row_up][j]);
                }
                row_up++;
            }

            if (col_left <= col_right) {
                for (int i = row_up; i <= row_down; ++i) {
                    res.push_back(matrix[i][col_right]);
                }
                col_right--;
            }

            if (row_up <= row_down) {
                for (int j = col_right; j >= col_left; --j) {
                    res.push_back(matrix[row_down][j]);
                }
                row_down--;
            }

            if (col_left <= col_right) {
                for (int i = row_down; i >= row_up; --i) {
                    res.push_back(matrix[i][col_left]);
                }
                col_left++;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<int> res;

    vector<vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    res = sol.spiralOrder(matrix1);
    printArray(res);

    vector<vector<int>> matrix2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    res = sol.spiralOrder(matrix2);
    printArray(res);

    return 0;
}