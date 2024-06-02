/*
https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency

Given a string `s`, you need to partition it into one or more **balanced** substrings. For example,
if `s == "ababcc"` then `("abab", "c", "c")`, `("ab", "abc", "c")`, and `("ababcc")` are all valid
partitions, but `("a", **"bab"**, "cc")`, `(**"aba"**, "bc", "c")`, and `("ab", **"abcc"**)` are
not. The unbalanced substrings are bolded.

Return the **minimum** number of substrings that you can partition `s` into.

**Note:** A **balanced** string is a string where each character in the string occurs the same
number of times.


**Example 1:**

**Input:** s = "fabccddg"

**Output:** 3

**Explanation:**

We can partition the string `s` into 3 substrings in one of the following ways: `("fab, "ccdd",
"g")`, or `("fabc", "cd", "dg")`.

**Example 2:**

**Input:** s = "abababaccddb"

**Output:** 2

**Explanation:**

We can partition the string `s` into 2 substrings like so: `("abab", "abaccddb")`.


**Constraints:**

* `1 <= s.length <= 1000`
* `s` consists only of English lowercase letters.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Had to look at the hints for solution. Solved it, but didn't get accepted because of Leetcode
// timing BS(running as testcase, but failed when submitting).
// Then had to look up multiple solutions for efficiently checking valid substring

class Solution {
  public:
    int minimumSubstringsInPartition(string s) {
        int n = s.length(), substr_valid = 1, first_freq = -1, max_freq = 0;
        vector<int> dp(n + 1, n);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            int freq[26] = {0};
            max_freq = 0;

            // Intuition: If we know the minimum no. of equal char. freq. partitions until idx 0 <=
            // j < i then we can use those to calculate the same for i, just go through 0 to i-1 and
            // check if substring j+1 to i is valid or not.
            // If it is valid, then take the minimum of all such 1 + dp[j].
            for (int j = i - 1; j >= 0; --j) {
                // Here is the real kicker, if you go through j+1 to i everytime to check substring
                // valid, then that is again an O(n) operation which overall makes it O(n^3).

                // So just go backwards instead and keep track of max_freq and check the frequency
                // array so far if substring made so far is valid or not. Since all characters must
                // be equal freq, then all characters in this substring so far must be of this
                // max_freq.
                freq[s[j] - 'a']++;
                max_freq = max(max_freq, freq[s[j] - 'a']);

                substr_valid = 1;
                for (int i = 0; i < 26; ++i) {
                    if (freq[i] != 0 && freq[i] != max_freq)
                        substr_valid = 0;
                }

                // If substring from j+1 to i is valid, then minimum no. of equal char freq.
                // partitions until j is counted in dp[j], and add 1 for this substring
                if (substr_valid) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;

    string s_1 = "fabccddg";
    int expected_1 = 3;
    int output_1 = sol.minimumSubstringsInPartition(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "abababaccddb";
    int expected_2 = 2;
    int output_2 = sol.minimumSubstringsInPartition(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}