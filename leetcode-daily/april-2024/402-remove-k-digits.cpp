/*
https://leetcode.com/problems/remove-k-digits

Given string num representing a non-negative integer `num`, and an integer `k`, return *the smallest
possible integer after removing* `k` *digits from* `num`.


**Example 1:**

**Input:** num = "1432219", k = 3
**Output:** "1219"
**Explanation:** Remove the three digits 4, 3, and 2 to form the new number 1219 which is the
smallest.

**Example 2:**

**Input:** num = "10200", k = 1
**Output:** "200"
**Explanation:** Remove the leading 1 and the number is 200. Note that the output must not contain
leading zeroes.

**Example 3:**

**Input:** num = "10", k = 2
**Output:** "0"
**Explanation:** Remove all the digits from the number and it is left with nothing which is 0.


**Constraints:**

* `1 <= k <= num.length <= 10⁵`
* `num` consists of only digits.
* `num` does not have any leading zeros except for the zero itself.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    string removeLeadingZeros(string num) {
        int i = 0, n = num.length();
        string res = "";
        while (num[i] == '0') {
            i++;
        }
        while (i < n) {
            res.push_back(num[i++]);
        }
        if (res == "")
            return "0";
        else
            return res;
    }

    string removeDigits(string num, int k) {
        deque<char> dq;
        int del = 0;
        int i = 0, n = num.length();
        string res = "";
        while (i < n) {
            if (del == k)
                break;
            while (!dq.empty() && del < k && dq.back() > num[i]) {
                del++;
                dq.pop_back();
            }
            dq.push_back(num[i]);

            i++;
        }

        if (i == n) {
            while (del < k) {
                del++;
                dq.pop_back();
            }
        } else {
            while (i < n) {
                dq.push_back(num[i++]);
            }
        }

        while (!dq.empty()) {
            res.push_back(dq.front());
            dq.pop_front();
        }

        return res;
    }

  public:
    string removeKdigits(string num, int k) {
        int n = num.length();
        if (num == "0" || k == n)
            return "0";

        string res = removeDigits(num, k);
        return removeLeadingZeros(res);
    }
};

int main() {
    Solution sol;

    string num_1 = "1432219";
    int k_1 = 3;
    string expected_1 = "1219";
    string output_1 = sol.removeKdigits(num_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string num_2 = "10200";
    int k_2 = 1;
    string expected_2 = "200";
    string output_2 = sol.removeKdigits(num_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string num_3 = "10";
    int k_3 = 2;
    string expected_3 = "0";
    string output_3 = sol.removeKdigits(num_3, k_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}