/*
https://leetcode.com/problems/island-perimeter

You are given `row x col` `grid` representing a map where `grid[i][j] = 1` represents land and
`grid[i][j] = 0` represents water.

Grid cells are connected **horizontally/vertically** (not diagonally). The `grid` is completely
surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes", meaning the water inside isn't connected to the water around the
island. One cell is a square with side length 1. The grid is rectangular, width and height don't
exceed 100. Determine the perimeter of the island.


**Example 1:**

**Input:** grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
**Output:** 16
**Explanation:** The perimeter is the 16 yellow stripes in the image above.

**Example 2:**

**Input:** grid = [[1]]
**Output:** 4

**Example 3:**

**Input:** grid = [[1,0]]
**Output:** 4


**Constraints:**

* `row == grid.length`
* `col == grid[i].length`
* `1 <= row, col <= 100`
* `grid[i][j]` is `0` or `1`.
* There is exactly one island in `grid`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int islandPerimeter(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int n_i, n_j, perimeter = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    for (int k = 0; k < 4; ++k) {
                        n_i = i + directions[k][0];
                        n_j = j + directions[k][1];

                        if (n_i < 0 || n_i == m || n_j < 0 || n_j == n || !grid[n_i][n_j])
                            perimeter++;
                    }
                }
            }
        }

        return perimeter;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid_1 = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
    int expected_1 = 16;
    int output_1 = sol.islandPerimeter(grid_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<vector<int>> grid_2 = {{1}};
    int expected_2 = 4;
    int output_2 = sol.islandPerimeter(grid_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<vector<int>> grid_3 = {{1, 0}};
    int expected_3 = 4;
    int output_3 = sol.islandPerimeter(grid_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}