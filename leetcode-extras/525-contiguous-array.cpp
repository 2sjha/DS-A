/*
https://leetcode.com/problems/contiguous-array

Given a binary array `nums`, return *the maximum length of a contiguous subarray with an equal number of *`0`* and *`1`.


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

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = 0, res = 0;
        vector<int> count = {0, 0};

        while(r < n) {
            count[nums[r]]++;
            r++;
            while(r < n && count[0] != count[1]) {
                count[nums[r]]++;
                if(count[0] == count[1]) break;

                r++;
            }

            res = max(res, r-l);
        }

        return res;
    }
};

int main() {
	Solution sol;

	vector<int> nums_1 = {0,1};
	int expected_1 = 2;
	int output_1 = sol.findMaxLength(nums_1);
	cout << output_1 << endl;
	assert(output_1 == expected_1);

	vector<int> nums_2 = {0,1,0};
	int expected_2 = 2;
	int output_2 = sol.findMaxLength(nums_2);
	cout << output_2 << endl;
	assert(output_2 == expected_2);

	return 0;
}