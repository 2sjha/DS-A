/*
https://leetcode.com/problems/string-to-integer-atoi/

Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar
to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:

    Read in and ignore any leading whitespace.
    Check if the next character (if not already at the end of the string) is '-' or '+'. Read this
character in if it is either. This determines if the final result is negative or positive
respectively. Assume the result is positive if neither is present. Read in next the characters until
the next non-digit character or the end of the input is reached. The rest of the string is ignored.
    Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read,
then the integer is 0. Change the sign as necessary (from step 2). If the integer is out of the
32-bit signed integer range [-231, 231 - 1], then clamp the integer so that it remains in the range.
Specifically, integers less than -231 should be clamped to -231, and integers greater than 231 - 1
should be clamped to 231 - 1. Return the integer as the final result.

Note:

    Only the space character ' ' is considered a whitespace character.
    Do not ignore any characters other than the leading whitespace or the rest of the string after
the digits.


Example 1:

Input: s = "42"
Output: 42
Explanation: The underlined characters are what is read in, the caret is the current reader
position. Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
The parsed integer is 42.
Since 42 is in the range [-231, 231 - 1], the final result is 42.

Example 2:

Input: s = "   -42"
Output: -42
Explanation:
Step 1: "   -42" (leading whitespace is read and ignored)
            ^
Step 2: "   -42" ('-' is read, so the result should be negative)
             ^
Step 3: "   -42" ("42" is read in)
               ^
The parsed integer is -42.
Since -42 is in the range [-231, 231 - 1], the final result is -42.

Example 3:

Input: s = "4193 with words"
Output: 4193
Explanation:
Step 1: "4193 with words" (no characters read because there is no leading whitespace)
         ^
Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a
non-digit)
             ^
The parsed integer is 4193.
Since 4193 is in the range [-231, 231 - 1], the final result is 4193.


Constraints:

    0 <= s.length <= 200
    s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void clipLeadingZeroes(vector<char> &d) {
        if (d.empty()) {
            return;
        }

        int start = 0;
        if (d[0] == '-' or d[0] == '+') {
            start = 1;
        }
        int zcount = 0;
        int i = start;
        while (i < d.size() - 1) {
            if (d[i] == '0' and d[i + 1] == '0') {
                zcount++;
            } else {
                break;
            }
            i++;
        }

        i = 1;
        while (i < zcount) {
            d.erase(d.begin() + start);
            i++;
        }
    }

    int convert(vector<char> s) {
        if (s.empty()) {
            return 0;
        }

        if (s.size() > 11) {
            if (s[0] == '-') {
                return INT_MIN;
            } else {
                return INT_MAX;
            }
        }

        long res = 0;
        bool sign = false;
        bool negative = false;
        if (s[0] == '-') {
            negative = true;
            sign = true;
        } else if (s[0] == '+') {
            negative = false;
            sign = true;
        }

        int i;
        if (sign) {
            i = 1;
        } else {
            i = 0;
        }

        while (i < s.size()) {
            res *= 10;
            res += s[i] - 48;
            i++;
        }

        if (negative) {
            res *= -1;
        }

        if (negative && res < INT_MIN) {
            return INT_MIN;
        } else if (!negative && res > INT_MAX) {
            return INT_MAX;
        }

        return res;
    }

  public:
    int myAtoi(string s) {
        bool digits_read = false;
        vector<char> d;

        for (char i : s) {
            if (!digits_read && (i == '-' || i == '+')) {
                digits_read = true;
                d.push_back(i);
            } else if (!digits_read && i == ' ') {
                continue;
            } else if (!digits_read && (i < '0' || i > '9')) {
                break;
            } else if (digits_read && (i < '0' || i > '9')) {
                break;
            } else if (i >= '0' && i <= '9') {
                digits_read = true;
                d.push_back(i);
            }
        }

        clipLeadingZeroes(d);
        return convert(d);
    }
};

int main() {
    Solution sol;
    int res;

    string s1 = "42";
    res = sol.myAtoi(s1);
    cout << res << endl;
    assert(res == 42);

    string s2 = "   -42";
    res = sol.myAtoi(s2);
    cout << res << endl;
    assert(res == -42);

    string s3 = "4193 with words";
    res = sol.myAtoi(s3);
    cout << res << endl;
    assert(res == 4193);

    string s4 = "words and 987";
    res = sol.myAtoi(s4);
    cout << res << endl;
    assert(res == 0);

    string s5 = "words and -987";
    res = sol.myAtoi(s5);
    cout << res << endl;
    assert(res == 0);

    string s6 = "-91283472332";
    res = sol.myAtoi(s6);
    cout << res << endl;
    assert(res == -2147483648);

    string s7 = "  0000000000012345678";
    res = sol.myAtoi(s7);
    cout << res << endl;
    assert(res == 12345678);

    string s8 = "-01324000";
    res = sol.myAtoi(s8);
    cout << res << endl;
    assert(res == -1324000);

    string s9 = "-2147483647";
    res = sol.myAtoi(s9);
    cout << res << endl;
    assert(res == -2147483647);

    string s10 = "20000000000000000000";
    res = sol.myAtoi(s10);
    cout << res << endl;
    assert(res == 2147483647);

    return 0;
}