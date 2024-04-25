/*
https://leetcode.com/problems/n-th-tribonacci-number

The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given `n`, return the value of Tn.


**Example 1:**

**Input:** n = 4
**Output:** 4
**Explanation:**
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

**Example 2:**

**Input:** n = 25
**Output:** 1389537


**Constraints:**

* `0 <= n <= 37`
* The answer is guaranteed to fit within a 32-bit integer, ie. `answer <= 2^31 - 1`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int tribonacci(int n) {
        int t0 = 0, t1 = 1, t2 = 1;
        if (n == 0)
            return t0;
        else if (n == 1)
            return t1;
        else if (n == 2)
            return t2;
        else {
            int t3;
            for (int i = 3; i <= n; ++i) {
                t3 = t2 + t1 + t0;
                t0 = t1;
                t1 = t2;
                t2 = t3;
            }
            return t3;
        }
    }
};

int main() {
    Solution sol;

    int n_1 = 4;
    int expected_1 = 4;
    int output_1 = sol.tribonacci(n_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    int n_2 = 25;
    int expected_2 = 1389537;
    int output_2 = sol.tribonacci(n_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}