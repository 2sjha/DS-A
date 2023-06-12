/*
https://leetcode.com/problems/letter-combinations-of-a-phone-number

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that
the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does
not map to any letters.

digit_map['2'] = "abc";
digit_map['3'] = "def";
digit_map['4'] = "ghi";
digit_map['5'] = "jkl";
digit_map['6'] = "mno";
digit_map['7'] = "pqrs";
digit_map['8'] = "tuv";
digit_map['9'] = "wxyz";

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:

Input: digits = ""
Output: []

Example 3:

Input: digits = "2"
Output: ["a","b","c"]


Constraints:

    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        unordered_map<char, string> digit_map;
        digit_map['2'] = "abc";
        digit_map['3'] = "def";
        digit_map['4'] = "ghi";
        digit_map['5'] = "jkl";
        digit_map['6'] = "mno";
        digit_map['7'] = "pqrs";
        digit_map['8'] = "tuv";
        digit_map['9'] = "wxyz";

        string word;
        vector<string> res_copy;
        for (char digit : digits) {
            if (res.empty()) {
                for (char l : digit_map[digit]) {
                    word = "";
                    word += l;
                    res.push_back(word);
                }
            } else {
                res_copy.clear();
                for (string curr_word : res) {
                    for (char l : digit_map[digit]) {
                        res_copy.push_back(curr_word + l);
                    }
                }
                res = res_copy;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<string> res;

    string nums1 = "2";
    res = sol.letterCombinations(nums1);
    printArray(res);

    string nums2 = "23";
    res = sol.letterCombinations(nums2);
    printArray(res);

    string nums3 = "";
    res = sol.letterCombinations(nums3);
    printArray(res);

    return 0;
}