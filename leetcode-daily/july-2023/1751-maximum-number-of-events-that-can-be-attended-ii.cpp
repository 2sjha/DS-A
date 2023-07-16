/*
https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/

You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event
starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of
valuei. You are also given an integer k which represents the maximum number of events you can
attend.

You can only attend one event at a time. If you choose to attend an event, you must attend the
entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of
them starts and the other ends on the same day.

Return the maximum sum of values that you can receive by attending events.


Example 1:

Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
Output: 7
Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.

Example 2:

Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
Output: 10
Explanation: Choose event 2 for a total value of 10.
Notice that you cannot attend any other event as they overlap, and that you do not have to attend k
events.

Example 3:

Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
Output: 9
Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest
valued three.


Constraints:

    1 <= k <= events.length
    1 <= k * events.length <= 10^6
    1 <= startDayi <= endDayi <= 10^9
    1 <= valuei <= 10^6
*/

// UNSOLVED - still leads to wrong answer
// Similar to Knapsack but with extra details

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool overlap(vector<int> &event_i, vector<int> &event_j) {
        // Event i starts inside Event j's interval
        if (event_i[0] >= event_j[0] && event_i[0] <= event_j[1]) {
            return true;
        }

        // Event j starts inside Even i's interval
        if (event_j[0] >= event_i[0] && event_j[0] <= event_i[1]) {
            return true;
        }

        return false;
    }

    int findNextEventIdx(vector<vector<int>> &events, int chosen_idx) {
        int idx = chosen_idx - 1;
        for (; idx >= 0; --idx) {
            if (!overlap(events[chosen_idx], events[idx])) {
                break;
            }
        }

        return idx;
    }

  public:
    int maxValue(vector<vector<int>> &events, int k) {
        int n = events.size();
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
        sort(events.begin(), events.end());

        print2Dmatrix(events);

        int next_event_idx;
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= n; ++j) {
                next_event_idx = findNextEventIdx(events, j - 1);
                if (next_event_idx < n && next_event_idx >= 0) {
                    dp[i][j] = max(events[j - 1][2] + dp[i - 1][next_event_idx + 1], dp[i][j - 1]);
                } else {
                    dp[i][j] = events[j - 1][2];
                }
            }
        }

        print2Dmatrix(dp);

        return dp[k][n];
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> events1 = {{1, 2, 4}, {3, 4, 3}, {2, 3, 1}};
    int k1 = 2;
    res = sol.maxValue(events1, k1);
    cout << res << endl;
    assert(res == 7);

    vector<vector<int>> events2 = {{1, 2, 4}, {3, 4, 3}, {2, 3, 10}};
    int k2 = 2;
    res = sol.maxValue(events2, k2);
    cout << res << endl;
    assert(res == 10);

    vector<vector<int>> events3 = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}};
    int k3 = 3;
    res = sol.maxValue(events3, k3);
    cout << res << endl;
    assert(res == 9);

    vector<vector<int>> events4 = {{69, 83, 61}, {44, 90, 19}, {26, 87, 9}};
    int k4 = 3;
    res = sol.maxValue(events4, k4);
    cout << res << endl;
    assert(res == 61);

    vector<vector<int>> events5 = {{21, 77, 43}, {2, 74, 47},  {6, 59, 22}, {47, 47, 38},
                                   {13, 74, 57}, {27, 55, 27}, {8, 15, 8}};
    int k5 = 4;
    res = sol.maxValue(events5, k5);
    cout << res << endl;
    assert(res == 57);

    vector<vector<int>> events6 = {
        {11, 17, 56}, {24, 40, 53}, {5, 62, 67}, {66, 69, 84}, {56, 89, 15}};
    int k6 = 2;
    res = sol.maxValue(events6, k6);
    cout << res << endl;
    assert(res == 151);

    return 0;
}

// int findNextEventIdx(vector<vector<int>> &events, int chosen_idx) {
//     int n = events.size();
//     int start = -1;
//     int end = chosen_idx - 1;
//     int mid;

//     while (start < end) {
//         mid = (start + end) / 2;
//         if (!overlap(events, chosen_idx, mid) && mid + 1 < n &&
//             overlap(events, chosen_idx, mid + 1)) {
//             break;
//         } else if (overlap(events, chosen_idx, mid) && mid + 1 < n &&
//                    overlap(events, chosen_idx, mid + 1)) {
//             start = mid + 1;
//         } else {
//             end = mid;
//         }
//     }

//     return mid;
// }