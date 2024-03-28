/*
https://leetcode.com/problems/subarray-product-less-than-k

Given an array of integers `nums` and an integer `k`, return *the number of contiguous subarrays
where the product of all the elements in the subarray is strictly less than *`k`.


**Example 1:**

**Input:** nums = [10,5,2,6], k = 100
**Output:** 8
**Explanation:** The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

**Example 2:**

**Input:** nums = [1,2,3], k = 0
**Output:** 0


**Constraints:**

* `1 <= nums.length <= 3 * 10⁴`
* `1 <= nums[i] <= 1000`
* `0 <= k <= 10⁶`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    // O(n^2) sliding window solution that works
    int numSubarrayProductLessThanK2(vector<int> &nums, int k) {
        if (k == 0)
            return 0;

        int res = 0;
        int product;
        for (int i = 0; i < nums.size(); ++i) {
            product = 1;
            for (int j = i; j < nums.size(); ++j) {
                product *= nums[j];
                if (product >= k)
                    break;
                else
                    res++;
            }
        }

        return res;
    }

    // O(n) solution after looking up some solutions
    // and Use the intuition that if there is a n sized array which is valid
    // then there are close to n^2 subarrays [n + n-1 + n-2 + n-3 + ...].
    // but if we add one more element that will still keep the array valid,
    // then there are n more subarrays due to this element.
    int numSubarrayProductLessThanK(vector<int> &nums, int k) {
        if (k == 0)
            return 0;

        int n = nums.size(), res = 0, product = 1, l = 0, r = 0;
        while (r < n) {
            product *= nums[r];

			// move left pointer until product < k
            while (l <= r && product >= k) {
                product /= nums[l];
                l++;
            }

            res += r - l + 1;
            r++;
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {10, 5, 2, 6};
    int k_1 = 100;
    int expected_1 = 8;
    int output_1 = sol.numSubarrayProductLessThanK(nums_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {1, 2, 3};
    int k_2 = 0;
    int expected_2 = 0;
    int output_2 = sol.numSubarrayProductLessThanK(nums_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}