/*
https://leetcode.com/problems/find-the-duplicate-number

Given an array of integers `nums` containing `n + 1` integers where each integer is in the range
`[1, n]` inclusive.

There is only **one repeated number** in `nums`, return *this repeated number*.

You must solve the problem **without** modifying the array `nums` and uses only constant extra
space.


**Example 1:**

**Input:** nums = [1,3,4,2,2]
**Output:** 2

**Example 2:**

**Input:** nums = [3,1,3,4,2]
**Output:** 3

**Example 3:**

**Input:** nums = [3,3,3,3,3]
**Output:** 3


**Constraints:**

* `1 <= n <= 10⁵`
* `nums.length == n + 1`
* `1 <= nums[i] <= n`
* All the integers in `nums` appear only **once** except for **precisely one integer** which appears
**two or more** times.


Follow up:

* How can we prove that at least one duplicate number must exist in `nums`?
* Can you solve the problem in linear runtime complexity?
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int findDuplicate(vector<int> &nums) {
        int low = 1;
        int high = nums.size() - 1;
        int mid;
        while (low < high) {
            mid = (low + high) / 2;
            int count = 0;
            for (int i : nums) {
                if (i <= mid)
                    count++;
            }
            if (count > mid) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {1, 3, 4, 2, 2};
    int expected_1 = 2;
    int output_1 = sol.findDuplicate(nums_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {3, 1, 3, 4, 2};
    int expected_2 = 3;
    int output_2 = sol.findDuplicate(nums_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<int> nums_3 = {3, 3, 3, 3, 3};
    int expected_3 = 3;
    int output_3 = sol.findDuplicate(nums_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}