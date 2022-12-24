/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i
!= k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.


Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.


Constraints:

    3 <= nums.length <= 3000
    -105 <= nums[i] <= 105
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<pair<int, int>> getTwoSumPairs(vector<int> &nums, int reqSum, int curr_idx) {
        vector<pair<int, int>> res;
        int left, right;

        if (curr_idx == nums.size() - 2) {
            return res;
        }

        if (curr_idx > 0 and nums[curr_idx] == nums[curr_idx - 1]) {
            return res;
        }

        left = curr_idx + 1;
        right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == reqSum) {
                pair<int, int> p = {nums[left], nums[right]};
                res.push_back(p);
                while (nums[left] == p.first && nums[right] == p.second) {
                    if (left < nums.size() - 1) {
                        left++;
                    } else {
                        break;
                    }
                    if (right > 0) {
                        right--;
                    } else {
                        break;
                    }
                }
            } else if (sum > reqSum) {
                right--;
            } else if (sum < reqSum) {
                left++;
            }
        }

        return res;
    }

    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); ++i) {
            int reqSum = -(nums[i]);
            vector<pair<int, int>> twoSumPairs = getTwoSumPairs(nums, reqSum, i);
            if (!twoSumPairs.empty()) {
                for (pair<int, int> twoSum : twoSumPairs) {
                    res.push_back({nums[i], twoSum.first, twoSum.second});
                }
            }
        }

        return res;
    }
};

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    // vector<int> nums = {1, 0, 1};
    // vector<int> nums = {0, 0, 0};
    Solution sol;

    auto res = sol.threeSum(nums);
    for (auto r : res) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}