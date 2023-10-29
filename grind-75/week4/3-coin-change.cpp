/*
https://leetcode.com/problems/coin-change/

You are given an integer array coins representing coins of different denominations and an integer
amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money
cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.


Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3
Output: -1

Example 3:

Input: coins = [1], amount = 0
Output: 0


Constraints:

    1 <= coins.length <= 12
    1 <= coins[i] <= 231 - 1
    0 <= amount <= 10^4
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int coinChangeDP(vector<int> &coins, int amount, int idx) {
        if (amount < 0 or idx < 0) {
            return 10001;
        }

        if (amount == 0) {
            dp[amount][idx] = 0;
            return 0;
        }

        int coin = coins[idx];
        if (idx == 0) {
            if (amount % coin == 0) {
                dp[amount][idx] = amount / coin;
            } else {
                dp[amount][idx] = 10001;
            }
            return dp[amount][idx];
        }

        if (dp[amount][idx] != -1) {
            return dp[amount][idx];
        }

        if (amount >= coin) {
            dp[amount][idx] = min(1 + coinChangeDP(coins, amount - coin, idx),
                                  coinChangeDP(coins, amount, idx - 1));
        } else {
            dp[amount][idx] = min(10001, coinChangeDP(coins, amount, idx - 1));
        }
        return dp[amount][idx];
    }

  public:
    vector<vector<int>> dp;

    int coinChange(vector<int> &coins, int amount) {
        dp.clear();
        for (int i = 0; i < amount + 1; ++i) {
            vector<int> empty = vector<int>(12, -1);
            dp.push_back(empty);
        }

        sort(coins.begin(), coins.end());

        int res = coinChangeDP(coins, amount, coins.size() - 1);

        if (res >= 10001) {
            return -1;
        }
        return res;
    }
};

int main() {
    vector<int> amount = {11, 3, 0, 6249, 9864};
    vector<vector<int>> coins = {{1, 2, 5},
                                 {2},
                                 {1},
                                 {186, 419, 83, 408},
                                 {411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422}};

    Solution sol;
    for (int i = 0; i < 5; ++i) {
        cout << sol.coinChange(coins[i], amount[i]) << endl;
    }
    return 0;
}