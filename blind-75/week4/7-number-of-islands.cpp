/*
https://leetcode.com/problems/number-of-islands/

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return
the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or
vertically. You may assume all four edges of the grid are all surrounded by water.


Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3


Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int numIslands(vector<vector<char>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        bool visited[n][m];
        memset(visited, false, sizeof(visited));

        
    }
};

int main() {
    vector<vector<char>> grid = {{}};

    Solution sol;
    auto res = sol.numIslands(grid);
    cout << res << endl;
    return 0;
}