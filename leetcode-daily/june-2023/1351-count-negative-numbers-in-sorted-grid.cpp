/*
Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise,
return the number of negative numbers in grid.


Example 1:

Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.

Example 2:

Input: grid = [[3,2],[1,0]]
Output: 0


Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100
    -100 <= grid[i][j] <= 100


Follow up: Could you find an O(n + m) solution?
*/

#include "./../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    // For O(m+n) solution, start with the last column, find first negative number with lowest row
    // index. Other negative numbers will have row numbers greater than equal to this previous
    // negative row number. Just count (total rows - curr row) Then move leftwards towards positive
    // numbers
    int countNegatives(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size() - 1;
        int count = 0;

        int row = 0;
        while (n >= 0) {
            while (row < m) {
                if (grid[row][n] >= 0) {
                    row++;
                } else {
                    break;
                }
            }
            count += m - row;
            n--;
        }

        return count;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> grid1 = {{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}};
    res = sol.countNegatives(grid1);
    cout << res << endl;
    assert(res == 8);

    vector<vector<int>> grid2 = {{3, 2}, {1, 0}};
    res = sol.countNegatives(grid2);
    cout << res << endl;
    assert(res == 0);

    return 0;
}