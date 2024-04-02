/*
https://leetcode.com/problems/isomorphic-strings

Given two strings `s` and `t`, *determine if they are isomorphic*.

Two strings `s` and `t` are isomorphic if the characters in `s` can be replaced to get `t`.

All occurrences of a character must be replaced with another character while preserving the order of
characters. No two characters may map to the same character, but a character may map to itself.


**Example 1:**

**Input:** s = "egg", t = "add"
**Output:** true

**Example 2:**

**Input:** s = "foo", t = "bar"
**Output:** false

**Example 3:**

**Input:** s = "paper", t = "title"
**Output:** true


**Constraints:**

* `1 <= s.length <= 5 * 10⁴`
* `t.length == s.length`
* `s` and `t` consist of any valid ascii character.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    bool isIsomorphic(string s, string t) {
        int n = s.length();
        if (n != t.length())
            return false;

        vector<char> s_t_mapping(128, '\0');
        vector<bool> t_mapped(128, false);
        vector<bool> s_mapped(128, false);
        string s_new = s;
        for (int i = 0; i < n; ++i) {
            if (s_t_mapping[s[i]] == '\0') {
                if (t_mapped[t[i]])
                    return false;
                if (s_mapped[s[i]])
                    return false;
                s_t_mapping[s[i]] = t[i];
                t_mapped[t[i]] = true;
                s_mapped[s[i]] = true;
            }
            s_new[i] = s_t_mapping[s[i]];
        }
        return s_new == t;
    }
};

int main() {
    Solution sol;

    string s_1 = "egg";
    string t_1 = "add";
    bool expected_1 = true;
    bool output_1 = sol.isIsomorphic(s_1, t_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "foo";
    string t_2 = "bar";
    bool expected_2 = false;
    bool output_2 = sol.isIsomorphic(s_2, t_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "paper";
    string t_3 = "title";
    bool expected_3 = true;
    bool output_3 = sol.isIsomorphic(s_3, t_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}