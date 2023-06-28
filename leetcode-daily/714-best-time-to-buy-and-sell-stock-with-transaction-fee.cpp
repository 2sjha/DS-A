/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

You are given an array prices where prices[i] is the price of a given stock on the ith day, and an
integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you
need to pay the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
before you buy again).


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

#include "./../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        
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