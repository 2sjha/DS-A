/*
https://leetcode.com/problems/merge-intervals/

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
and return an array of the non-overlapping intervals that cover all the intervals in the input.


Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


Constraints:

    1 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 104
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool overlap(vector<int> &curr, vector<int> &next) {
        int curr_end = curr[1];
        int next_start = next[0];
        int next_end = next[1];

        return (next_start <= curr_end) || (next_end <= curr_end);
    }

  public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        int i = 0;
        vector<vector<int>> merged = vector<vector<int>>();
        sort(intervals.begin(), intervals.end());
        vector<int> curr_interval = intervals[i];

        while (i < intervals.size()) {
            if (i < intervals.size() - 1) {
                vector<int> next_interval = intervals[i + 1];
                if (overlap(curr_interval, next_interval)) {
                    curr_interval[0] = min(curr_interval[0], next_interval[0]);
                    curr_interval[1] = max(curr_interval[1], next_interval[1]);
                    ++i;
                } else {
                    merged.push_back(curr_interval);
                    ++i;
                    curr_interval = intervals[i];
                }
            } else {
                merged.push_back(curr_interval);
                ++i;
            }
        }

        return merged;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals1{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    auto res = sol.merge(intervals1);
    print2Dmatrix(res);

    vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};
    res = sol.merge(intervals2);
    print2Dmatrix(res);

    vector<vector<int>> intervals3 = {{1, 4}, {0, 1}};
    res = sol.merge(intervals3);
    print2Dmatrix(res);

    return 0;
}