/*
https://leetcode.com/problems/length-of-last-word

Given a string `s` consisting of words and spaces, return *the length of the **last** word in the
string.*

A **word** is a maximal substring consisting of non-space characters only.


**Example 1:**

**Input:** s = "Hello World"
**Output:** 5
**Explanation:** The last word is "World" with length 5.

**Example 2:**

**Input:** s = "   fly me   to   the moon  "
**Output:** 4
**Explanation:** The last word is "moon" with length 4.

**Example 3:**

**Input:** s = "luffy is still joyboy"
**Output:** 6
**Explanation:** The last word is "joyboy" with length 6.


**Constraints:**

* `1 <= s.length <= 10⁴`
* `s` consists of only English letters and spaces `' '`.
* There will be at least one word in `s`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int lengthOfLastWord(string s) {
        int prev = 0, len = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            if (s[i] == ' ') {
                if (len != 0) {
                    prev = len;
                }
                len = 0;
            } else {
                len++;
            }
        }
        if (len != 0)
            return len;
        else
            return prev;
    }
};

int main() {
    Solution sol;

    string s_1 = "Hello World";
    int expected_1 = 5;
    int output_1 = sol.lengthOfLastWord(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "   fly me   to   the moon  ";
    int expected_2 = 4;
    int output_2 = sol.lengthOfLastWord(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "luffy is still joyboy";
    int expected_3 = 6;
    int output_3 = sol.lengthOfLastWord(s_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}