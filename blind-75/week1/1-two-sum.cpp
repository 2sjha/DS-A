/*
https://leetcode.com/problems/two-sum

Given an array of integers nums and an integer target, return indices of the two
numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not
use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]



Constraints:
    2 <= nums.length <= 104
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    Only one valid answer exists.

*/
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Solution {
  public:
    vector<int> twoSumSorted(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        vector<int> result;

        sort(nums.begin(), nums.end());

        while (low < high) {
            if (nums[low] + nums[high] == target) {
                result.push_back(nums[low]);
                result.push_back(nums[high]);
                return result;
            } else if (nums[low] + nums[high] > target) {
                high--;
            } else {
                low++;
            }
        }

        result.push_back(-1);
        result.push_back(-1);
        return result;
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        vector<int> res;

        for (int i = 0; i < nums.size(); i++) {
            if (map.find(target - nums[i]) != map.end() && map[target - nums[i]] != i) {
                res.push_back(map[target - nums[i]]);
                res.push_back(i);
                return res;
            }

            map[nums[i]] = i;
        }

        res.push_back(-1);
        return res;
    }
};

int main() {
    vector<int> input;
    int n, target;
    Solution solution;

    cout << "number of elements" << endl;
    cin >> n;
    cout << "input array" << endl;

    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        input.push_back(temp);
    }

    cout << "target sum" << endl;
    cin >> target;

    vector<int> res = solution.twoSum(input, target);

    cout << res[0] << "\t" << res[1] << endl;

    return 0;
}