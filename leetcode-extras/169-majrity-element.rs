/*
https://leetcode.com/problems/majority-element/

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.


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

Follow-up: Could you solve the problem in linear time and in O(1) space?
*/

struct Solution;
impl Solution {
    fn check_majority(nums: &Vec<i32>, start: usize, end: usize, maj: Vec<i32>) -> Option<i32> {
        let mut count: usize;
        for elem in maj {
            count = 0;
            for i in start..end + 1 {
                if nums[i] == elem {
                    count += 1;
                }
            }
            if count > (end - start) / 2 {
                return Some(elem);
            }
        }

        return None;
    }

    fn majority_elem(nums: &Vec<i32>, start: usize, end: usize) -> Vec<i32> {
        if end < start {
            return vec![];
        }

        if end - start == 2 {
            if nums[start] == nums[start + 1] || nums[start] == nums[end] {
                return vec![nums[start]];
            } else if nums[start + 1] == nums[end] {
                return vec![nums[end]];
            }
        } else if end == start {
            return vec![nums[start]];
        } else if end - start == 1 && nums[start] != nums[end] {
            return vec![nums[start], nums[end]];
        } else if end - start == 1 {
            return vec![nums[start]];
        }

        let mid1: usize = start + ((end - start) / 3);
        let mid2: usize = start + ((2 * (end - start)) / 3);

        let maj1: Vec<i32> = Self::majority_elem(nums, start, mid1);
        let maj2: Vec<i32> = Self::majority_elem(nums, mid1 + 1, mid2);
        let maj3: Vec<i32> = Self::majority_elem(nums, mid2 + 1, end);

        let maj1_res = Self::check_majority(nums, start, end, maj1);
        if maj1_res.is_some() {
            return vec![maj1_res.unwrap()];
        }

        let maj2_res = Self::check_majority(nums, start, end, maj2);
        if maj2_res.is_some() {
            return vec![maj2_res.unwrap()];
        }

        let maj3_res = Self::check_majority(nums, start, end, maj3);
        if maj3_res.is_some() {
            return vec![maj3_res.unwrap()];
        }

        return vec![nums[start]];
    }

    pub fn majority_element(nums: Vec<i32>) -> i32 {
        let end: usize = nums.len() - 1;
        let maj: Vec<i32> = Self::majority_elem(&nums, 0, end);

        maj[0]
    }
}

fn main() {
    let mut res: i32;

    let nums1: Vec<i32> = vec![3, 2, 3];
    res = Solution::majority_element(nums1);
    println!("{:?}", res);
    assert!(res == 3);

    let nums2: Vec<i32> = vec![2, 2, 1, 1, 1, 2, 2];
    res = Solution::majority_element(nums2);
    println!("{:?}", res);
    assert!(res == 2);

    let nums3: Vec<i32> = vec![8, 8, 7, 7, 7];
    res = Solution::majority_element(nums3);
    println!("{:?}", res);
    assert!(res == 7);

    let nums4: Vec<i32> = vec![1, 3, 1, 1, 4, 1, 1, 5, 1, 1, 6, 2, 2];
    res = Solution::majority_element(nums4);
    println!("{:?}", res);
    assert!(res == 1);
}
