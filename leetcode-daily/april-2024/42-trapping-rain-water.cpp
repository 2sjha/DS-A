/*
https://leetcode.com/problems/trapping-rain-water

Given `n` non-negative integers representing an elevation map where the width of each bar is `1`,
compute how much water it can trap after raining.


**Example 1:**

**Input:** height = [0,1,0,2,1,0,1,3,2,1,2,1]
**Output:** 6
**Explanation:** The above elevation map (black section) is represented by array
[0,1,0,2,1,0,1,3,2,1,2,1]. In this case , 6 units of rain water (blue section) are being trapped.

**Example 2:**

**Input:** height = [4,2,0,3,2,5]
**Output:** 9


**Constraints:**

* `n == height.length`
* `1 <= n <= 2 * 10⁴`
* `0 <= height[i] <= 10⁵`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int flowLeft(vector<int> &height, vector<int> &st) {
        int i = 0, n = height.size();
        st.push_back(height[i++]);

        while (i < n && height[i] >= st.back()) {
            st.pop_back();
            st.push_back(height[i++]);
        }
        return i;
    }

    int collect(vector<int> &height, bool end) {
        vector<int> st;
        int i = flowLeft(height, st), res = 0, n = height.size();

        while (i < n) {
            while (i < n && height[i] < st[0]) {
                st.push_back(height[i++]);
            }

            if (i == n) {
                if (!end) {
                    reverse(st.begin(), st.end());
                    res += collect(st, true);
                }
            } else {
                for (int j = 1; j < st.size(); j++) {
                    res += st[0] - st[j];
                }
                st.clear();
                st.push_back(height[i++]);
            }
        }

        return res;
    }

  public:
    int trap(vector<int> &height) { return collect(height, false); }
};

int main() {
    Solution sol;

    vector<int> height_1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int expected_1 = 6;
    int output_1 = sol.trap(height_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> height_2 = {4, 2, 0, 3, 2, 5};
    int expected_2 = 9;
    int output_2 = sol.trap(height_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}