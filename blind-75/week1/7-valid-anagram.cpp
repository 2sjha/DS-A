/*
https://leetcode.com/problems/valid-anagram

Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true

Example 2:

Input: s = "rat", t = "car"
Output: false

Constraints:

    1 <= s.length, t.length <= 5 * 104
    s and t consist of lowercase English letters.

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such
a case?
*/

#include "bits/stdc++.h"
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
  public:
    bool isAnagram(string s, string t) {
        bool res = true;
        int char_count_s[26];
        int char_count_t[26];

        for (int i = 0; i < 26; i++) {
            char_count_s[i] = 0;
            char_count_t[i] = 0;
        }

        for (int i = 0; i < s.length(); i++) {
            char k = s[i];
            char_count_s[(int)k - 97]++;
        }

        for (int i = 0; i < t.length(); i++) {
            char k = t[i];
            char_count_t[(int)k - 97]++;
        }

        for (int i = 0; i < 26; i++) {
            if (char_count_s[i] != char_count_t[i]) {
                res = false;
                break;
            }
        }

        return res;
    }
};

int main() {
    string s, t;
    Solution sol;
    cout << "Enter string s t" << endl;
    cin >> s >> t;

    bool res = sol.isAnagram(s, t);
    cout << res;
    return 0;
}