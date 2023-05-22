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
