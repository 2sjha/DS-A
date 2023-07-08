/*
https://leetcode.com/problems/minimum-size-subarray-sum/

Given an array of positive integers nums and a positive integer target, return the minimal length of
a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0
instead.


Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0


Constraints:

    1 <= target <= 109
    1 <= nums.length <= 105
    1 <= nums[i] <= 104

Follow up: If you have figured out the O(n) solution, try coding another solution of which the time
complexity is O(n log(n)).
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int low = 0, sum = 0, i = 0, minLen = INT_MAX;

        while (i < nums.size()) {
            sum += nums[i];

            while (sum >= target) {
                sum -= nums[low];
                minLen = min(minLen, i - low + 1);
                low++;
            }

            i++;
        }

        if (minLen == INT_MAX) {
            return 0;
        } else {
            return minLen;
        }
    }
};

int main() {
    Solution sol;
    int res;

    int target1 = 7;
    vector<int> nums1 = {2, 3, 1, 2, 4, 3};
    res = sol.minSubArrayLen(target1, nums1);
    cout << res << endl;
    assert(res == 2);

    int target2 = 4;
    vector<int> nums2 = {1, 4, 4};
    res = sol.minSubArrayLen(target2, nums2);
    cout << res << endl;
    assert(res == 1);

    int target3 = 11;
    vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1};
    res = sol.minSubArrayLen(target3, nums3);
    cout << res << endl;
    assert(res == 0);

    return 0;
}