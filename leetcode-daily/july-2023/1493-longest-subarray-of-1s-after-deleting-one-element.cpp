/*
https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element

Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array. Return
0 if there is no such subarray.


Example 1:

Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.

Example 2:

Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value
of 1's is [1,1,1,1,1].

Example 3:

Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.


Constraints:

    1 <= nums.length <= 105
    nums[i] is either 0 or 1.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int longestSubarray(vector<int> &nums) {
        vector<int> zeroIndices;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                zeroIndices.push_back(i);
            }
        }

        if (zeroIndices.empty() || zeroIndices.size() == 1) {
            return nums.size() - 1;
        }

        zeroIndices.push_back(nums.size());
        int res = 0;
        int prev = -1;
        int ones = 0;

        for (int i = 1; i < zeroIndices.size(); ++i) {
            ones = 0;
            for (int j = prev + 1; j < zeroIndices[i - 1]; ++j) {
                if (nums[j] == 1)
                    ones++;
            }
            for (int j = zeroIndices[i - 1] + 1; j < zeroIndices[i]; ++j) {
                if (nums[j] == 1)
                    ones++;
            }
            prev = zeroIndices[i - 1];
            res = max(res, ones);
        }

        return res;
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> nums1 = {1, 1, 0, 1};
    res = sol.longestSubarray(nums1);
    cout << res << endl;
    assert(res == 3);

    vector<int> nums2 = {0, 1, 1, 1, 0, 1, 1, 0, 1};
    res = sol.longestSubarray(nums2);
    cout << res << endl;
    assert(res == 5);

    vector<int> nums3 = {1, 1, 1};
    res = sol.longestSubarray(nums3);
    cout << res << endl;
    assert(res == 2);

    return 0;
}