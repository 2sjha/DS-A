/*
https://leetcode.com/problems/flip-string-to-monotone-increasing/

A binary string is monotone increasing if it consists of some number of 0's (possibly none),
followed by some number of 1's (also possibly none).

You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.

Return the minimum number of flips to make s monotone increasing.


Example 1:

Input: s = "00110"
Output: 1
Explanation: We flip the last digit to get 00111.

Example 2:

Input: s = "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.

Example 3:

Input: s = "00011000"
Output: 2
Explanation: We flip to get 00000000.


Constraints:

    1 <= s.length <= 105
    s[i] is either '0' or '1'.
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int minFlipsMonoIncr(string s) {
        int n = s.length();
        vector<int> dp(n + 1, 0);
        int cntOnes = 0;

        for (int i = 1; i <= n; ++i) {
            // If s[i] == 1, then its valid, but needs to be counted
            if (s[i - 1] == '1') {
                cntOnes++;
                dp[i] = dp[i - 1];
            } else {
                // because if s[i] == 0, then if we dont flip this char, then all the ones to left
                // (cntOnes) need to be flipped. Or we flip this.
                dp[i] = min(dp[i - 1] + 1, cntOnes);
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    int res;

    string s1 = "00110";
    res = sol.minFlipsMonoIncr(s1);
    cout << res << endl;
    assert(res == 1);

    string s2 = "010110";
    res = sol.minFlipsMonoIncr(s2);
    cout << res << endl;
    assert(res == 2);

    string s4 = "0001100";
    res = sol.minFlipsMonoIncr(s4);
    cout << res << endl;
    assert(res == 2);

    string s3 = "00011000";
    res = sol.minFlipsMonoIncr(s3);
    cout << res << endl;
    assert(res == 2);

    return 0;
}