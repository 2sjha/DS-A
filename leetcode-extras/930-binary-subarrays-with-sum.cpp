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

**Input:** nums = [0,0,0,0,0], goal = 0
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

class Solution {
private:
    unordered_map<int, unordered_map<int, pair<int, int>>> dp;

    // returns num of subarrays including idx and excluding idx
    pair<int, int> numSubarraysSum(vector<int>& nums, int idx, int goal) {
        if(idx >= nums.size()) return {0, 0};

        if(dp.count(idx) && dp[idx].count(goal)) return dp[idx][goal];


        pair<int, int> res;
        if(idx == nums.size() - 1) {
            if(!nums[idx] && !goal) res = {1, 0};
            else if(nums[idx] && goal == 1) res = {1, 0};
            else res = {0, 0};
        } else {
            if(nums[idx]) {
                pair<int, int> next = numSubarraysSum(nums, idx+1, goal);
                pair<int, int> next2 = numSubarraysSum(nums, idx+1, goal-1);
                res = {next2.first, next.first + next.second};
            } else {
                pair<int, int> next = numSubarraysSum(nums, idx+1, goal);
                if(next == make_pair(0, 0)) {
                    res = next;
                } else if (!goal) {
                    res = {1 + next.first, next.first + next.second};
                } else {
                    res = {next.first, next.first + next.second};
                }
            }
        }

        cout << "idx: " << idx << ", goal: " << goal << ", res: {" << res.first << ", " << res.second << "}\n";
        dp[idx][goal] = res;
        return dp[idx][goal];
    }
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int sum = 0;
        for(int i: nums) sum += i;
        if(sum < goal) return 0;

        pair<int, int> res = numSubarraysSum(nums, 0, goal);
        return res.first + res.second;
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