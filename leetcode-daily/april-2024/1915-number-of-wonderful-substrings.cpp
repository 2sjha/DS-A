/*
https://leetcode.com/problems/number-of-wonderful-substrings

A **wonderful** string is a string where **at most one** letter appears an **odd** number of times.

* For example, `"ccjjc"` and `"abab"` are wonderful, but `"ab"` is not.

Given a string `word` that consists of the first ten lowercase English letters (`'a'` through
`'j'`), return *the
**number of wonderful non-empty substrings** in *`word`*. If the same substring appears multiple
times in *`word`*, then count **each occurrence** separately.*

A **substring** is a contiguous sequence of characters in a string.


**Example 1:**

**Input:** word = "aba"
**Output:** 4
**Explanation:** The four wonderful substrings are underlined below:
- "**a**ba" -> "a"
- "a**b**a" -> "b"
- "ab**a**" -> "a"
- "**aba**" -> "aba"

**Example 2:**

**Input:** word = "aabb"
**Output:** 9
**Explanation:** The nine wonderful substrings are underlined below:
- "**a**abb" -> "a"
- "**aa**bb" -> "aa"
- "**aab**b" -> "aab"
- "**aabb**" -> "aabb"
- "a**a**bb" -> "a"
- "a**abb**" -> "abb"
- "aa**b**b" -> "b"
- "aa**bb**" -> "bb"
- "aab**b**" -> "b"

**Example 3:**

**Input:** word = "he"
**Output:** 2
**Explanation:** The two wonderful substrings are underlined below:
- "he" -> "h"
- "h**e**" -> "e"


**Constraints:**

* `1 <= word.length <= 10⁵`
* `word` consists of lowercase English letters from `'a'` to `'j'`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int getBitmask(vector<bool> &freq) {
        int num = 0;
        for (int i = 0; i < 10; ++i) {
            if (freq[9 - i]) {
                num += pow(2, i);
            }
        }

        return num;
    }

  public:
    long long wonderfulSubstrings(string word) {
        int n = word.length();
        long long res = 0;
        vector<bool> freq(10, false);  // false means even frequency, bool array because odd-even
                                       // frequencies are like booleans
        vector<int> bitmasks(1024, 0); // Since only 10 bit bitmasks can be created from 10 chars,
                                       // we use a 2^10 size array as a hashmap
        bitmasks[0] = 1;

        for (int i = 0; i < n; ++i) {
            freq[word[i] - 'a'] = !freq[word[i] - 'a'];
            int curr_bitmask = getBitmask(freq);

            // Like the subarrays with sum = goal problem, we're trying to find prefix subarrays
            // with sum = curr_sum - goal which can be chopped off
            // to count valid subarrays with sum = goal

            // Consider if 'a' has odd frequency, then were trying to chop off substrings where
            // every other character has same bool frequency as the current prefix string
            // (if other character has odd freq, then some prefix substring with this odd freq of
            // this character must be chopped off to have even freq in resulting substring,
            // odd - odd = even & even - even = even) but 'a' has even frequency,
            // so the resulting substring has only one char with odd freq, i.e 'a',
            // and vice versa for even frequency.

            // Now we check this for all characters 'a' through 'j'.
            for (int j = 0; j < 10; ++j) {
                // Try to find bitmasks(prefix freq arrays) which differ by 1 bit
                freq[j] = !freq[j];
                int one_diff_bitmask = getBitmask(freq);
                if (bitmasks[one_diff_bitmask] != 0)
                    res += bitmasks[one_diff_bitmask];

                freq[j] = !freq[j];
            }

            // To count the subarrays where no character has odd frequency,
            // then we try to chop off subarrays with the same bool freq
            if (bitmasks[curr_bitmask] != 0)
                res += bitmasks[curr_bitmask];

            bitmasks[curr_bitmask]++;
        }

        return res;
    }
};

int main() {
    Solution sol;

    string word_1 = "aba";
    long long expected_1 = 4;
    long long output_1 = sol.wonderfulSubstrings(word_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string word_2 = "aabb";
    long long expected_2 = 9;
    long long output_2 = sol.wonderfulSubstrings(word_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string word_3 = "he";
    long long expected_3 = 2;
    long long output_3 = sol.wonderfulSubstrings(word_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}