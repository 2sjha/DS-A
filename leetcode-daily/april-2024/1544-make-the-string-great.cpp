/*
https://leetcode.com/problems/make-the-string-great

Given a string `s` of lower and upper case English letters.

A good string is a string which doesn't have **two adjacent characters** `s[i]` and `s[i + 1]`
where:

* `0 <= i <= s.length - 2`
* `s[i]` is a lower-case letter and `s[i + 1]` is the same letter but in upper-case or
**vice-versa**.

To make the string good, you can choose **two adjacent** characters that make the string bad and
remove them. You can keep doing this until the string becomes good.

Return *the string* after making it good. The answer is guaranteed to be unique under the given
constraints.

**Notice** that an empty string is also good.


**Example 1:**

**Input:** s = "leEeetcode"
**Output:** "leetcode"
**Explanation:** In the first step, either you choose i = 1 or i = 2, both will result "leEeetcode"
to be reduced to "le etcode".

**Example 2:**

**Input:** s = "abBAcC"
**Output:** ""
**Explanation:** We have many possible scenarios, and all lead to the same answer. For example:
"abBAcC" --> "aAcC" --> "cC" --> ""
"abBAcC" --> "abBA" --> "aA" --> ""

**Example 3:**

**Input:** s = "s"
**Output:** "s"


**Constraints:**

* `1 <= s.length <= 100`
* `s` contains only lower and upper case English letters.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    string makeGood(string s) {
        while (true) {
            if (s == "")
                return s;

            bool bad = false;
            string res = "";
            int i = 0;
            while (i < s.length() - 1) {
                if (abs(s[i + 1] - s[i]) == abs('A' - 'a')) {
                    bad = true;
                    i += 2;
                } else {
                    res.push_back(s[i]);
                    i++;
                }
            }
            if (i == s.length() - 1)
                res.push_back(s[i]);

            if (!bad)
                return res;
            else
                s = res;
        }
    }
};

int main() {
    Solution sol;

    string s_1 = "leEeetcode";
    string expected_1 = "leetcode";
    string output_1 = sol.makeGood(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "abBAcC";
    string expected_2 = "";
    string output_2 = sol.makeGood(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "s";
    string expected_3 = "s";
    string output_3 = sol.makeGood(s_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}