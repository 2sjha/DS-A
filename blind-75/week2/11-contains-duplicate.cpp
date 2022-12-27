/*
https://leetcode.com/problems/contains-duplicate/

Given an integer array nums, return true if any value appears at least twice in the array, and
return false if every element is distinct.


Example 1:

Input: nums = [1,2,3,1]
Output: true

Example 2:

Input: nums = [1,2,3,4]
Output: false

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true


Constraints:

    1 <= nums.length <= 105
    -109 <= nums[i] <= 109
*/

/*
If the numbers are consecutive from 1 to N, then xor trick can be used
https://stackoverflow.com/questions/8018086/xor-to-find-duplicates-in-an-array
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  public:
    bool containsDuplicate(vector<int>& nums) {
        if (nums.size() <= 1) {
            return false;
        }

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] == nums[i + 1])
                return true;
        }
        return false;
    }

    bool containsDuplicateON(vector<int>& nums) {
        if (nums.size() <= 1) {
            return false;
        }

        unordered_map<int, int> mp;
        for (int n : nums) {
            mp[n]++;
            if (mp[n] == 2) {
                return true;
            }
        }
        return false;
    }
};