/*
https://leetcode.com/problems/word-break/

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a
space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.


Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false


Constraints:

    1 <= s.length <= 300
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 20
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    set<string> words;
    vector<pair<bool, bool>> dp;

  private:
    void init_words_set(string &s, vector<string> &wordDict) {
        dp = vector<pair<bool, bool>>();
        words = set<string>();
        for (int i = 0; i < s.length(); ++i) {
            dp.push_back({false, false});
        }
        for (string word : wordDict) {
            words.insert(word);
        }
    }

    bool find_words(string &s, int start) {
        if (start >= s.length()) {
            return true;
        }
        if (dp[start].first) {
            return dp[start].second;
        }

        string tmp;
        bool res = false;
        for (int i = start; i < s.length(); ++i) {
            tmp += s[i];
            if (words.find(tmp) != words.end()) {
                res = res || find_words(s, i + 1);
            }
        }
        dp[start].first = true;
        dp[start].second = res;
        return res;
    }

  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        init_words_set(s, wordDict);

        return find_words(s, 0);
    }
};

int main() {
    Solution sol;
    bool res;

    string s1 = "leetcode";
    vector<string> dict1 = {"leet", "code"};
    res = sol.wordBreak(s1, dict1);
    cout << res << endl;
    assert(res == true);

    string s2 = "applepenapple";
    vector<string> dict2 = {"apple", "pen"};
    res = sol.wordBreak(s2, dict2);
    cout << res << endl;
    assert(res == true);

    string s3 = "catsandog";
    vector<string> dict3 = {"cats", "dog", "sand", "and", "cat"};
    res = sol.wordBreak(s3, dict3);
    cout << res << endl;
    assert(res == false);

    return 0;
}