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
    pair<int, int> helper(vector<int> &height) {
        int n = height.size();
        int count = 0;

        if (n <= 2) {
            return {0, n};
        }

        int res = 0;
        queue<int> q;
        if (height[0] > height[1]) {
            q.push(0);
        }
        count++;

        for (int i = 1; i < n - 1; ++i) {
            q.push(i);

            if (q.size() >= 2 && height[q.back()] >= height[q.front()]) {
                int first = q.front();
                q.pop();
                count++;

                while (q.size() != 1) {
                    res += height[first] - height[q.front()];
                    q.pop();
                    count++;
                }
            }
        }

        if (height[n - 1] >= height[q.front()]) {
            int first = q.front();
            q.pop();
            count++;

            while (!q.empty()) {
                res += height[first] - height[q.front()];
                q.pop();
                count++;
            }
        }

        return {res, count};
    }

  public:
    int trap(vector<int> &height) {
        int n = height.size();
        int res = 0;
        pair<int, int> part1 = helper(height);
        res = part1.first;

        if (part1.second == n) {
            return res;
        } else {
            int sz = n - part1.second;
            vector<int> v(sz + 1, 0);
            for (int i = 0; i <= sz; i++) {
                v[i] = height[n - 1 - i];
            }

            pair<int, int> part2 = helper(v);
            res += part2.first;
        }

        return res;
    }
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

    vector<int> height_3 = {4, 2, 3};
    int expected_3 = 1;
    int output_3 = sol.trap(height_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}