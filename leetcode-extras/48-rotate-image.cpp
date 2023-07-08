/*
https://leetcode.com/problems/rotate-image/

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.


Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:

Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]


Constraints:

    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void swap(vector<int> &tmp, int idx, vector<vector<int>> &matrix, int row, int col) {
        int sw = tmp[idx];
        tmp[idx] = matrix[row][col];
        matrix[row][col] = sw;
    }

    void rotate(vector<vector<int>> &matrix, int start, int end) {
        if (start >= end) {
            return;
        }

        // Init tmp for swap
        vector<int> tmp(end - start, 0);
        for (int j = start; j < end; ++j) {
            tmp[j - start] = matrix[start][j];
        }

        // rotate outer ring
        for (int i = start; i < end; ++i) {
            swap(tmp, i - start, matrix, i, end);
        }
        for (int j = end; j > start; j--) {
            swap(tmp, end - j, matrix, end, j);
        }
        for (int i = end; i > start; i--) {
            swap(tmp, end - i, matrix, i, start);
        }
        for (int j = start; j < end; ++j) {
            swap(tmp, j - start, matrix, start, j);
        }

        rotate(matrix, start + 1, end - 1);
    }

  public:
    void rotate(vector<vector<int>> &matrix) { rotate(matrix, 0, matrix.size() - 1); }
};

int main() {
    Solution sol;

    vector<vector<int>> matrix1 = {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
    cout << "original:" << endl;
    print2Dmatrix(matrix1);
    sol.rotate(matrix1);
    cout << "rotated:" << endl;
    print2Dmatrix(matrix1);

    vector<vector<int>> matrix2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "original:" << endl;
    print2Dmatrix(matrix2);
    sol.rotate(matrix2);
    cout << "rotated:" << endl;
    print2Dmatrix(matrix2);

    vector<vector<int>> matrix3 = {{4, 8}, {3, 6}};
    cout << "original:" << endl;
    print2Dmatrix(matrix3);
    sol.rotate(matrix3);
    cout << "rotated:" << endl;
    print2Dmatrix(matrix3);

    return 0;
}