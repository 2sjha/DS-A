/*
https://leetcode.com/problems/minimum-deletions-to-make-string-k-special

You are given a string `word` and an integer `k`.

We consider `word` to be **k-special** if `|freq(word[i]) - freq(word[j])| <= k` for all indices `i`
and `j` in the string.

Here, `freq(x)` denotes the frequency of the character `x` in `word`, and `|y|` denotes the absolute
value of `y`.

Return *the **minimum** number of characters you need to delete to make* `word` ***k-special***.


**Example 1:**

**Input: **word = "aabcaba", k = 0

**Output: **3

**Explanation:** We can make `word` `0`-special by deleting `2` occurrences of `"a"` and `1`
occurrence of `"c"`. Therefore, `word` becomes equal to `"baba"` where `freq('a') == freq('b') ==
2`.

**Example 2:**

**Input: **word = "dabdcbdcdcd", k = 2

**Output: **2

**Explanation:** We can make `word` `2`-special by deleting `1` occurrence of `"a"` and `1`
occurrence of `"d"`. Therefore, `word` becomes equal to "bdcbdcdcd" where `freq('b') == 2`,
`freq('c') == 3`, and `freq('d') == 4`.

**Example 3:**

**Input: **word = "aaabaaa", k = 2

**Output: **1

**Explanation:** We can make `word` `2`-special by deleting `1` occurrence of `"b"`. Therefore,
`word` becomes equal to
`"aaaaaa"` where each letter's frequency is now uniformly `6`.


**Constraints:**

* `1 <= word.length <= 10⁵`
* `0 <= k <= 10⁵`
* `word` consists only of lowercase English letters.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int minDeletions(vector<int> &freq, int k) {
        // this freq only has non-zero elements and its is sorted
        int n = freq.size(), res = INT_MAX;
        // If we were to bring all frequencies to the same frequency such that
        // no element in the array differ by more than k

        for (int i = 0; i < n; ++i) {
            // Try all the frequencies in the array
            int curr_freq = freq[i];
            int curr_freq_deletion = 0;
            // if we bring all elements in the array close to this current frequency
            // count the total deletions in the array
            for (int j = 0; j < n; ++j) {
                // if this element differs by more than k
                // then we delete the difference from this element
                if (freq[j] - curr_freq > k) {
                    curr_freq_deletion += freq[j] - curr_freq - k;
                } else if (freq[j] - curr_freq < 0) {
                    // but if difference is negative then we cant add more characters
                    // so we make this frequency = zero
                    curr_freq_deletion += freq[j];
                }
            }
            // choose the minimum deletions among all the attempts
            res = min(res, curr_freq_deletion);
        }

        return res != INT_MAX ? res : 0;
    }

  public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }

        vector<int> newfreq;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > 0) {
                newfreq.push_back(freq[i]);
            }
        }

        if (newfreq.size() == 1)
            return 0;

        sort(newfreq.begin(), newfreq.end());
        return minDeletions(newfreq, k);
    }
};

int main() {
    Solution sol;

    string word_1 = "aabcaba";
    int k_1 = 0;
    int expected_1 = 3;
    int output_1 = sol.minimumDeletions(word_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string word_2 = "dabdcbdcdcd";
    int k_2 = 2;
    int expected_2 = 2;
    int output_2 = sol.minimumDeletions(word_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string word_3 = "aaabaaa";
    int k_3 = 2;
    int expected_3 = 1;
    int output_3 = sol.minimumDeletions(word_3, k_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    string word_4 = "vvnowvov";
    int k_4 = 1;
    int expected_4 = 1;
    int output_4 = sol.minimumDeletions(word_4, k_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    return 0;
}