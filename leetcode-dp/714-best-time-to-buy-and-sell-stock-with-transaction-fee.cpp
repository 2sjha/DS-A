/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee

You are given an array prices where prices[i] is the price of a given stock on the ith day, and an
integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you
need to pay the transaction fee for each transaction.

Note:

    You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before
you buy again). The transaction fee is only charged once for each stock purchase and sale.


Example 1:

Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

Example 2:

Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6


Constraints:

    1 <= prices.length <= 5 * 104
    1 <= prices[i] < 5 * 104
    0 <= fee < 5 * 104

*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  private:
    vector<int> dp_nh;
    vector<int> dp_h;

    int recursion(vector<int> &prices, int fee, bool holding, int idx) {
        if (idx == prices.size() - 1) {
            if(holding) {
                return prices[idx] - fee;
            } else {
                return 0;
            }
        }

        if (holding && dp_h[idx] != -1) {
            return dp_h[idx];
        } else if(!holding && dp_nh[idx] != -1) {
            return dp_nh[idx];
        }

        if (holding) {
            dp_h[idx] = max(prices[idx] - fee + recursion(prices, fee, false, idx + 1), // Sell
                                       recursion(prices, fee, true, idx + 1));   // Dont Sell
        } else {
            dp_nh[idx] = max(-prices[idx] + recursion(prices, fee, true, idx + 1), // Buy
                                   recursion(prices, fee, false, idx + 1));     // Dont Buy
        }

        if(holding) {
            return dp_h[idx];
        } else {
            return dp_nh[idx];
        }
    }

  public:
    int maxProfit(vector<int> &prices, int fee) {
        dp_h = vector<int>(prices.size(), -1);
        dp_nh = vector<int>(prices.size(), -1);
        return recursion(prices, fee, false, 0);
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> prices1 = {1, 3, 2, 8, 4, 9};
    int fee1 = 2;
    res = sol.maxProfit(prices1, fee1);
    cout << res << endl;
    assert(res == 8);

    vector<int> prices2 = {1, 3, 7, 5, 10, 3};
    int fee2 = 3;
    res = sol.maxProfit(prices2, fee2);
    cout << res << endl;
    assert(res == 6);

    return 0;
}