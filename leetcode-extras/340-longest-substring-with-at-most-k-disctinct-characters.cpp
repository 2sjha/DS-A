/*
https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/ [Premium Problem]

Given a string, find the longest substring that contains only two unique characters.
For example, given "abcbbbbcccbdddadacb", the longest substring that contains 2 unique character is
"bcbbbbcccb".
*/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution {
  public:
    string longestSubstringWithAtMostKDistinctCharacters(string s, int k) {
        if (s.length() == 0 || s.length() == 1) {
            return s;
        }

        int start = 0, end = 1;
        pair<int, int> res = {0, 1};
        unordered_map<char, int> map;
        map[s[start]] = 0;

        while (end < s.length()) {
            if (map.size() < k) {
                end++;
            } else if (map.find(s[end]) == map.end() && map.size() == k) {
                start = end - 1;
                map.clear();
                end++;
            }

            map[s[end]] = end;
            if (res.second - res.first + 1 < end - start + 1) {
                res.first = start;
                res.second = end;
            }
        }

        return s.substr(res.first, res.second);
    }
};

int main() {
    int k;
    string s;
    Solution sol;

    cout << "enter string" << endl;
    cin >> s;
    cout << "enter k (no. of distinct characters) " << endl;
    cin >> k;

    string res = sol.longestSubstringWithAtMostKDistinctCharacters(s, k);
    cout << res << endl;

    return 0;
}
