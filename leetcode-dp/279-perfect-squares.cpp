/*
https://leetcode.com/problems/perfect-squares/

Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product
of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are
not.


Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.


Constraints:
    1 <= n <= 10^4
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool perfectSquare(int n) {
        float k = sqrt(n);
        int j = sqrt(n);
        return j == k;
    }

  public:
    int numSquares(int n) {
        if (n == 1)
            return 1;
        if (perfectSquare(n))
            return 1;

        vector<int> dp(n + 1, 10001);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (perfectSquare(i)) {
                dp[i] = 1;
            } else {
                int j = 1, k = 1;
                while (k <= i) {
                    dp[i] = min(dp[i], dp[i - k] + 1);
                    j++;
                    k = j * j;
                }
            }
        }

        printArray(dp);
        return dp[n];
    }
};

int main() {
    Solution sol;
    int res;

    int n = 9;
    res = sol.numSquares(n);
    cout << res << endl;
    assert(res == 1);

    n = 12;
    res = sol.numSquares(n);
    cout << res << endl;
    assert(res == 3);

    n = 13;
    res = sol.numSquares(n);
    cout << res << endl;
    assert(res == 2);

    return 0;
}