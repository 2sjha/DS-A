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
  public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
        vector<vector<int>> result;

        int merge = 0;
        for (auto currInterval : intervals) {
            if ((newInterval[0] >= currInterval[0] and newInterval[0] <= currInterval[1]) or
                (newInterval[1] >= currInterval[0] and newInterval[1] <= currInterval[1]) or
                (newInterval[0] <= currInterval[0] and newInterval[1] >= currInterval[1]) or
                (newInterval[0] >= currInterval[0] and newInterval[1] <= currInterval[1])) {
                newInterval[0] = min(newInterval[0], currInterval[0]);
                newInterval[1] = max(newInterval[1], currInterval[1]);
                merge = 2;
            } else {
                if (merge == 2) {
                    result.push_back(newInterval);
                    merge = 1;
                }
                result.push_back(currInterval);
            }
        }

        if (merge == 0) {
            result.push_back(newInterval);
        }

        return result;
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