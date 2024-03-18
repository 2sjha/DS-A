/*
https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons

There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons
are represented as a 2D integer array `points` where `points[i] = [xstart, xend]` denotes a balloon
whose **horizontal diameter** stretches between `xstart` and `xend`. You do not know the exact
y-coordinates of the balloons.

Arrows can be shot up **directly vertically** (in the positive y-direction) from different points
along the x-axis. A balloon with `xstart` and `xend` is **burst** by an arrow shot at `x` if `xstart
<= x <= xend`. There is **no limit** to the number of arrows that can be shot. A shot arrow keeps
traveling up infinitely, bursting any balloons in its path.

Given the array `points`, return *the **minimum** number of arrows that must be shot to burst all
balloons*.


**Example 1:**

**Input:** points = [[10,16},{2,8},{1,6},{7,12]]
**Output:** 2
**Explanation:** The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

**Example 2:**

**Input:** points = [[1,2},{3,4},{5,6},{7,8]]
**Output:** 4
**Explanation:** One arrow needs to be shot for each balloon for a total of 4 arrows.

**Example 3:**

**Input:** points = [[1,2},{2,3},{3,4},{4,5]]
**Output:** 2
**Explanation:** The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].


**Constraints:**

* `1 <= points.length <= 10⁵`
* `points[i].length == 2`
* `-2³¹ <= xstart < xend <= 2³¹ - 1`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool overlap(vector<int> circle_a, vector<int> circle_b) {
        return (circle_b[0] >= circle_a[0] && circle_b[0] <= circle_a[1]);
    }

  public:
    int findMinArrowShots(vector<vector<int>> &points) {
        sort(points.begin(), points.end());
        int i = 0, res = 0, n = points.size();
        vector<int> common = {0, 0};
        while (i < n) {
            common = points[i];
            while (i < n - 1 && overlap(common, points[i + 1]) && common[0] <= common[1]) {
                common[0] = max(common[0], points[i + 1][0]);
                common[1] = min(common[1], points[i + 1][1]);
                i++;
            }
            i++;
            res++;
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> points_1 = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    int expected_1 = 2;
    int output_1 = sol.findMinArrowShots(points_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<vector<int>> points_2 = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int expected_2 = 4;
    int output_2 = sol.findMinArrowShots(points_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<vector<int>> points_3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    int expected_3 = 2;
    int output_3 = sol.findMinArrowShots(points_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    vector<vector<int>> points_4 = {{2, 3}, {2, 3}};
    int expected_4 = 1;
    int output_4 = sol.findMinArrowShots(points_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    vector<vector<int>> points_5 = {
        {77171087, 133597895}, {45117276, 135064454}, {80695788, 90089372}, {91705403, 110208054},
        {52392754, 127005153}, {53999932, 118094992}, {11549676, 55543044}, {43947739, 128157751},
        {55636226, 105334812}, {69348094, 125645633}};
    int expected_5 = 2;
    int output_5 = sol.findMinArrowShots(points_5);
    cout << output_5 << endl;
    assert(output_5 == expected_5);

    return 0;
}