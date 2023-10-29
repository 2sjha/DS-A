/*
https://leetcode.com/problems/01-matrix

Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.


Example 1:

Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]

Example 2:

Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]


Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 104
    1 <= m * n <= 104
    mat[i][j] is either 0 or 1.
    There is at least one 0 in mat.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        vector<vector<int>> res;
        int m = mat.size();
        int n = mat[0].size();

        for (int i = 0; i < m; ++i) {
            vector<int> empty(n, INT_MAX - 10000);
            res.push_back(empty);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    res[i][j] = 0;
                } else if ((i - 1 >= 0 and mat[i - 1][j] == 0) or
                           (i + 1 <= m - 1 and mat[i + 1][j] == 0) or
                           (j - 1 >= 0 and mat[i][j - 1] == 0) or
                           (j + 1 <= n - 1 and mat[i][j + 1] == 0)) {
                    res[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int l = INT_MAX - 10000, u = INT_MAX - 10000;

                if (i - 1 >= 0) {
                    u = res[i - 1][j];
                }
                if (j - 1 >= 0) {
                    l = res[i][j - 1];
                }

                res[i][j] = min(res[i][j], 1 + min(l, u));
            }
        }

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int r = INT_MAX - 10000, d = INT_MAX - 10000;

                if (i + 1 <= m - 1) {
                    d = res[i + 1][j];
                }

                if (j + 1 <= n - 1) {
                    r = res[i][j + 1];
                }

                res[i][j] = min(res[i][j], 1 + min(r, d));
            }
        }

        return res;
    }
};

int main() {
    // vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    // vector<vector<int>> mat = {{0},{0},{0},{0},{0}};

    Solution sol;
    vector<vector<int>> res = sol.updateMatrix(mat);

    for (auto r : mat) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (auto r : res) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}