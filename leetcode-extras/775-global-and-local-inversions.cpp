/*
https://leetcode.com/problems/global-and-local-inversions/

You are given an integer array nums of length n which represents a permutation of all the integers
in the range [0, n - 1].

The number of global inversions is the number of the different pairs (i, j) where:

    0 <= i < j < n
    nums[i] > nums[j]

The number of local inversions is the number of indices i where:

    0 <= i < n - 1
    nums[i] > nums[i + 1]

Return true if the number of global inversions is equal to the number of local inversions.


Example 1:

Input: nums = [1,0,2]
Output: true
Explanation: There is 1 global inversion and 1 local inversion.

Example 2:

Input: nums = [1,2,0]
Output: false
Explanation: There are 2 global inversions and 1 local inversion.


Constraints:

    n == nums.length
    1 <= n <= 105
    0 <= nums[i] < n
    All the integers of nums are unique.
    nums is a permutation of all the numbers in the range [0, n - 1].
*/

/*
Solvable in O(NlogN). dont want to do O(N)
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int globalInversionsMerge(vector<int> &nums, int start, int mid, int end) {
        int size = end - start + 1;
        vector<int> tmp = vector<int>(size, -1);

        int inv = 0;
        int i = start;
        int j = mid + 1;

        for (int k = 0; k < size; ++k) {
            if (i > mid) {
                tmp[k] = nums[j];
                ++j;
            } else if (j > end) {
                tmp[k] = nums[i];
                ++i;
            } else if (nums[i] < nums[j]) {
                tmp[k] = nums[i];
                ++i;
            } else if (nums[i] > nums[j]) {
                tmp[k] = nums[j];
                ++j;
                inv += mid - i + 1;
            } else {
                tmp[k] = nums[i];
                i++;
            }
        }

        for (int k = start; k <= end; ++k) {
            nums[k] = tmp[k - start];
        }

        return inv;
    }

    int globalInversions(vector<int> &nums, int start, int end) {
        if (end - start < 1) {
            return 0;
        }

        int gInv = 0;
        int mid = start + ((end - start) / 2);
        gInv += globalInversions(nums, start, mid);
        gInv += globalInversions(nums, mid + 1, end);
        gInv += globalInversionsMerge(nums, start, mid, end);
        return gInv;
    }

    int localInversions(vector<int> &nums) {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] > nums[i + 1])
                count++;
        }

        return count;
    }

  public:
    bool isIdealPermutation(vector<int> &nums) {
        int lInv = localInversions(nums);
        int gInv = globalInversions(nums, 0, nums.size() - 1);
        cout << "lInv: " << lInv << ", gInv: " << gInv << endl;
        return gInv == lInv;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> nums = {{1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {1, 2, 0, 3}, {0, 3, 1, 2}};
    for (int i = 0; i < 5; ++i) {
        auto res = sol.isIdealPermutation(nums[i]);
        cout << "res: " << res << endl;
    }

    return 0;
}