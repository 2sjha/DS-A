/*
https://leetcode.com/problems/equal-row-and-column-pairs

Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri
and column cj are equal.

A row and column pair is considered equal if they contain the same elements in the same order (i.e.,
an equal array).


Example 1:

Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
Output: 1
Explanation: There is 1 equal row and column pair:
- (Row 2, Column 1): [2,7,7]

Example 2:

Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
Output: 3
Explanation: There are 3 equal row and column pairs:
- (Row 0, Column 0): [3,1,2,2]
- (Row 2, Column 2): [2,4,2,2]
- (Row 3, Column 2): [2,4,2,2]


Constraints:

    n == grid.length == grid[i].length
    1 <= n <= 200
    1 <= grid[i][j] <= 105
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void getColumn(vector<vector<int>> &grid, vector<int> &col, int col_num) {
        int n = grid.size();
        for (int i = 0; i < n; ++i) {
            col.push_back(grid[i][col_num]);
        }
    }

    bool checkEqual(vector<int> &row, vector<int> &col) {
        int n = row.size();
        bool equal = true;

        for (int i = 0; i < n; ++i) {
            if (row[i] != col[i]) {
                equal = false;
                break;
            }
        }

        return equal;
    }

  public:
    int equalPairs(vector<vector<int>> &grid) {
        int n = grid.size();
        vector<int> row, col;
        int count = 0;

        for (int i = 0; i < n; ++i) {
            row = grid[i];
            for (int j = 0; j < n; ++j) {
                col.clear();
                getColumn(grid, col, j);
                if (checkEqual(row, col)) {
                    count++;
                }
            }
        }

        return count;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> grid1 = {{3, 2, 1}, {1, 7, 6}, {2, 7, 7}};
    res = sol.equalPairs(grid1);
    cout << res << endl;
    assert(res == 1);

    vector<vector<int>> grid2 = {{3, 1, 2, 2}, {1, 4, 4, 5}, {2, 4, 2, 2}, {2, 4, 2, 2}};
    res = sol.equalPairs(grid2);
    cout << res << endl;
    assert(res == 3);

    return 0;
}