/*
https://leetcode.com/problems/longest-palindrome/

Given a string s which consists of lowercase or uppercase letters, return the length of the longest
palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

Example 1:

Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.

Example 2:

Input: s = "a"
Output: 1
Explanation: The longest palindrome that can be built is "a", whose length is 1.

 

Constraints:

    1 <= s.length <= 2000
    s consists of lowercase and/or uppercase English letters only.


*/

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int longestPalindrome(string s) {
    unordered_map<char, int> mp;
    for (char c : s) {
        mp[c]++;
    }

    int maxOddCount = 0;
    char maxOddChar;
    for (auto iter = mp.begin(); iter != mp.end(); iter++) {
        if (iter->second % 2 != 0) {
            if (iter->second > maxOddCount) {
                maxOddCount = iter->second;
                maxOddChar = iter->first;
            }
        }
    }

    int totalCount = 0;
    for (auto iter = mp.begin(); iter != mp.end(); iter++) {
        if (iter->second % 2 == 0) {
            totalCount += iter->second;
        } else {
            if (iter->first == maxOddChar) {
                totalCount += iter->second;
            } else {
                totalCount += iter->second - 1;
            }
        }
    }

    return totalCount;
}

int main() {
    string s;
    cin >> s;
    int res = longestPalindrome(s);
    cout << res << endl;
}