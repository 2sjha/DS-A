/*
https://leetcode.com/problems/number-of-islands

Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water),
return *the number of islands*.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or
vertically. You may assume all four edges of the grid are all surrounded by water.


**Example 1:**

**Input:** grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
**Output:** 1

**Example 2:**

**Input:** grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
**Output:** 3


**Constraints:**

* `m == grid.length`
* `n == grid[i].length`
* `1 <= m, n <= 300`
* `grid[i][j]` is `'0'` or `'1'`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    void conquerIsland(vector<vector<char>> &grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();
        stack<pair<int, int>> dfs_st;
        pair<int, int> curr;
        int n_i, n_j;

        dfs_st.push({i, j});
        while (!dfs_st.empty()) {
            curr = dfs_st.top();
            dfs_st.pop();
            grid[curr.first][curr.second] = '-';

            for (int k = 0; k < 4; ++k) {
                n_i = curr.first + dir[k][0];
                n_j = curr.second + dir[k][1];

                if (n_i < 0 || n_i >= m) {
                    continue;
                }

                if (n_j < 0 || n_j >= n) {
                    continue;
                }

                if (grid[n_i][n_j] == '-') {
                    continue;
                }

                if (grid[n_i][n_j] == '0') {
                    grid[n_i][n_j] = '-';
                } else {
                    dfs_st.push({n_i, n_j});
                }
            }
        }
    }

  public:
    int numIslands(vector<vector<char>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        int islands = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '-') {
                    continue;
                }

                if (grid[i][j] == '0') {
                    grid[i][j] = '-';
                } else {
                    islands++;
                    conquerIsland(grid, i, j);
                }
            }
        }

        return islands;
    }
};

int main() {
    Solution sol;

    vector<vector<char>> grid_1 = {{'1', '1', '1', '1', '0'},
                                   {'1', '1', '0', '1', '0'},
                                   {'1', '1', '0', '0', '0'},
                                   {'0', '0', '0', '0', '0'}};
    int expected_1 = 1;
    int output_1 = sol.numIslands(grid_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<vector<char>> grid_2 = {{'1', '1', '0', '0', '0'},
                                   {'1', '1', '0', '0', '0'},
                                   {'0', '0', '1', '0', '0'},
                                   {'0', '0', '0', '1', '1'}};
    int expected_2 = 3;
    int output_2 = sol.numIslands(grid_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}