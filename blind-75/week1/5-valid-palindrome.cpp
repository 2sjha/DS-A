/*
https://leetcode.com/problems/valid-palindrome

A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and
removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric
characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.


Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.


Constraints:

    1 <= s.length <= 2 * 105
    s consists only of printable ASCII characters.
*/

#include <bits/stdc++.h>
#include <cctype>
#include <iostream>
using namespace std;

class Solution {
  public:
    bool isPalindrome(string s) {
        string copy;
        for (int i = 0; i < s.length(); i++) {
            char element = s[i];
            if (isalnum(element)) {
                copy.push_back(tolower(element));
            }
        }

        int mid = copy.length() / 2;
        bool isPalindrome = true;
        if (copy.length() % 2 == 0) {
            int k = 0;
            while (mid + k < copy.length() && mid - 1 - k >= 0) {
                if (copy[mid + k] != copy[mid - 1 - k]) {
                    isPalindrome = false;
                    break;
                }
                k++;
            }
        } else {
            int k = 1;
            while (mid + k < copy.length() && mid - k >= 0) {
                if (copy[mid + k] != copy[mid - k]) {
                    isPalindrome = false;
                    break;
                }
                k++;
            }
        }

        return isPalindrome;
    }
};

int main() {
    Solution sol;
    string s;

    cout << "Enter String" << endl;
    cin >> s;

    bool res = sol.isPalindrome(s);
    cout << res << endl;

    return 0;
}