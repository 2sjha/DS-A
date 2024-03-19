/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the
`i^{th}` day.

On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of
the stock at any time. However, you can buy it then immediately sell it on the **same day**.

Find and return *the **maximum** profit you can achieve*.


**Example 1:**

**Input:** prices = [7,1,5,3,6,4]
**Output:** 7
**Explanation:** Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.

**Example 2:**

**Input:** prices = [1,2,3,4,5]
**Output:** 4
**Explanation:** Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.

**Example 3:**

**Input:** prices = [7,6,4,3,1]
**Output:** 0
**Explanation:** There is no way to make a positive profit, so we never buy the stock to achieve the
maximum profit of 0
.


**Constraints:**

* `1 <= prices.length <= 3 * 10⁴`
* `0 <= prices[i] <= 10⁴`
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<vector<int>> dp;

    int helper(vector<int> &prices, int idx, int holding) {
        if (idx == prices.size() - 1) {
            return holding ? prices[idx] : 0;
        }

        if (holding && dp[1][idx] != -1)
            return dp[1][idx];
        if (!holding && dp[0][idx] != -1)
            return dp[0][idx];

        int profit = 0;
        if (holding) {
            profit = max(helper(prices, idx + 1, 1),                // dont sell here
                         prices[idx] + helper(prices, idx + 1, 0)); // sell here

            dp[1][idx] = profit;
        } else {
            profit = max(helper(prices, idx + 1, 0),                 // dont buy here
                         -prices[idx] + helper(prices, idx + 1, 1)); // buy here

            dp[0][idx] = profit;
        }

        return profit;
    }

  public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        this->dp = vector<vector<int>>(2, vector<int>(n + 1, -1));

        return helper(prices, 0, 0);
    }
};

int main() {
    Solution sol;

    vector<int> prices_1 = {7, 1, 5, 3, 6, 4};
    int expected_1 = 7;
    int output_1 = sol.maxProfit(prices_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> prices_2 = {1, 2, 3, 4, 5};
    int expected_2 = 4;
    int output_2 = sol.maxProfit(prices_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<int> prices_3 = {7, 6, 4, 3, 1};
    int expected_3 = 0;
    int output_3 = sol.maxProfit(prices_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}