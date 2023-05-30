'''
https://leetcode.com/problems/search-in-rotated-sorted-array/

There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.


Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:

Input: nums = [1], target = 0
Output: -1


Constraints:

    1 <= nums.length <= 5000
    -104 <= nums[i] <= 104
    All values of nums are unique.
    nums is an ascending array that is possibly rotated.
    -104 <= target <= 104
'''

from typing import List


class Solution:
    def binary_search(self, nums: List[int], start: int, end: int, target: int) -> int:
        if start > end:
            return -1
        elif start == end:
            if nums[start] == target:
                return start
            else:
                return -1

        while start < end:
            if nums[start] == target:
                return start
            if nums[end] == target:
                return end

            mid = start + (end - start) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] > target:
                end = mid - 1
            else:
                start = mid + 1

        return -1

    def search(self, nums: List[int], target: int) -> int:
        k = 0
        for i in range(len(nums) - 1):
            if nums[i] > nums[i + 1]:
                k = i
        res = -1
        res = self.binary_search(nums, 0, k, target)
        if res != -1:
            return res

        res = self.binary_search(nums, k + 1, len(nums) - 1, target)
        return res


def main():
    sol: Solution = Solution()

    nums = [4, 5, 6, 7, 0, 1, 2]
    target = 0
    print(sol.search(nums, target))

    nums = [1]
    target = 0
    print(sol.search(nums, target))

    nums = [4, 5, 6, 7, 0, 1, 2]
    target = 3
    print(sol.search(nums, target))


if __name__:
    main()
