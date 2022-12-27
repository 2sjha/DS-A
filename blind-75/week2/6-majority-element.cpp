/*
https://leetcode.com/problems/majority-element/

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the
majority element always exists in the array.


Example 1:

Input: nums = [3,2,3]
Output: 3

Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2


Constraints:

    n == nums.length
    1 <= n <= 5 * 104
    -109 <= nums[i] <= 109

PS - easily solvable using hashmap;
to do in O(N) time and O(1) space, read https://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html
*/

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  public:
    int majorityElement(vector<int> &nums) {
        int size = nums.size();
        unordered_map<int, int> map;
        for (int i : nums) {
            map[i]++;
        }
        int max = 0, max_elem = 0;
        for (auto iter = map.begin(); iter != map.end(); iter++) {
            if (iter->second > max) {
                max = iter->second;
                max_elem = iter->first;
            }
        }

        return max_elem;
    }

    int majorityElementInO1Space(vector<int> &nums) {
        int size = nums.size();
        int major, count_major;
        for (int i = 0; i < size - 1; ++i) {
            if (count_major == 0) {
                count_major++;
                major = nums[i];
            } else if (nums[i] == major) {
                count_major++;
            } else {
                count_major--;
            }
        }

        return major;
    }
};

int main() {
    vector<int> arr = {2, 2, 1, 1, 1, 2, 2};
    Solution s;
    int res = s.majorityElement(arr);
    cout << res << endl;

    return 0;
}