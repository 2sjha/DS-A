/*
https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses

Given a string s of `'('` , `')'` and lowercase English characters.

Your task is to remove the minimum number of parentheses ( `'('` or `')'`, in any positions ) so
that the resulting *parentheses string* is valid and return **any** valid string.

Formally, a *parentheses string* is valid if and only if:

* It is the empty string, contains only lowercase characters, or
* It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid strings, or
* It can be written as `(A)`, where `A` is a valid string.


**Example 1:**

**Input:** s = "lee(t(c)o)de)"
**Output:** "lee(t(c)o)de"
**Explanation:** "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

**Example 2:**

**Input:** s = "a)b(c)d"
**Output:** "ab(c)d"

**Example 3:**

**Input:** s = "))(("
**Output:** ""
**Explanation:** An empty string is also valid.


**Constraints:**

* `1 <= s.length <= 10⁵`
* `s[i]` is either`'('` , `')'`, or lowercase English letter`.`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    string minRemoveToMakeValid(string s) {
        // Process string s, push indices to be removed
        unordered_set<int> remove;
        stack<int> st;
        char c;
        for (int i = 0; i < s.length(); ++i) {
            c = s[i];
            if (c == '(') {
                st.push(i);
            } else if (c == ')') {
                if (st.empty()) {
                    remove.insert(i);
                } else {
                    st.pop();
                }
            }
        }

        while (!st.empty()) {
            remove.insert(st.top());
            st.pop();
        }

        string res = "";
        for (int i = 0; i < s.length(); ++i) {
            if (!remove.count(i))
                res.push_back(s[i]);
        }
        return res;
    }
};

int main() {
    Solution sol;

    string s_1 = "lee(t(c)o)de)";
    string expected_1 = "lee(t(c)o)de";
    string output_1 = sol.minRemoveToMakeValid(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "a)b(c)d";
    string expected_2 = "ab(c)d";
    string output_2 = sol.minRemoveToMakeValid(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "))((";
    string expected_3 = "";
    string output_3 = sol.minRemoveToMakeValid(s_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}