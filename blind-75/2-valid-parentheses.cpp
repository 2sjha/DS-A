/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the
input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.



Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "()[]{}"
Output: true

Example 3:

Input: s = "(]"
Output: false



Constraints:

    1 <= s.length <= 104
    s consists of parentheses only '()[]{}'.
*/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution {
  public:
    bool isValid(string s) {
        stack<char> st;

        for (int i = 0; i < s.length(); i++) {

            if (isClosing(s[i])) {
                char open = findOpenForClose(s[i]);
                if (!st.empty() && open == st.top()) {
                    st.pop();
                } else {
                    st.push(s[i]);
                }
            } else {
                st.push(s[i]);
            }
        }

        if (st.empty()) {
            return true;
        } else {
            return false;
        }
    }

  private:
    bool isClosing(char parenthesis) {
        return (parenthesis == '}' || parenthesis == ']' || parenthesis == ')');
    }

    char findOpenForClose(char parenthesis) {
        switch (parenthesis) {
        case ')':
            return '(';
        case '}':
            return '{';
        case ']':
            return '[';
        default:
            return 'z';
        }
    }
};

int main() {
    string s;
    Solution sol;

    cout << "enter string with parentheses" << endl;
    cin >> s;

    bool res = sol.isValid(s);
    cout << res << endl;

    return 0;
}
