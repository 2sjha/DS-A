/*
https://leetcode.com/problems/maximum-profit-in-job-scheduling

We have `n` jobs, where every job is scheduled to be done from `startTime[i]` to `endTime[i]`,
obtaining a profit of `profit[i]`.

You're given the `startTime`, `endTime` and `profit` arrays, return the maximum profit you can take
such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time `X` you will be able to start another job that starts at time
`X`.


**Example 1:**

****

**Input:** startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
**Output:** 120
**Explanation:** The subset chosen is the first and fourth job.
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

**Example 2:**

** **

**Input:** startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
**Output:** 150
**Explanation:** The subset chosen is the first, fourth and fifth job.
Profit obtained 150 = 20 + 70 + 60.

**Example 3:**

****

**Input:** startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
**Output:** 6


**Constraints:**

* `1 <= startTime.length == endTime.length == profit.length <= 5 * 10⁴`
* `1 <= startTime[i] < endTime[i] <= 10⁹`
* `1 <= profit[i] <= 10⁴`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<int> dp;
    bool noOverlap(vector<vector<int>> &jobs, int idx) {
        if (idx >= jobs.size() - 1)
            return true;

        return jobs[idx][1] < jobs[idx + 1][0];
    }

    int findNextNoOverlap(vector<vector<int>> &jobs, int idx) {
        int low = idx + 1;
        int high = jobs.size();
        int mid = jobs.size();
        while (low < high) {
            mid = (low + high) / 2;
            if (jobs[mid][0] < jobs[idx][1]) {
                low = mid + 1;
            } else if (jobs[mid][0] >= jobs[idx][1] && mid > 0 && jobs[mid - 1][0] < jobs[idx][1]) {
                break;
            } else {
                high = mid - 1;
            }
        }

        if (low == high)
            return low;
        else
            return mid;
    }

    int maxProfit(vector<vector<int>> &jobs, int idx) {
        if (idx >= jobs.size()) {
            return 0;
        }

        if (dp[idx] != -1) {
            return dp[idx];
        }

        int mxProfit = 0;
        if (noOverlap(jobs, idx)) {
            mxProfit = jobs[idx][2] + maxProfit(jobs, idx + 1);
        } else {
            int firstNoOverlap = findNextNoOverlap(jobs, idx);
            mxProfit = max(mxProfit, jobs[idx][2] + maxProfit(jobs, firstNoOverlap));
            for (int i = idx + 1; i <= firstNoOverlap && i < jobs.size(); ++i) {
                mxProfit = max(mxProfit, jobs[i][2] + maxProfit(jobs, findNextNoOverlap(jobs, i)));
            }
        }

        dp[idx] = mxProfit;
        return mxProfit;
    }

  public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
        int n = startTime.size();
        dp = vector<int>(n + 1, -1);

        vector<vector<int>> jobs(n, vector<int>(3, 0));
        for (int i = 0; i < n; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        sort(jobs.begin(), jobs.end());
        return maxProfit(jobs, 0);
    }
};

int main() {
    Solution sol;

    vector<int> startTime_1 = {1, 2, 3, 3};
    vector<int> endTime_1 = {3, 4, 5, 6};
    vector<int> profit_1 = {50, 10, 40, 70};
    int expected_1 = 120;
    int output_1 = sol.jobScheduling(startTime_1, endTime_1, profit_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> startTime_2 = {1, 2, 3, 4, 6};
    vector<int> endTime_2 = {3, 5, 10, 6, 9};
    vector<int> profit_2 = {20, 20, 100, 70, 60};
    int expected_2 = 150;
    int output_2 = sol.jobScheduling(startTime_2, endTime_2, profit_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<int> startTime_3 = {1, 1, 1};
    vector<int> endTime_3 = {2, 3, 4};
    vector<int> profit_3 = {5, 6, 4};
    int expected_3 = 6;
    int output_3 = sol.jobScheduling(startTime_3, endTime_3, profit_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}