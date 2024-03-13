/*
https://leetcode.com/problems/longest-substring-without-repeating-characters/

Given a string s, find the length of the longest
substring without repeating characters.


Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.


Constraints:

    0 <= s.length <= 5 * 104
    s consists of English letters, digits, symbols and spaces.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() == 0 or s.length() == 1) {
            return s.length();
        }

        unordered_map<char, int> char_idx_map;
        int res = 0;
        int len = 0;
        int start = 0;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (char_idx_map.find(c) == char_idx_map.end() or char_idx_map[c] < start) {
                len++;
                res = max(res, len);
            } else {
                len = i - char_idx_map[c];
                start = char_idx_map[c] + 1;
            }
            char_idx_map[c] = i;
        }
        res = max(res, len);
        return res;
    }
};

int main() {
    // string s = "abba";
    string s = "pwwkew";
    // string s = "bbbb";
    // string s = "abcabcbdefgh";
    // string s = "tmmzuxt";
    // string s = "wobgrovw";
    // string s = "dvdf";

    Solution sol;
    int res = sol.lengthOfLongestSubstring(s);
    cout << res << endl;
    return 0;
}