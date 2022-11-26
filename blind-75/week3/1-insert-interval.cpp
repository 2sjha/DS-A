/*
https://leetcode.com/problems/insert-interval/

You are given an array of non-overlapping intervals intervals where intervals[i]
= [starti, endi] represent the start and the end of the ith interval and
intervals is sorted in ascending order by starti. You are also given an interval
newInterval = [start, end] that represents the start and end of another
interval.

Insert newInterval into intervals such that intervals is still sorted in
ascending order by starti and intervals still does not have any overlapping
intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

 

Constraints:

    0 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 105
    intervals is sorted by starti in ascending order.
    newInterval.length == 2
    0 <= start <= end <= 105
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  private:
  public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
        if (intervals.size() == 0) {
            return {newInterval};
        }

        int newInterval_start = newInterval[0];
        int newInterval_end = newInterval[1];
        vector<vector<int>> res;

        int merge_start = -1, merge_end = -1;
        for (auto interval : intervals) {
            int curr_start = interval[0];
            int curr_end = interval[1];

            if (merge_start != -1 and merge_end != -1) {
                res.push_back({merge_start, merge_end});
                merge_start = merge_end = -2;
            }

            if (newInterval_start > curr_end or newInterval_end < curr_start) {

                if (merge_start != -1 and merge_end == -1) {
                    merge_end = newInterval_end;
                    res.push_back({merge_start, merge_end});
                    merge_start = merge_end = -2;
                }

                res.push_back(interval);
                continue;
            }

            if (newInterval_start >= curr_start and newInterval_end <= curr_end) {
                res.push_back(interval);
                merge_start = merge_end = -2;
                continue;
            }

            if (newInterval_start >= curr_start) {
                merge_start = curr_start;
                continue;
            }

            if (newInterval_end <= curr_end) {
                merge_end = curr_end;
                continue;
            }
        }

        if (merge_start != -1 and merge_end == -1) {
            merge_end = newInterval_end;
            res.push_back({merge_start, merge_end});
        }

        if (merge_start == -1 and merge_end == -1) {
            res.push_back({newInterval_start, newInterval_end});
        }

        return res;
    }
};

int main() {
    // vector<vector<int>> intervals = {{1, 3}, {6, 9}};
    // vector<int> newInterval = {2, 5};

    vector<vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> newInterval = {4, 8};

    Solution s;
    vector<vector<int>> res = s.insert(intervals, newInterval);

    cout << "Result: " << endl;
    for (auto r : res) {
        for (int ij : r) {
            cout << ij << " ";
        }
        cout << endl;
    }
}