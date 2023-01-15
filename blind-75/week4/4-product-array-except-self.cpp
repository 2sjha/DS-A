/*
https://leetcode.com/problems/product-of-array-except-self/

Given an integer array nums, return an array answer such that answer[i] is equal to the product of
all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.


Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]


Constraints:

    2 <= nums.length <= 105
    -30 <= nums[i] <= 30
    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not
count as extra space for space complexity analysis.)
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int n = nums.size();
        vector<int> res, left, right;
        res = left = right = vector<int>(n);

        left[0] = 1;
        for (int i = 1; i < n; ++i) {
            left[i] = left[i - 1] * nums[i - 1];
        }

        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i) {
            right[i] = right[i + 1] * nums[i + 1];
        }

        res[0] = right[0];
        res[n - 1] = left[n - 1];
        for (int i = 1; i < n - 1; ++i) {
            res[i] = left[i] * right[i];
        }

        return res;
    }

    vector<int> productExceptSelf_O1Space(vector<int> &nums) {
        int n = nums.size();
        int left = 1;
        vector<int> res(n, 1);

        for (int i = n - 2; i >= 0; --i) {
            res[i] = res[i + 1] * nums[i + 1];
        }

        for (int i = 0; i < n; ++i) {
            res[i] = left * res[i];
            left = left * nums[i];
        }

        return res;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4};

    Solution sol;
    vector<int> res = sol.productExceptSelf(nums);
    for (int i : res) {
        cout << i << " ";
    }
    return 0;
}