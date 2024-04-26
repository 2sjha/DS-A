/*
https://leetcode.com/problems/longest-ideal-subsequence

You are given a string `s` consisting of lowercase letters and an integer `k`. We call a string `t`
**ideal** if the following conditions are satisfied:

* `t` is a **subsequence** of the string `s`.
* The absolute difference in the alphabet order of every two **adjacent** letters in `t` is less
than or equal to `k`.

Return *the length of the **longest** ideal string*.

A **subsequence** is a string that can be derived from another string by deleting some or no
characters without changing the order of the remaining characters.

**Note** that the alphabet order is not cyclic. For example, the absolute difference in the alphabet
order of `'a'` and
`'z'` is `25`, not `1`.


**Example 1:**

**Input:** s = "acfgbd", k = 2
**Output:** 4
**Explanation:** The longest ideal string is "acbd". The length of this string is 4, so 4 is
returned. Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet
order.

**Example 2:**

**Input:** s = "abcd", k = 3
**Output:** 4
**Explanation:** The longest ideal string is "abcd". The length of this string is 4, so 4 is
returned.


**Constraints:**

* `1 <= s.length <= 10⁵`
* `0 <= k <= 25`
* `s` consists of lowercase English letters.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<vector<int>> dp;

    int getDpIdx(char last_char) {
        if (last_char == '.')
            return 0;
        else
            return last_char - 'a' + 1;
    }

    int maxLenIdealSubsequence(string &s, int k, int idx, char last_char) {
        if (idx >= s.length())
            return 0;

        int last_char_idx = getDpIdx(last_char);
        if (dp[idx][last_char_idx] != 0) {
            return dp[idx][last_char_idx];
        }

        if (last_char != '.' && abs(last_char - s[idx]) > k) {
            dp[idx][last_char_idx] = maxLenIdealSubsequence(s, k, idx + 1, last_char);
        } else {
            dp[idx][last_char_idx] = max(maxLenIdealSubsequence(s, k, idx + 1, last_char),
                                         1 + maxLenIdealSubsequence(s, k, idx + 1, s[idx]));
        }
        return dp[idx][last_char_idx];
    }

  public:
    int longestIdealString(string s, int k) {
        dp = vector<vector<int>>(s.length(), vector<int>(27, 0));
        return maxLenIdealSubsequence(s, k, 0, '.');
    }
};

int main() {
    Solution sol;

    string s_1 = "acfgbd";
    int k_1 = 2;
    int expected_1 = 4;
    int output_1 = sol.longestIdealString(s_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "abcd";
    int k_2 = 3;
    int expected_2 = 4;
    int output_2 = sol.longestIdealString(s_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}