/*
https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor

Given an array of integers `arr`.

We want to select three indices `i`, `j` and `k` where `(0 <= i < j <= k < arr.length)`.

Let's define `a` and `b` as follows:

* `a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]`
* `b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]`

Note that **^** denotes the **bitwise-xor** operation.

Return *the number of triplets* (`i`, `j` and `k`) Where `a == b`.


**Example 1:**

**Input:** arr = [2,3,1,6,7]
**Output:** 4
**Explanation:** The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)

**Example 2:**

**Input:** arr = [1,1,1,1,1]
**Output:** 10


**Constraints:**

* `1 <= arr.length <= 300`
* `1 <= arr[i] <= 10⁸`
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Used hints to solve.

class Solution {
  public:
    int countTriplets(vector<int> &arr) {
        int n = arr.size(), res = 0;

        vector<vector<int>> xor_mat(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            int xor_so_far = arr[i];
            xor_mat[i][i] = xor_so_far;
            for (int k = i + 1; k < n; ++k) {
                xor_so_far ^= arr[k];
                xor_mat[i][k] = xor_so_far;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int k = i + 1; k < n; ++k) {
                // For this subarray i to k, we must partition it such that both partitions have
                // equal xors. If such partitions exits and they have equal xor,
                // then the xor of this overall subarray must be 0.
                if (xor_mat[i][k] == 0) {
                    // If this subarray has 0 xor, then at each bit there are even no. of 1s.
                    // There are only 2 cases for every bit to be even no. of 1s, E = E + E or E = O
                    // + O. In either case, the final xor of the partition will be equal for every
                    // partition in this subarray. Thus if the subarray is of lenth m, there are m-1
                    // partitions of equal xor
                    res += k - i;
                }
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> arr_1 = {2, 3, 1, 6, 7};
    int expected_1 = 4;
    int output_1 = sol.countTriplets(arr_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> arr_2 = {1, 1, 1, 1, 1};
    int expected_2 = 10;
    int output_2 = sol.countTriplets(arr_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}