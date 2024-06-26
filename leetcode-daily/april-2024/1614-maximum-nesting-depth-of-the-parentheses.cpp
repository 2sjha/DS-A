/*
https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses

A string is a **valid parentheses string** (denoted **VPS**) if it meets one of the following:

* It is an empty string `""`, or a single character not equal to `"("` or `")"`,
* It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are **VPS**'s, or
* It can be written as `(A)`, where `A` is a **VPS**.

We can similarly define the **nesting depth** `depth(S)` of any VPS `S` as follows:

* `depth("") = 0`
* `depth(C) = 0`, where `C` is a string with a single character not equal to `"("` or `")"`.
* `depth(A + B) = max(depth(A), depth(B))`, where `A` and `B` are **VPS**'s.
* `depth("(" + A + ")") = 1 + depth(A)`, where `A` is a **VPS**.

For example, `""`, `"()()"`, and `"()(()())"` are **VPS**'s (with nesting depths 0, 1, and 2), and
`")("` and `"(()"` are not **VPS**'s.

Given a **VPS** represented as string `s`, return *the **nesting depth** of *`s`.


**Example 1:**

**Input:** s = "(1+(2*3)+((8)/4))+1"
**Output:** 3
**Explanation:** Digit 8 is inside of 3 nested parentheses in the string.

**Example 2:**

**Input:** s = "(1)+((2))+(((3)))"
**Output:** 3


**Constraints:**

* `1 <= s.length <= 100`
* `s` consists of digits `0-9` and characters `'+'`, `'-'`, `'*'`, `'/'`, `'('`, and `')'`.
* It is guaranteed that parentheses expression `s` is a **VPS**.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int maxDepth(string s) {
        int nest = 0;
        int res = 0;
        int i = 0, n = s.length();
        while (i < n) {
            if (s[i] == '(') {
                nest++;
                res = max(res, nest);
            } else if (s[i] == ')') {
                nest--;
            }
            i++;
        }

        return res;
    }
};

int main() {
    Solution sol;

    string s_1 = "(1+(2*3)+((8)/4))+1";
    int expected_1 = 3;
    int output_1 = sol.maxDepth(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "(1)+((2))+(((3)))";
    int expected_2 = 3;
    int output_2 = sol.maxDepth(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}