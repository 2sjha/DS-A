/*
https://leetcode.com/problems/minimum-array-end

You are given two integers `n` and `x`. You have to construct an array of **positive** integers
`nums` of size `n` where for every `0 <= i < n - 1`, `nums[i + 1]` is **greater than** `nums[i]`,
and the result of the bitwise `AND` operation between all elements of `nums` is `x`.

Return the **minimum** possible value of `nums[n - 1]`.


**Example 1:**

**Input:** n = 3, x = 4

**Output:** 6

**Explanation:**

`nums` can be `[4,5,6]` and its last element is 6.

**Example 2:**

**Input:** n = 2, x = 7

**Output:** 15

**Explanation:**

`nums` can be `[7,15]` and its last element is 15.


**Constraints:**

* `1 <= n, x <= 10⁸`
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<bool> getBinary(int x) {
        vector<bool> res;
        while (x > 0) {
            res.push_back(x % 2);
            x /= 2;
        }
        return res;
    }

    long long getDecimal(vector<bool> &bin) {
        long long res = 0;
        for (int i = 0; i < bin.size(); ++i) {
            if (bin[i])
                res += pow(2, i);
        }
        return res;
    }

    int countZerosBetween(vector<bool> &bin) {
        int zeros = 0;
        for (bool b : bin) {
            if (!b)
                zeros++;
        }
        return zeros;
    }

    vector<bool> fillInBetween(vector<bool> &bin, vector<bool> &fill) {
        vector<bool> filled = bin;
        for (int i = 0, j = 0; i < filled.size(); ++i) {
            if (!filled[i] && j < fill.size()) {
                filled[i] = fill[j++];
            }
        }

        return filled;
    }

    vector<bool> fillBeyond(vector<bool> &bin, vector<bool> &fill) {
        vector<bool> filled = bin;
        int j = 0;
        for (int i = 0; i < filled.size(); ++i) {
            if (!filled[i]) {
                filled[i] = fill[j++];
            }
        }
        while (j < fill.size()) {
            filled.push_back(fill[j++]);
        }
        return filled;
    }

  public:
    long long minEnd(int n, int x) {
        if (n == 1)
            return (long long)x;

        vector<bool> x_bin = getBinary(x);
        vector<bool> last = getBinary(n - 1);
        int bw_zeros = countZerosBetween(x_bin);
        int max_n_within_x_len = pow(2, bw_zeros);

        if (n <= max_n_within_x_len) {
            vector<bool> filled = fillInBetween(x_bin, last);
            return getDecimal(filled);
        } else {
            vector<bool> filled = fillBeyond(x_bin, last);
            return getDecimal(filled);
        }
    }
};

int main() {
    Solution sol;

    int n_1 = 3;
    int x_1 = 4;
    long long expected_1 = 6;
    long long output_1 = sol.minEnd(n_1, x_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    int n_2 = 2;
    int x_2 = 7;
    long long expected_2 = 15;
    long long output_2 = sol.minEnd(n_2, x_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    int n_3 = 3;
    int x_3 = 2;
    long long expected_3 = 6;
    long long output_3 = sol.minEnd(n_3, x_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    int n_4 = 2;
    int x_4 = 4;
    long long expected_4 = 5;
    long long output_4 = sol.minEnd(n_4, x_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    return 0;
}