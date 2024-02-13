/*
https://leetcode.com/problems/3sum/

Given an integer array nums, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`,
and `j!= k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.


**Example 1:**

**Input:** nums = [-1,0,1,2,-1,-4]
**Output:** [[-1,-1,2],[-1,0,1]]
**Explanation:** 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

**Example 2:**

**Input:** nums = [0,1,1]
**Output:** []
**Explanation:** The only possible triplet does not sum up to 0.

**Example 3:**

**Input:** nums = [0,0,0]
**Output:** [[0,0,0]]
**Explanation:** The only possible triplet sums up to 0.


**Constraints:**

* `3 <= nums.length <= 3000`
* `-10⁵ <= nums[i] <= 10⁵`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int low = 0, high = 0, a = 0, b = 0, c = 0;
        for(int i=0; i<n;) {
            a = -nums[i];
            low = i+1;
            high = n-1;

            while(low < n && high >= 0 && low < high) {
                if(nums[low] + nums[high] == a) {
                    b = nums[low];
                    c = nums[high];

                    res.push_back({nums[i], nums[low], nums[high]});
                    while(low < n && nums[low] == b) {
                        low++;
                    }
                    while(high >= 0 && nums[high] == c) {
                        high--;
                    }
                } else if(nums[low] + nums[high] > a) {
                    high--;
                } else {
                    low++;
                }
            }

            while(i < n && nums[i] == -a) {
                i++;
            }
        }

        return res;
    }
};

int main() {
	Solution sol;

	vector<int> nums_1 = {-1,0,1,2,-1,-4};
	vector<vector<int>> expected_1 = {{-1,-1,2},{-1,0,1}};
	vector<vector<int>> output_1 = sol.threeSum(nums_1);
	print2Dmatrix(output_1);
	assert(output_1 == expected_1);

	vector<int> nums_2 = {0,1,1};
	vector<vector<int>> expected_2 = {};
	vector<vector<int>> output_2 = sol.threeSum(nums_2);
	print2Dmatrix(output_2);
	assert(output_2 == expected_2);

	vector<int> nums_3 = {0,0,0};
	vector<vector<int>> expected_3 = {{0,0,0}};
	vector<vector<int>> output_3 = sol.threeSum(nums_3);
	print2Dmatrix(output_3);
	assert(output_3 == expected_3);

	return 0;
}