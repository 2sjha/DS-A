/*
https://leetcode.com/problems/minimum-cost-for-tickets

You have planned some train traveling one year in advance. The days of the year in which you will
travel are given as an integer array days. Each day is an integer from 1 to 365.

Train tickets are sold in three different ways:

    a 1-day pass is sold for costs[0] dollars,
    a 7-day pass is sold for costs[1] dollars, and
    a 30-day pass is sold for costs[2] dollars.

The passes allow that many days of consecutive travel.

    For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7,
and 8.

Return the minimum number of dollars you need to travel every day in the given list of days.


Example 1:

Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total, you spent $11 and covered all the days of your travel.

Example 2:

Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total, you spent $17 and covered all the days of your travel.


Constraints:

    1 <= days.length <= 365
    1 <= days[i] <= 365
    days is in strictly increasing order.
    costs.length == 3
    1 <= costs[i] <= 1000
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int searchIdx(vector<int> &days, int idx, int diff) {
        int day = days[idx];
        int searchDay = day + diff;
        int n = days.size();

        int low = idx, high = n - 1, mid;
        while (low < high) {
            mid = (low + high) / 2;
            if (mid == n - 1) {
                if (days[mid] >= searchDay)
                    return n - 1;
                else
                    return n;
            } else {
                if (days[mid] < searchDay && days[mid + 1] >= searchDay)
                    return mid + 1;
                else if (days[mid] < searchDay && days[mid + 1] < searchDay)
                    low = mid + 1;
                else
                    high = mid;
            }
        }

        return n;
    }

    int minCostTickets(vector<int> &days, vector<int> &costs, int idx, vector<int> &dp) {
        int n = days.size();
        int minCost = 1e7;

        if (idx >= n)
            return 0;

        if (dp[idx] != 1e7) {
            return dp[idx];
        }

        // In this case we actually want to find the upper bound of a value,
        // it is easier to use upper_bound than to write binary search for specific context
        // (PS: I wasted a lot of time in writing this binary search)

        minCost = min(minCost, costs[0] + minCostTickets(days, costs, idx + 1, dp));
        int nextIdxAfter7days = upper_bound(days.begin(), days.end(), days[idx] + 6) - days.begin();
        minCost = min(minCost, costs[1] + minCostTickets(days, costs, nextIdxAfter7days, dp));
        int nextIdxAfter30days = upper_bound(days.begin(), days.end(), days[idx] + 29) - days.begin();
        minCost = min(minCost, costs[2] + minCostTickets(days, costs, nextIdxAfter30days, dp));

        // minCost = min(minCost, costs[0] + minCostTickets(days, costs, idx + 1, dp));
        // int nextIdxAfter7days = searchIdx(days, idx, 7);
        // minCost = min(minCost, costs[1] + minCostTickets(days, costs, nextIdxAfter7days, dp));
        // int nextIdxAfter30days = searchIdx(days, idx, 30);
        // minCost = min(minCost, costs[2] + minCostTickets(days, costs, nextIdxAfter30days, dp));

        dp[idx] = minCost;
        return minCost;
    }

  public:
    int mincostTickets(vector<int> &days, vector<int> &costs) {
        int n = days.size();
        vector<int> dp(n, 1e7);
        return minCostTickets(days, costs, 0, dp);
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> days1 = {1, 4, 6, 7, 8, 20};
    vector<int> costs1 = {2, 7, 15};
    res = sol.mincostTickets(days1, costs1);
    cout << res << endl;
    assert(res == 11);

    vector<int> days2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    vector<int> costs2 = {2, 7, 15};
    res = sol.mincostTickets(days2, costs2);
    cout << res << endl;
    assert(res == 17);

    vector<int> days3 = {1,  2,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
                         18, 20, 21, 24, 25, 27, 28, 29, 30, 31, 34, 37, 38, 39, 41, 43,
                         44, 45, 47, 48, 49, 54, 57, 60, 62, 63, 66, 69, 70, 72, 74, 76,
                         78, 80, 81, 82, 83, 84, 85, 88, 89, 91, 93, 94, 97, 99};
    vector<int> costs3 = {9, 38, 134};
    res = sol.mincostTickets(days3, costs3);
    cout << res << endl;
    assert(res == 423);
    return 0;
}