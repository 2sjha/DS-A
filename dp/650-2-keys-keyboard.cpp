/*
https://leetcode.com/problems/2-keys-keyboard/

There is only one character 'A' on the screen of a notepad. You can perform one of two operations on
this notepad for each step:

    Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
    Paste: You can paste the characters which are copied last time.

Given an integer n, return the minimum number of operations to get the character 'A' exactly n times
on the screen.


Example 1:

Input: n = 3
Output: 3
Explanation: Initially, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Example 2:

Input: n = 1
Output: 0


Constraints:
    1 <= n <= 1000
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<vector<int>> dp;

    int minSteps(int n, int curr, int copy) {
        if (curr == n)
            return 0;
        if (curr > n)
            return 1e7;

        if (dp[curr][copy] != 1e7)
            return dp[curr][copy];

        if (copy == 0) {
            dp[curr][copy] = 1 + minSteps(n, curr, curr);
        } else if (copy == curr) {
            dp[curr][copy] = 1 + minSteps(n, curr + copy, copy);
        } else {
            dp[curr][copy] = 1 + min(minSteps(n, curr + copy, copy), minSteps(n, curr, curr));
        }

        return dp[curr][copy];
    }

  public:
    int minSteps(int n) {
        dp = vector<vector<int>>(n, vector<int>(n, 1e7));
        return minSteps(n, 1, 0);
    }
};

int main() {
    Solution sol;
    int res;

    res = sol.minSteps(3);
    assert(res == 3);

    res = sol.minSteps(1);
    assert(res == 0);

    return 0;
}