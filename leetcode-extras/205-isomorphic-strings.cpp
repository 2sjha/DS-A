/*
Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of
characters. No two characters may map to the same character, but a character may map to itself.


Example 1:

Input: s = "egg", t = "add"
Output: true

Example 2:

Input: s = "foo", t = "bar"
Output: false

Example 3:

Input: s = "paper", t = "title"
Output: true


Constraints:

    1 <= s.length <= 5 * 10^4
    t.length == s.length
    s and t consist of any valid ascii character.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    bool isIsomorphic(string s, string t) {
        int n = s.length();
        int flips = 0;
        map<char, char> st_mp;

        for (int i = 0; i < n; ++i) {
            if (!st_mp.count(s[i])) {
                st_mp[s[i]] = t[i];
                flips++;
            }
        }

        for (auto iter1 = st_mp.begin(); iter1 != st_mp.end(); iter1++) {
            auto iter2 = iter1;
            iter2++;
            for (; iter2 != st_mp.end(); iter2++) {
                if (iter1->second == iter2->second) {
                    return false;
                }
            }
        }

        string s_new = s;
        for (int i = 0; i < n; ++i) {
            if (st_mp.count(s_new[i])) {
                s_new[i] = st_mp[s_new[i]];
            }
        }

        return s_new == t;
    }
};

int main() {
    Solution sol;
    bool res;

    string s1 = "egg";
    string t1 = "add";
    res = sol.isIsomorphic(s1, t1);
    cout << res << endl;
    assert(res == 1);

    string s2 = "foo";
    string t2 = "bar";
    res = sol.isIsomorphic(s2, t2);
    cout << res << endl;
    assert(res == 0);

    string s3 = "paper";
    string t3 = "title";
    res = sol.isIsomorphic(s3, t3);
    cout << res << endl;
    assert(res == 1);

    return 0;
}