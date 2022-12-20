/*
https://leetcode.com/problems/maximum-subarray/

Given an integer array nums, find the subarray which has the largest sum and return its sum.

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: nums = [1]
Output: 1

Example 3:
Input: nums = [5,4,-1,7,8]
Output: 23

Constraints:
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104 

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide
and conquer approach, which is more subtle.
*/

#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  private:
    bool allPositive(vector<int> nums) {
        for (int n : nums) {
            if (n < 0)
                return false;
        }
        return true;
    }

    bool allNegative(vector<int> nums) {
        for (int n : nums) {
            if (n > 0)
                return false;
        }
        return true;
    }

    int sumArray(vector<int> nums) {
        int sum = 0;
        for (int n : nums) {
            sum += n;
        }
        return sum;
    }

    int maxArray(vector<int> nums) {
        int maxElem = INT_MIN;
        for (int n : nums) {
            maxElem = max(maxElem, n);
        }
        return maxElem;
    }

    int maxSubArrayDnC(vector<int>& nums, int start_idx, int end_idx) {
        if (start_idx == end_idx) {
            return nums[start_idx];
        }

        if (end_idx - start_idx == 1) {
            return max(max(nums[start_idx], nums[end_idx]), nums[start_idx] + nums[end_idx]);
        }

        int mid = start_idx + ((end_idx - start_idx) / 2);

        int leftMaxSubArrSum = maxSubArrayDnC(nums, start_idx, mid - 1);
        int rightMaxSubArrSum = maxSubArrayDnC(nums, mid, end_idx);

        int leftSum = 0;
        int maxLeftSum = INT_MIN;
        for (int i = mid - 1; i >= start_idx; --i) {
            leftSum += nums[i];
            maxLeftSum = max(leftSum, maxLeftSum);
        }

        int rightSum = 0;
        int maxRightSum = INT_MIN;
        for (int i = mid; i <= end_idx; ++i) {
            rightSum += nums[i];
            maxRightSum = max(rightSum, maxRightSum);
        }

        return max(max(leftMaxSubArrSum, rightMaxSubArrSum), maxLeftSum + maxRightSum);
    }

  public:
    /*
    Based on Kadane's Algorithm O(n)
    https://www.youtube.com/watch?v=ohHWQf1HDfU&t=775s
    https://en.wikipedia.org/wiki/Maximum_subarray_problem
    Aassumes that there is atleast one positive integer.
    If all positive integers, then return total array sum
    If all negative integers, then return max element
    */
    int maxSubArray(vector<int>& nums) {
        if (allNegative(nums)) {
            return maxArray(nums);
        }

        if (allPositive(nums)) {
            return sumArray(nums);
        }

        int sum = 0;
        int maxSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum = sum + nums[i];
            maxSum = max(sum, maxSum);
            if (sum < 0) {
                sum = 0;
            }
        }

        return maxSum;
    }

    int maxSubArrayDnC(vector<int>& nums) { return maxSubArrayDnC(nums, 0, nums.size() - 1); }
};

int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    Solution s;
    int res;
    res = s.maxSubArray(nums);
    cout << res << endl;
    res = s.maxSubArrayDnC(nums);
    cout << res << endl;

    return 0;
}