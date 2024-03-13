/*
https://leetcode.com/problems/find-all-anagrams-in-a-string/

Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may
return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.


Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".


Constraints:

    1 <= s.length, p.length <= 3 * 10^4
    s and p consist of lowercase English letters.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool anagram(vector<int> &pcharsfreq, vector<int> &scharsfreq) {
        for (int i = 0; i < 26; ++i) {
            if (pcharsfreq[i] != scharsfreq[i]) {
                return false;
            }
        }
        return true;
    }

  public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int plen = p.length();
        int n = s.length();

        if (n < plen) {
            return res;
        }

        int i = 0;
        vector<int> pcharsfreq = vector<int>(26, 0);
        vector<int> scharsfreq = vector<int>(26, 0);
        while (i < plen) {
            pcharsfreq[p[i] - 'a']++;
            scharsfreq[s[i] - 'a']++;
            i++;
        }

        i = 0;
        while (i < n - plen) {
            if (anagram(pcharsfreq, scharsfreq)) {
                res.push_back(i);
            }
            scharsfreq[s[i] - 'a']--;
            scharsfreq[s[i + plen] - 'a']++;
            i++;
        }
        if (anagram(pcharsfreq, scharsfreq)) {
            res.push_back(i);
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<int> res;

    string s1 = "cbaebabacd";
    string p1 = "abc";
    res = sol.findAnagrams(s1, p1);
    printArray(res);

    string s2 = "abab";
    string p2 = "ab";
    res = sol.findAnagrams(s2, p2);
    printArray(res);

    return 0;
}