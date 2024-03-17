/*
https://leetcode.com/problems/contiguous-array

Given a binary array `nums`, return *the maximum length of a contiguous subarray with an equal
number of *`0`* and *`1`*.


**Example 1:**

**Input:** nums = [0,1]
**Output:** 2
**Explanation:** [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

**Example 2:**

**Input:** nums = [0,1,0]
**Output:** 2
**Explanation:** [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `nums[i]` is either `0` or `1`.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Solve with prefix sum in O(n)

class Solution {
  public:
    int findMaxLength(vector<int> &nums) {
        int n = nums.size(), res = 0, curr_sum = 0;
        // replace 0 with -1 to make sum = 0 at desired subarrays to use the prefix sum method
        // same count of 0s and 1s means sum of subarray = 0 when 0s in array replaced with -1
        for (int i = 0; i < n; ++i) {
            if (!nums[i])
                nums[i] = -1;
        }

        // Prefix sum map to store the minimum size subarray that starts with idx = 0
        // with a given prefix_sum
        unordered_map<int, int> prefsum_minsize;
        // Init empty subarray of size = 0
        prefsum_minsize[0] = 0;

        for (int i = 0; i < n; ++i) {
            curr_sum += nums[i];

            // if we can find a minimum size subarray with sum = curr_sum that starts with idx = 0
            // and ends at k such that  0 <= k < i which can be chopped off from current
            // subarray(which also has sum = curr_sum), then our resulting subarray is of
            // the maximum size with sum = 0
            if (prefsum_minsize.count(curr_sum)) {
                // choose between the maximum size subarray with sum = 0 so far
                // and current subarray size - the minimum size that can be chopped off
                res = max(res, i + 1 - prefsum_minsize[curr_sum]);

                // no need to update the map because as go further the subarrays that start with
                // idx = 0 and have sum = curr_sum are only going to increase in size
            } else {
                prefsum_minsize[curr_sum] = i + 1;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {0, 1};
    int expected_1 = 2;
    int output_1 = sol.findMaxLength(nums_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {0, 1, 0};
    int expected_2 = 2;
    int output_2 = sol.findMaxLength(nums_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<int> nums_3 = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1,
                          1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0,
                          0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1,
                          1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1,
                          0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1};
    int expected_3 = 94;
    int output_3 = sol.findMaxLength(nums_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);
    return 0;
}