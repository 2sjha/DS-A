/*
https://leetcode.com/problems/longest-palindromic-substring/

Given a string s, return the longest palindromic substring in s.


Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:

Input: s = "cbbd"
Output: "bb"


Constraints:

    1 <= s.length <= 1000
    s consist of only digits and English letters.
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    string get_palindrome(string s, int start, bool odd) {
        deque<char> palindrome;
        int left, right;
        if (odd) {
            palindrome.push_front(s[start]);
            left = start - 1;
            right = start + 1;
        } else {
            left = start;
            right = start + 1;
        }

        while (left >= 0 && right < s.length()) {
            if (s[left] == s[right]) {
                palindrome.push_front(s[left]);
                palindrome.push_back(s[right]);
                left--;
                right++;
            } else {
                break;
            }
        }

        string palindrome_str = "";
        while (!palindrome.empty()) {
            palindrome_str += palindrome.front();
            palindrome.pop_front();
        }

        return palindrome_str;
    }

  public:
    string longestPalindrome(string s) {
        string odd, even, max = "";
        for (int i = 0; i < s.length(); ++i) {
            odd = get_palindrome(s, i, true);
            even = get_palindrome(s, i, false);

            if (odd.length() > max.length()) {
                max = odd;
            }
            if (even.length() > max.length()) {
                max = even;
            }
        }

        return max;
    }
};

int main() {
    Solution sol;
    string res;

    string s1 = "babad";
    res = sol.longestPalindrome(s1);
    cout << res << endl;
    assert(res == "bab");

    string s2 = "cbbd";
    res = sol.longestPalindrome(s2);
    cout << res << endl;
    assert(res == "bb");

    return 0;
}