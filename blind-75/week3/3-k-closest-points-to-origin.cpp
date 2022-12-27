/*
https://leetcode.com/problems/k-closest-points-to-origin/

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an
integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1
- y2)2).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order
that it is in).


Example 1:

Input: points = {{1,3},{-2,2}}, k = 1
Output: {{-2,2}}
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just {{-2,2}}.

Example 2:

Input: points = {{3,3},{5,-1},{-2,4}}, k = 2
Output: {{3,3},{-2,4}}
Explanation: The answer {{-2,4},{3,3}} would also be accepted.


Constraints:

    1 <= k <= points.length <= 104
    -104 < xi, yi < 104
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
        multiset<pair<double, vector<int>>> closestPoints;
        vector<vector<int>> res;

        for (vector<int> point : points) {
            double distance = sqrt(pow(point[0], 2) + pow(point[1], 2));
            closestPoints.insert({distance, point});
            if (closestPoints.size() > k) {
                closestPoints.erase(--closestPoints.end());
            }
        }

        for (auto p : closestPoints) {
            res.push_back(p.second);
        }

        return res;
    }
};

int main() {
    // vector<vector<int>> points = {{9997, 9997}, {9996, 9998}};
    // vector<vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
    vector<vector<int>> points = {{2, 2}, {2, 2}, {3, 3}, {2, -2}, {1, 1}};
    int k = 4;

    Solution sol;
    vector<vector<int>> res = sol.kClosest(points, k);

    for (auto r : points) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (auto r : res) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}