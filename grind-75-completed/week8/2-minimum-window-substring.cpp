/*
https://leetcode.com/problems/minimum-window-substring

Given two strings `s` and `t` of lengths `m` and `n` respectively, return *the **minimum window***
***substring**** of
*`s`* such that every character in *`t`* (**including duplicates**) is included in the window*. If
there is no such substring, return *the empty string *`""`.

The testcases will be generated such that the answer is **unique**.


**Example 1:**

**Input:** s = "ADOBECODEBANC", t = "ABC"
**Output:** "BANC"
**Explanation:** The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

**Example 2:**

**Input:** s = "a", t = "a"
**Output:** "a"
**Explanation:** The entire string s is the minimum window.

**Example 3:**

**Input:** s = "a", t = "aa"
**Output:** ""
**Explanation:** Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.


**Constraints:**

* `m == s.length`
* `n == t.length`
* `1 <= m, n <= 10⁵`
* `s` and `t` consist of uppercase and lowercase English letters.


**Follow up:** Could you find an algorithm that runs in `O(m + n)` time?
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void clearFreq(unordered_map<char, int> &freq) {
        for (int i = 0; i < 26; ++i) {
            freq[i + 'a'] = 0;
            freq[i + 'A'] = 0;
        }
    }

    bool match(unordered_map<char, int> &sfreq, unordered_map<char, int> &tfreq) {
        for (int i = 0; i < 26; ++i) {
            if (tfreq[i + 'a'] > sfreq[i + 'a']) {
                return false;
            }
            if (tfreq[i + 'A'] > sfreq[i + 'A']) {
                return false;
            }
        }

        return true;
    }

    string checkWindowSubstring(string s, unordered_map<char, int> &sfreq,
                                unordered_map<char, int> &tfreq, int winSz) {
        int m = s.length();
        if (winSz > m)
            return "";

        clearFreq(sfreq);
        for (int i = 0; i < winSz; ++i) {
            sfreq[s[i]]++;
        }
        if (match(sfreq, tfreq)) {
            return s.substr(0, winSz);
        }

        if (m < 2)
            return "";

        for (int i = 1; i <= m - winSz; ++i) {
            sfreq[s[i - 1]]--;
            sfreq[s[i + winSz - 1]]++;
            if (match(sfreq, tfreq)) {
                return s.substr(i, winSz);
            }
        }

        return "";
    }

  public:
    string minWindow(string s, string t) {
        int m = s.length();
        int n = t.length();

        if (n > m)
            return "";

        unordered_map<char, int> tfreq, sfreq;
        clearFreq(tfreq);
        clearFreq(sfreq);

        for (char c : t) {
            tfreq[c]++;
        }

        if (n == m) {
            for (char c : s) {
                sfreq[c]++;
            }
            if (match(sfreq, tfreq))
                return s;
            else
                return "";
        }

        int low = n;
        int high = m;
        int mid;
        string res = "";
        string midstr, midstr_1;
        while (low < high) {
            mid = low + (high - low) / 2;
            midstr = checkWindowSubstring(s, sfreq, tfreq, mid);
            midstr_1 = checkWindowSubstring(s, sfreq, tfreq, mid + 1);

            if (midstr != "" && midstr_1 != "") {
                high = mid;
                res = midstr;
            } else if (midstr == "" && midstr_1 == "") {
                low = mid + 1;
            } else {
                if (midstr != "")
                    return midstr;
                else
                    return midstr_1;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    string s_1 = "ADOBECODEBANC";
    string t_1 = "ABC";
    string expected_1 = "BANC";
    string output_1 = sol.minWindow(s_1, t_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "a";
    string t_2 = "a";
    string expected_2 = "a";
    string output_2 = sol.minWindow(s_2, t_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "a";
    string t_3 = "aa";
    string expected_3 = "";
    string output_3 = sol.minWindow(s_3, t_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    string s_4 = "ab";
    string t_4 = "a";
    string expected_4 = "";
    string output_4 = sol.minWindow(s_4, t_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    return 0;
}