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
  void print_line(vector<int> &line) {
    for (auto l : line) {
      cout << l << " ";
    }
    cout << endl;
  }

  void print_map(unordered_map<string, int> &line) {
    for (auto l : line) {
      cout << l.first << " " << l.second << endl;
    }
    cout << endl;
  }

  vector<int> getInterval(string tmp_ins) {
    int dashIdx = tmp_ins.find('-');
    int start = stoi(tmp_ins.substr(0, dashIdx));
    int end = stoi(tmp_ins.substr(dashIdx + 1, tmp_ins.length()));
    vector<int> interval = {start, end};
    return interval;
  }

public:
  vector<vector<int>> insert(vector<vector<int>> &intervals,
                             vector<int> &newInterval) {
    int newInterval_start = newInterval[0];
    int newInterval_end = newInterval[1];
    int sz_intervals = intervals.size();
    int last = intervals[sz_intervals - 1][1];
    vector<int> line(last + 1, -2);
    unordered_map<string, int> tmp;
    vector<vector<int>> res;

    for (int i = 0; i < intervals.size(); ++i) {
      int start = intervals[i][0];
      int end = intervals[i][1];

      for (int j = start; j <= end; ++j) {
        line[j] = i;
      }
    }

    print_line(line);

    for (int i = newInterval_start; i <= newInterval_end; ++i) {
      line[i] = -1;
    }

    print_line(line);

    for (int i = 0; i < last + 1;) {
      if (line[i] >= 0) {
        string tmp_ins = to_string(intervals[line[i]][0]) + '-' +
                         to_string(intervals[line[i]][1]);
        tmp[tmp_ins] = 1;
        ++i;
      } else if (line[i] == -2) {
        ++i;
      } else if (line[i] == -1) {
        int left_end = i;
        int right_end = i;
        vector<int> mergedInterval = {-1, -1};

        while (line[left_end] == -1) {
          left_end--;
        }

        while (line[right_end] == -1) {
          right_end++;
        }

        if (line[left_end] == -2) {
          mergedInterval[0] = left_end + 1;
        } else {
          mergedInterval[0] = intervals[line[left_end]][0];
          string tmp_ins = to_string(intervals[line[left_end]][0]) + '-' +
                           to_string(intervals[line[left_end]][1]);
          cout << "tmp_ins to be deleted: " << tmp_ins << endl;
          tmp[tmp_ins]--;
        }

        if (line[right_end] == -2) {
          mergedInterval[1] = right_end - 1;
          i = right_end;
        } else {
          mergedInterval[1] = intervals[line[right_end]][1];
          string tmp_ins = to_string(intervals[line[right_end]][0]) + '-' +
                           to_string(intervals[line[right_end]][1]);
          cout << "tmp_ins to be deleted: " << tmp_ins << endl;
          tmp[tmp_ins]--;
          i = right_end;
          while (line[i] == line[right_end]) {
            ++i;
          }
        }

        string tmp_ins =
            to_string(mergedInterval[0]) + '-' + to_string(mergedInterval[1]);
        tmp[tmp_ins]++;
      }
    }

    print_map(tmp);
    for (auto iter = tmp.begin(); iter != tmp.end(); iter++) {
      if (iter->second == 1) {
        res.push_back(getInterval(iter->first));
      }
    }
    return res;
  }
};

int main() {
  vector<vector<int>> intervals = {{1, 3}, {6, 9}};
  vector<int> newInterval = {2, 5};

//   vector<vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
//   vector<int> newInterval = {4, 8};

  Solution s;
  vector<vector<int>> res = s.insert(intervals, newInterval);
  reverse(res.begin(), res.end());

  cout << "Result: " << endl;
  for (auto r : res) {
    for (int ij : r) {
      cout << ij << " ";
    }
    cout << endl;
  }
}