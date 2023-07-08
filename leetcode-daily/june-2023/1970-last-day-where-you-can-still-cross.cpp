/*
https://leetcode.com/problems/last-day-where-you-can-still-cross/

There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given
integers row and col representing the number of rows and columns in the matrix, respectively.

Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with
water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith
day, the cell on the rith row and cith column (1-based coordinates) will be covered with water
(i.e., changed to 1).

You want to find the last day that it is possible to walk from the top to the bottom by only walking
on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You
can only travel in the four cardinal directions (left, right, up, and down).

Return the last day where it is possible to walk from the top to the bottom by only walking on land
cells.


Example 1:

Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
Output: 2
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 2.

Example 2:

Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
Output: 1
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 1.

Example 3:

Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
Output: 3
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 3.


Constraints:

    2 <= row, col <= 2 * 104
    4 <= row * col <= 2 * 104
    cells.length == row * col
    1 <= ri <= row
    1 <= ci <= col
    All the values of cells are unique.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// UNSOLVED - TLE
// Approach too brute-forcey

class Solution {
  private:
    vector<vector<int>> cells;
    vector<vector<bool>> grid;
    int row;
    int col;

    void initGrid(int row, int col) { grid = vector<vector<bool>>(row, vector<bool>(col, false)); }

    void clearGrid() {
        for (int i = 0; i < this->row; ++i) {
            for (int j = 0; j < this->col; ++j) {
                grid[i][j] = false;
            }
        }
    }

    bool checkVisited(set<pair<int, int>> &visited, pair<int, int> curr) {
        return visited.find(curr) != visited.end();
    }

    bool canReachBottom(int start_col) {
        stack<pair<int, int>> dfs_st;
        set<pair<int, int>> visited;

        dfs_st.push({0, start_col});

        pair<int, int> curr;
        while (!dfs_st.empty()) {
            curr = dfs_st.top();
            dfs_st.pop();

            if (curr.first == row - 1) {
                return true;
            }
            if (this->grid[curr.first][curr.second] == true) {
                continue;
            }

            if (checkVisited(visited, curr)) {
                continue;
            }
            visited.insert({curr.first, curr.second});

            if (curr.first < row - 1 && !this->grid[curr.first + 1][curr.second] &&
                !checkVisited(visited, {curr.first + 1, curr.second})) {
                dfs_st.push({curr.first + 1, curr.second});
            }

            if (curr.second > 0 && !this->grid[curr.first][curr.second - 1] &&
                !checkVisited(visited, {curr.first, curr.second - 1})) {
                dfs_st.push({curr.first, curr.second - 1});
            }

            if (curr.second < col - 1 && !this->grid[curr.first][curr.second + 1] &&
                !checkVisited(visited, {curr.first, curr.second + 1})) {
                dfs_st.push({curr.first, curr.second + 1});
            }

            if (curr.first > 0 && !this->grid[curr.first - 1][curr.second] &&
                !checkVisited(visited, {curr.first - 1, curr.second})) {
                dfs_st.push({curr.first - 1, curr.second});
            }
        }

        return false;
    }

    bool canCross(int idx) {
        clearGrid();
        for (int i = 0; i <= idx; ++i) {
            grid[cells[i][0] - 1][cells[i][1] - 1] = true;
        }

        for (int i = 0; i < col; ++i) {
            if (canReachBottom(i)) {
                return true;
            }
        }

        return false;
    }

  public:
    int latestDayToCross(int row, int col, vector<vector<int>> &cells) {
        this->cells = cells;
        this->row = row;
        this->col = col;
        initGrid(row, col);

        // Binary Search
        int low = 0, high = cells.size() - 1, mid;
        while (low <= high) {
            mid = (high + low) / 2;
            if (mid < cells.size() - 1 && canCross(mid) && !canCross(mid + 1)) {
                break;
            } else if (mid < cells.size() - 1 && canCross(mid) && canCross(mid + 1)) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return mid + 1;
    }
};

int main() {
    Solution sol;
    int res;

    int row1 = 2;
    int col1 = 2;
    vector<vector<int>> cells1 = {{1, 1}, {2, 1}, {1, 2}, {2, 2}};
    res = sol.latestDayToCross(row1, col1, cells1);
    cout << res << endl;
    assert(res == 2);

    int row2 = 2;
    int col2 = 2;
    vector<vector<int>> cells2 = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    res = sol.latestDayToCross(row2, col2, cells2);
    cout << res << endl;
    assert(res == 1);

    int row3 = 3;
    int col3 = 3;
    vector<vector<int>> cells3 = {{1, 2}, {2, 1}, {3, 3}, {2, 2}, {1, 1},
                                  {1, 3}, {2, 3}, {3, 2}, {3, 1}};
    res = sol.latestDayToCross(row3, col3, cells3);
    cout << res << endl;
    assert(res == 3);

    return 0;
}