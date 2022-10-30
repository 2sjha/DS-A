/*
Given an array of integers nums which is sorted in ascending order, and an integer target, write a
function to search target in nums. If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity.



Example 1:

Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Example 2:

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1



Constraints:

    1 <= nums.length <= 104
    -104 < nums[i], target < 104
    All the integers in nums are unique.
    nums is sorted in ascending order.
*/

#include "bits/stdc++.h"
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    int search(vector<int>& nums, int target) {
        int found = -1;

        int low = 0, high = nums.size() - 1;
        int mid = (low + high) / 2;
        while (low <= high) {
            mid = (low + high) / 2;
            cout << "low = " << low << ", high = " << high << ", mid = " << mid << endl;

            if (nums[mid] == target) {
                found = mid;
                break;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return found;
    }
};

int main() {
    Solution sol;
    int n, target;
    vector<int> nums;

    cout << "Enter size of the array" << endl;
    cin >> n;
    cout << "Enter array" << endl;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }

    cout << "Enter target" << endl;
    cin >> target;
    int res = sol.search(nums, target);
    cout << res << endl;
    return 0;
}