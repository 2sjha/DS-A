/*
https://leetcode.com/problems/powx-n

Implement pow(x, n), which calculates x raised to the power n (i.e., xn).


Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000

Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25


Constraints:

    -100.0 < x < 100.0
    -2^31 <= n <= 2^31-1
    n is an integer.
    Either x is not zero or n > 0.
    -10^4 <= x^n <= 10^4
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    unordered_map<long, double> calc;

  private:
    double doPow(double x, long n) {
        if (n < 0)
            return 0;
        else if (n == 0)
            return 1;
        else if (n == 1)
            return x;

        if (calc.count(n))
            return calc[n];

        double res = doPow(x, n / 2) * doPow(x, n / 2);
        if (n % 2 != 0) {
            res = res * x;
        }
        calc[n] = res;
        return res;
    }

  public:
    double myPow(double x, int n) {
        if (x == 1) {
            return x;
        }
        if (x == -1) {
            if (n % 2 == 0) {
                return 1;
            } else {
                return -1;
            }
        }

        double res = 1;
        if (n > 0) {
            res = doPow(x, n);
        } else {
            long p = -1 * (long)n;
            res = doPow(x, p);
            res = 1 / res;
        }

        return res;
    }
};

int main() {
    Solution sol;
    double res;
    double x;
    int n;

    x = 2.00000, n = 10;
    res = sol.myPow(x, n);
    cout << res << endl;

    x = 2.10000, n = 3;
    res = sol.myPow(x, n);
    cout << res << endl;

    x = 2.00000, n = -2;
    res = sol.myPow(x, n);
    cout << res << endl;

    return 0;
}