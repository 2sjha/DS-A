/*
https://leetcode.com/problems/basic-calculator

Given a string `s` representing a valid expression, implement a basic calculator to evaluate it, and
return *the result of the evaluation*.

**Note:** You are **not** allowed to use any built-in function which evaluates strings as
mathematical expressions, such as `eval()`.


**Example 1:**

**Input:** s = "1 + 1"
**Output:** 2

**Example 2:**

**Input:** s = " 2-1 + 2 "
**Output:** 3

**Example 3:**

**Input:** s = "(1+(4+5+2)-3)+(6+8)"
**Output:** 23


**Constraints:**

* `1 <= s.length <= 3 * 10⁵`
* `s` consists of digits, `'+'`, `'-'`, `'('`, `')'`, and `' '`.
* `s` represents a valid expression.
* `'+'` is **not** used as a unary operation (i.e., `"+1"` and `"+(2 + 3)"` is invalid).
* `'-'` could be used as a unary operation (i.e., `"-1"` and `"-(2 + 3)"` is valid).
* There will be no two consecutive operators in the input.
* Every number and running calculation will fit in a signed 32-bit integer.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    pair<int, int> getNum(vector<char> &v, int start) {
        int res = 0;
        int end = start;

        while (end < v.size() && v[end] >= '0' && v[end] <= '9') {
            res = 10 * res + (v[end] - '0');
            end++;
        }
        return {res, end};
    }

    int evalSimpleExp(vector<char> &v, int start, int end) {
        int res = 0;

        int i = start;
        while (i <= end) {
            char c = v[i];

            if (c == '+' || c == '(' || c == ')') {
                i++;
            } else if (c == '-') {
                pair<int, int> num = getNum(v, ++i);
                res += -1 * num.first;
                i = num.second;
            } else {
                pair<int, int> num = getNum(v, i);
                res += num.first;
                i = num.second;
            }
        }

        if (start > 0 && res < 0) {
            if (v[start - 1] == '+') {
                v.pop_back();
            } else if (v[start - 1] == '-') {
                res = -1 * res;
                v[start - 1] = '+';
            }
        }

        for (int i = start; i <= end; ++i)
            v.pop_back();

        for (char c : to_string(res)) {
            v.push_back(c);
        }

        return res;
    }

  public:
    int calculate(string s) {
        int n = s.length();
        vector<int> brackets;
        vector<char> v;

        for (int i = 0; i < n; ++i) {
            char c = s[i];

            if (c != ' ') {
                v.push_back(c);
            }

            if (c == '(') {
                brackets.push_back(v.size() - 1);
            } else if (c == ')') {
                if (brackets.back() > v.size()) {
                    evalSimpleExp(v, brackets.back(), min(i, (int)v.size() - 1));
                } else {
                    evalSimpleExp(v, brackets.back(), min(i, (int)v.size() - 1));
                }
                brackets.pop_back();
            }
        }

        return evalSimpleExp(v, 0, v.size() - 1);
    }
};

int main() {
    Solution sol;

    string s_1 = "1 + 1";
    int expected_1 = 2;
    int output_1 = sol.calculate(s_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string s_2 = " 2-1 + 2 ";
    int expected_2 = 3;
    int output_2 = sol.calculate(s_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string s_3 = "(1+(4+5+2)-3)+(6+8)";
    int expected_3 = 23;
    int output_3 = sol.calculate(s_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    string s_4 = "0";
    int expected_4 = 0;
    int output_4 = sol.calculate(s_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    string s_5 = "(1-(-4-5+2)-3)+(6+8)";
    int expected_5 = 19;
    int output_5 = sol.calculate(s_5);
    cout << output_5 << endl;
    assert(output_5 == expected_5);

    string s_6 = "(1+(-4-5+2)-3)+(6+8)";
    int expected_6 = 5;
    int output_6 = sol.calculate(s_6);
    cout << output_6 << endl;
    assert(output_6 == expected_6);

    return 0;
}