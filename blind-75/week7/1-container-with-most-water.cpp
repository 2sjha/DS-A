/*
https://leetcode.com/problems/container-with-most-water/

You are given an integer array height of length n. There are n vertical lines drawn such that the
two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the
most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.


Example 1:

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case,
the max area of water (blue section) the container can contain is 49.

Example 2:

Input: height = [1,1]
Output: 1


Constraints:

    n == height.length
    2 <= n <= 105
    0 <= height[i] <= 104
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int maxArea(vector<int> &height) {
        int n = height.size();
        int start = 0;
        int end = n - 1;
        int maxArea = INT_MIN;
        int area;
        while (start < end) {
            area = (end - start) * min(height[start], height[end]);
            maxArea = max(area, maxArea);

            if (height[start] < height[end]) {
                start++;
            } else {
                end--;
            }
        }

        return maxArea;
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> heights1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    res = sol.maxArea(heights1);
    cout << res << endl;
    assert(res == 49);

    vector<int> heights2 = {1, 1};
    res = sol.maxArea(heights2);
    cout << res << endl;
    assert(res == 1);

    vector<int> heights3 = {1, 2, 1};
    res = sol.maxArea(heights3);
    cout << res << endl;
    assert(res == 2);

    vector<int> heights4 = {1, 0, 0, 0, 0, 0, 0, 2, 2};
    res = sol.maxArea(heights4);
    cout << res << endl;
    assert(res == 8);

    vector<int> heights5 = {1, 2, 4, 3};
    res = sol.maxArea(heights5);
    cout << res << endl;
    assert(res == 4);

    vector<int> heights6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    res = sol.maxArea(heights6);
    cout << res << endl;
    assert(res == 25);

    vector<int> heights7 = {2, 3, 10, 5, 7, 8, 9};
    res = sol.maxArea(heights7);
    cout << res << endl;
    assert(res == 36);

    return 0;
}