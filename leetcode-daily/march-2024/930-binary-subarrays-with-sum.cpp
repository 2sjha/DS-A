/*
https://leetcode.com/problems/binary-subarrays-with-sum

Given a binary array `nums` and an integer `goal`, return *the number of non-empty **subarrays** with a sum* `goal`.

A **subarray** is a contiguous part of the array.


**Example 1:**

**Input:** nums = [1,0,1,0,1], goal = 2
**Output:** 4
**Explanation:** The 4 subarrays are bolded and underlined below:
[**1,0,1**,0,1]
[**1,0,1,0**,1]
[1,**0,1,0,1**]
[1,0,**1,0,1**]

**Example 2:**

**Input:** nums = [0,0,0,0,0], goal = sss0
**Output:** 15


**Constraints:**

* `1 <= nums.length <= 3 * 10⁴`
* `nums[i]` is either `0` or `1`.
* `0 <= goal <= nums.length`
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Use prefix sum to solve in O(n)
// Detailed explanation in code

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int sum = 0;
        for(int i: nums) sum += i;
        if(sum < goal) return 0;

        int res = 0, curr_sum = 0;
        // Map to count the subarrays that start at index 0, with sum = key
        unordered_map<int, int> prefsum_subarrays_cnt;
        // special case for prefsum
        prefsum_subarrays_cnt[0] = 1;
        for(int i = 0; i < nums.size(); ++i) {
            // current sum = sum of current subarray size i+1 (0-i)
            curr_sum += nums[i];

            // Can we find a subarray with sum = goal - currsum
            // that starts from idx 0 and end at k (anywhere between 0 to i)
            if(prefsum_subarrays_cnt.count(curr_sum - goal)) {
                // If yes, then all those subarrays can be chopped off 
                // from our current array so we find all subarrays
                // that start from k and end at i
                // then resulting subarray will have sum = curr_sum - (curr_sum - goal)
                res += prefsum_subarrays_cnt[curr_sum - goal];
            }

            // update the count of subarrays with sum curr_sum to be used later
            prefsum_subarrays_cnt[curr_sum]++;
        }

        return res;
    }
};

int main() {
	Solution sol;

	vector<int> nums_1 = {1,0,1,0,1};
	int goal_1 = 2;
	int expected_1 = 4;
	int output_1 = sol.numSubarraysWithSum(nums_1, goal_1);
	cout << output_1 << endl;
	assert(output_1 == expected_1);

	vector<int> nums_2 = {0,0,0,0,0};
	int goal_2 = 0;
	int expected_2 = 15;
	int output_2 = sol.numSubarraysWithSum(nums_2, goal_2);
	cout << output_2 << endl;
	assert(output_2 == expected_2);

	return 0;
}