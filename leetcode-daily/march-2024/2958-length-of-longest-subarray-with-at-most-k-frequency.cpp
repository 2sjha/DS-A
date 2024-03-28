/*
https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency

You are given an integer array `nums` and an integer `k`.

The **frequency** of an element `x` is the number of times it occurs in an array.

An array is called **good** if the frequency of each element in this array is **less than or equal**
to `k`.

Return *the length of the **longest** **good** subarray of* `nums`*.*

A **subarray** is a contiguous non-empty sequence of elements within an array.


**Example 1:**

**Input:** nums = [1,2,3,1,2,3,1,2], k = 2
**Output:** 6
**Explanation:** The longest possible good subarray is [1,2,3,1,2,3] since the values 1, 2, and 3
occur at most twice in this subarray. Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are
also good. It can be shown that there are no good subarrays with length more than 6.

**Example 2:**

**Input:** nums = [1,2,1,2,1,2,1,2], k = 1
**Output:** 2
**Explanation:** The longest possible good subarray is [1,2] since the values 1 and 2 occur at most
once in this subarra y. Note that the subarray [2,1] is also good. It can be shown that there are no
good subarrays with length more than 2.

**Example 3:**

**Input:** nums = [5,5,5,5,5,5,5], k = 4
**Output:** 4
**Explanation:** The longest possible good subarray is [5,5,5,5] since the value 5 occurs 4 times in
this subarray. It can be shown that there are no good subarrays with length more than 4.


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `1 <= nums[i] <= 10⁹`
* `1 <= k <= nums.length`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    // O(n.logk) solution that works
    int maxSubarrayLength(vector<int> &nums, int k) {
        unordered_map<int, set<int>> seen;
        int n = nums.size(), res = 0, l = 0;
        for (int r = 0; r < n; ++r) {
            seen[nums[r]].insert(r);

            if (seen[nums[r]].size() > k) {
                res = max(res, r - l);
                int new_l = *seen[nums[r]].begin() + 1;
                seen[nums[r]].erase(l - 1);

                for (int j = l; j < new_l; ++j) {
                    seen[nums[j]].erase(j);
                }
                l = new_l;
            } else {
                res = max(res, r - l + 1);
            }
        }
        return res;
    }

    // O(n) solution after looking at a solution
    int maxSubarrayLength2(vector<int> &nums, int k) {
        unordered_map<int, int> freq;
        int n = nums.size(), res = 0, l = 0;
        for (int r = 0; r < n; ++r) {
            freq[nums[r]]++;

            if (freq[nums[r]] > k) {
                res = max(res, r - l);
                // Move left pointer of sliding window until freq[violating number] <= k
                // It will stop when it passes the first violating number
                while (freq[nums[r]] > k) {
                    freq[nums[l]]--;
                    l++;
                }

                // Another approach here is that move left pointer until you encounter
				// the same violating number and then move one more step. 
                // while (nums[l] != [nums[r]]) {
                //     freq[nums[l]]--;
                //     l++;
                // }
                // freq[nums[l]]--;
                // l++;
            } else {
                res = max(res, r - l + 1);
            }
        }
        return res;
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {1, 2, 3, 1, 2, 3, 1, 2};
    int k_1 = 2;
    int expected_1 = 6;
    int output_1 = sol.maxSubarrayLength(nums_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {1, 2, 1, 2, 1, 2, 1, 2};
    int k_2 = 1;
    int expected_2 = 2;
    int output_2 = sol.maxSubarrayLength(nums_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<int> nums_3 = {5, 5, 5, 5, 5, 5, 5};
    int k_3 = 4;
    int expected_3 = 4;
    int output_3 = sol.maxSubarrayLength(nums_3, k_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}