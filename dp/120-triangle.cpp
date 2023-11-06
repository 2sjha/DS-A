/*
https://leetcode.com/problems/triangle

Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on
index i on the current row, you may move to either index i or index i + 1 on the next row.


Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:

Input: triangle = [[-10]]
Output: -10


Constraints:

    1 <= triangle.length <= 200
    triangle[0].length == 1
    triangle[i].length == triangle[i - 1].length + 1
    -104 <= triangle[i][j] <= 104

Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the
triangle?
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int minimumTotal(vector<vector<int>> &triangle) {
        int n = triangle.size();
        vector<vector<int>> dp = triangle;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < triangle[i].size(); ++j) {
                dp[i][j] = 10001;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < triangle[i].size(); ++j) {
                if (i == 0 && j == 0) {
                    dp[i][j] = triangle[i][j];
                    continue;
                }

                if (i - 1 >= 0 && j < dp[i - 1].size()) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + triangle[i][j]);
                }

                if (i - 1 >= 0 && j - 1 >= 0 && j - 1 < dp[i - 1].size()) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + triangle[i][j]);
                }
            }
        }

        int mini = 10001;
        for (int i = 0; i < dp[n - 1].size(); ++i) {
            mini = min(mini, dp[n - 1][i]);
        }
        return mini;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> triangle1 = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    res = sol.minimumTotal(triangle1);
    cout << res << endl;
    assert(res == 11);

    vector<vector<int>> triangle2 = {{-10}};
    res = sol.minimumTotal(triangle2);
    cout << res << endl;
    assert(res == -10);

    vector<vector<int>> triangle3 = {{-1}, {-2, -3}};
    res = sol.minimumTotal(triangle3);
    cout << res << endl;
    assert(res == -4);

    return 0;
}