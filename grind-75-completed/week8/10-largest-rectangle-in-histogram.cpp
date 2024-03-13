/*
https://leetcode.com/problems/largest-rectangle-in-histogram

Given an array of integers `heights` representing the histogram's bar height where the width of each
bar is `1`, return *the area of the largest rectangle in the histogram*.


**Example 1:**

**Input:** heights = [2,1,5,6,2,3]
**Output:** 10
**Explanation:** The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

**Example 2:**

**Input:** heights = [2,4]
**Output:** 4


**Constraints:**

* `1 <= heights.length <= 10⁵`
* `0 <= heights[i] <= 10⁴`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int emptyStack(stack<pair<int, int>> &st, int curr_idx) {
        int res = 0;
        int back, back_begin_idx;

        while (!st.empty()) {
            back = st.top().first;
            back_begin_idx = st.top().second;
            st.pop();

            res = max(res, (curr_idx - back_begin_idx) * back);
        }
        return res;
    }

  public:
    int largestRectangleArea(vector<int> &heights) {
        int n = heights.size();
        int i = 0, res = 0, back = 0, back_begin_idx = 0;
        stack<pair<int, int>> st;

        for (; i < n; ++i) {
            if (st.empty()) {
                st.push({heights[i], i});
            } else if (!heights[i]) {
                res = max(res, emptyStack(st, i));
            } else if (heights[i] == st.top().first) {
                continue;
            } else if (heights[i] > st.top().first) {
                st.push({heights[i], i});
            } else {
                while (!st.empty() && heights[i] < st.top().first) {
                    back = st.top().first;
                    back_begin_idx = st.top().second;
                    st.pop();

                    res = max(res, (i - back_begin_idx) * back);
                }

                st.push({heights[i], back_begin_idx});
            }
        }

        res = max(res, emptyStack(st, i));
        return res;
    }
};

int main() {
    Solution sol;

    vector<int> heights_1 = {2, 1, 5, 6, 2, 3};
    int expected_1 = 10;
    int output_1 = sol.largestRectangleArea(heights_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> heights_2 = {2, 4};
    int expected_2 = 4;
    int output_2 = sol.largestRectangleArea(heights_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<int> heights_3 = {2, 1, 2};
    int expected_3 = 3;
    int output_3 = sol.largestRectangleArea(heights_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    vector<int> heights_4 = {4, 2, 0, 3, 2, 5};
    int expected_4 = 6;
    int output_4 = sol.largestRectangleArea(heights_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    vector<int> heights_5 = {1, 2, 2};
    int expected_5 = 4;
    int output_5 = sol.largestRectangleArea(heights_5);
    cout << output_5 << endl;
    assert(output_5 == expected_5);

    return 0;
}