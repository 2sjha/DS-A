/*
https://leetcode.com/problems/maximal-rectangle

Given a `rows x cols` binary `matrix` filled with `0`'s and `1`'s, find the largest rectangle
containing only `1`'s and return *its area*.


**Example 1:**

**Input:** matrix =
[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
**Output:** 6
**Explanation:** The maximal rectangle is shown in the above picture.

**Example 2:**

**Input:** matrix = [["0"]]
**Output:** 0

**Example 3:**

**Input:** matrix = [["1"]]
**Output:** 1


**Constraints:**

* `rows == matrix.length`
* `cols == matrix[i].length`
* `1 <= row, cols <= 200`
* `matrix[i][j]` is `'0'` or `'1'`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int largestRectangleArea(vector<int> &heights) {
        stack<pair<int, int>> st;
        int i = 0, n = heights.size(), max_area = 0, begin = 0;
        while (i < n) {
            begin = i;
            while (!st.empty() && heights[i] < st.top().second) {
                max_area = max(max_area, (i - st.top().first) * st.top().second);
                begin = st.top().first;
                st.pop();
            }
            st.push({begin, heights[i]});
            i++;
        }

        while (!st.empty()) {
            max_area = max(max_area, (i - st.top().first) * st.top().second);
            st.pop();
        }
        return max_area;
    }

  public:
    int maximalRectangle(vector<vector<char>> &matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> heights(m, vector<int>(n, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                int height = 0;
                if (matrix[i][j] == '1') {
                    if (i > 0 && heights[i - 1][j] > 1) {
                        height = heights[i - 1][j] - 1;
                    } else {
                        height = 0;
                        int k = i;
                        while (k < m && matrix[k][j] == '1') {
                            height++;
                            k++;
                        }
                    }
                }
                heights[i][j] = height;
            }
        }

        int max_area = INT_MIN;
        for (int i = 0; i < m; ++i) {
            max_area = max(max_area, largestRectangleArea(heights[i]));
        }
        return max_area;
    }
};

int main() {
    Solution sol;

    vector<vector<char>> matrix_1 = {{'1', '0', '1', '0', '0'},
                                     {'1', '0', '1', '1', '1'},
                                     {'1', '1', '1', '1', '1'},
                                     {'1', '0', '0', '1', '0'}};
    int expected_1 = 6;
    int output_1 = sol.maximalRectangle(matrix_1);
    cout << output_1 << endl;
    // assert(output_1 == expected_1);

    vector<vector<char>> matrix_2 = {{'0'}};
    int expected_2 = 0;
    int output_2 = sol.maximalRectangle(matrix_2);
    cout << output_2 << endl;
    // assert(output_2 == expected_2);

    vector<vector<char>> matrix_3 = {{'1'}};
    int expected_3 = 1;
    int output_3 = sol.maximalRectangle(matrix_3);
    cout << output_3 << endl;
    // assert(output_3 == expected_3);

    vector<vector<char>> matrix_4 = {
        {'0', '0', '1', '0'}, {'0', '0', '1', '0'}, {'0', '0', '1', '0'}, {'0', '0', '1', '1'},
        {'0', '1', '1', '1'}, {'0', '1', '1', '1'}, {'1', '1', '1', '1'}};
    int expected_4 = 9;
    int output_4 = sol.maximalRectangle(matrix_4);
    cout << output_4 << endl;
    // assert(output_4 == expected_4);

    vector<vector<char>> matrix_5 = {{'0', '0', '1'}, {'1', '1', '1'}};
    int expected_5 = 3;
    int output_5 = sol.maximalRectangle(matrix_5);
    cout << output_5 << endl;
    // assert(output_5 == expected_5);

    vector<vector<char>> matrix_6 = {
        {'1', '0', '0', '0', '1'}, {'1', '1', '0', '1', '1'}, {'1', '1', '1', '1', '1'}};
    int expected_6 = 5;
    int output_6 = sol.maximalRectangle(matrix_6);
    cout << output_6 << endl;
    // assert(output_6 == expected_6);

    return 0;
}