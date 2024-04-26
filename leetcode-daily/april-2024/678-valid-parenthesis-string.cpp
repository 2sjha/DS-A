/*
https://leetcode.com/problems/valid-parenthesis-string

Given a string `s` containing only three types of characters: `'('`, `')'` and `'*'`, return `true`
*if* `s` *is
**valid***.

The following rules define a **valid** string:

* Any left parenthesis `'('` must have a corresponding right parenthesis `')'`.
* Any right parenthesis `')'` must have a corresponding left parenthesis `'('`.
* Left parenthesis `'('` must go before the corresponding right parenthesis `')'`.
* `'*'` could be treated as a single right parenthesis `')'` or a single left parenthesis `'('` or
an empty string `""`.


**Example 1:**

**Input:** s = "()"
**Output:** true

**Example 2:**

**Input:** s = "(*)"
**Output:** true

**Example 3:**

**Input:** s = "(*))"
**Output:** true


**Constraints:**

* `1 <= s.length <= 100`
* `s[i]` is `'('`, `')'` or `'*'`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    bool checkValidString(string s) {
        stack<pair<char, int>> left;
        queue<pair<char, int>> right;
        deque<pair<char, int>> astr;
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];
            if (c == '(') {
                left.push({c, i});
            } else if (c == ')') {
                if (left.empty()) {
                    right.push({c, i});
                } else {
                    left.pop();
                }
            } else {
                astr.push_back({c, i});
            }
        }

        while (!left.empty() && !astr.empty()) {
            if (left.top().second < astr.front().second) {
                left.pop();
                astr.pop_front();
            } else if (left.top().second < astr.back().second) {
                left.pop();
                astr.pop_back();
            } else {
                break;
            }
        }

        while (!right.empty() && !astr.empty()) {
            if (right.front().second > astr.back().second) {
                right.pop();
                astr.pop_back();
            } else if (right.front().second > astr.front().second) {
                right.pop();
                astr.pop_front();
            } else {
                break;
            }
        }

        return left.empty() && right.empty();
    }
};

int main() {
    Solution sol;

    string s_1 = "()";
    bool expected_1 = true;
    bool output_1 = sol.checkValidString(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = "(*)";
    bool expected_2 = true;
    bool output_2 = sol.checkValidString(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "(*))";
    bool expected_3 = true;
    bool output_3 = sol.checkValidString(s_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    string s_4 = "(((((*(()((((*((**(((()()*)()()()*((((**)())*)*)))))))(())(()))())((*()()(((()((("
                 ")*(())*(()**)()(())";
    bool expected_4 = true;
    bool output_4 = sol.checkValidString(s_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    string s_5 = "((((()(()()()*()(((((*)()*(**(())))))(())()())(((())())())))))))(((((())*)))()))("
                 "()((*()*(*)))(*)()";
    bool expected_5 = true;
    bool output_5 = sol.checkValidString(s_5);
    cout << output_5 << endl;
    assert(output_5 == expected_5);

    return 0;
}