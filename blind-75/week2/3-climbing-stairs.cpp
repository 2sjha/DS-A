/*
https://leetcode.com/problems/climbing-stairs/

You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways
can you climb to the top?

Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

 

Constraints:
    1 <= n <= 45
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> dp;
int climbStairs(int n) {
    if (dp[n] != -1) {
        return dp[n];
    }

    if (n <= 0) {
        dp[0] = 0;
        return dp[0];
    } else if (n == 1) {
        dp[1] = 1;
        return dp[1];
    } else if (n == 2) {
        dp[2] = 2;
        return dp[2];
    }

    dp[n] = climbStairs(n - 1) + climbStairs(n - 2);
    return dp[n];
}

int main() {
    int n;
    cin >> n;
    dp = vector<int>(n + 1, -1);
    int res = climbStairs(n);
    cout << res << endl;
    return 0;
}