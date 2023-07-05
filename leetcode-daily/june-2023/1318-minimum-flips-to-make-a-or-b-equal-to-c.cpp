/*
https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/

Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to
make ( a OR b == c ). (bitwise OR operation). Flip operation consists of change any single bit 1 to
0 or change the bit 0 to 1 in their binary representation.


Example 1:

Input: a = 2, b = 6, c = 5
Output: 3
Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)

Example 2:

Input: a = 4, b = 2, c = 7
Output: 1

Example 3:

Input: a = 1, b = 2, c = 3
Output: 0


Constraints:

    1 <= a <= 10^9
    1 <= b <= 10^9
    1 <= c <= 10^9
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    vector<int> getBinary(int num) {
        vector<int> ans;
        for (int i = 0; i < 32; ++i) {
            ans.push_back(num % 2);
            num = num / 2;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

  public:
    int minFlipsBinaryConversion(int a, int b, int c) {
        vector<int> a_b, b_b, c_b;
        a_b = getBinary(a);
        b_b = getBinary(b);
        c_b = getBinary(c);

        // No need for DP, greedily counting bitFlips works
        // Because there's no backtracking invloved,
        // We dont have to choose which bit to flip, we just flip the necessary bits
        int bitflips = 0;
        for (int i = 0; i < 32; ++i) {
            if (c_b[i] == 1) {
                if (a_b[i] == 0 && b_b[i] == 0) {
                    bitflips += 1;
                }
            } else if (c_b[i] == 0) {
                if (a_b[i] == 1 && b_b[i] == 1) {
                    bitflips += 2;
                } else if (a_b[i] == 1 || b_b[i] == 1) {
                    bitflips += 1;
                }
            }
        }

        return bitflips;
    }

    int minFlipsBitManipulation(int a, int b, int c) {
        int bitflips = 0;
        int a_i, b_i, c_i;
        for (int i = 0; i < 32; ++i) {
            a_i = ((a >> i) & 1);
            b_i = ((b >> i) & 1);
            c_i = ((c >> i) & 1);

            if (c_i == 1) {
                if (a_i == 0 && b_i == 0) {
                    bitflips += 1;
                }
            } else if (c_i == 0) {
                if (a_i == 1 && b_i == 1) {
                    bitflips += 2;
                } else if (a_i == 1 || b_i == 1) {
                    bitflips += 1;
                }
            }
        }

        return bitflips;
    }

    int minFlips(int a, int b, int c) {
        return minFlipsBinaryConversion(a, b, c);
        // return minFlipsBitManipulation(a, b, c);
    }
};

int main() {
    Solution sol;
    int res;

    int a1 = 2, b1 = 6, c1 = 5;
    res = sol.minFlips(a1, b1, c1);
    cout << res << endl;
    assert(res == 3);

    int a2 = 4, b2 = 2, c2 = 7;
    res = sol.minFlips(a2, b2, c2);
    cout << res << endl;
    assert(res == 1);

    int a3 = 1, b3 = 2, c3 = 3;
    res = sol.minFlips(a3, b3, c3);
    cout << res << endl;
    assert(res == 0);

    int a4 = 8, b4 = 3, c4 = 5;
    res = sol.minFlips(a4, b4, c4);
    cout << res << endl;
    assert(res == 3);

    return 0;
}