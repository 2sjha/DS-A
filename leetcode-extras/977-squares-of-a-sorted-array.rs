/*
https://leetcode.com/problems/squares-of-a-sorted-array/

Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.


Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].

Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]


Constraints:

    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums is sorted in non-decreasing order.


Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?
*/

struct Solution;
impl Solution {
    fn square_as_is(nums: &Vec<i32>) -> Vec<i32> {
        let mut i: usize = 0;
        let size: usize = nums.len();
        let mut res: Vec<i32> = vec![0; size];

        for num in nums {
            res[i] = num * num;
            i += 1;
        }

        res
    }

    pub fn sorted_squares(nums: Vec<i32>) -> Vec<i32> {
        let mut all_positive: bool = true;
        for num in &nums {
            if *num < 0 {
                all_positive = false;
                break;
            }
        }
        if all_positive {
            return Self::square_as_is(&nums);
        }

        let mut all_negative: bool = true;
        for num in &nums {
            if *num > 0 {
                all_negative = false;
                break;
            }
        }
        if all_negative {
            let mut squares: Vec<i32> = Self::square_as_is(&nums);
            squares.reverse();
            return squares;
        }

        let mut res: Vec<i32> = Vec::new();
        let mut low: i32 = 0;
        let mut low_us: usize;
        let mut high: usize = 0;

        for i in 0..nums.len() {
            if nums[i] >= 0 {
                low = (i - 1) as i32;
                high = i;
                break;
            }
        }

        while low >= 0 || high < nums.len() {
            low_us = low as usize;
            if low >= 0 && high < nums.len() && nums[low_us].abs() <= nums[high].abs() {
                res.push(nums[low_us] * nums[low_us]);
                low -= 1;
            } else if low >= 0 && high < nums.len() && nums[low_us].abs() > nums[high].abs() {
                res.push(nums[high] * nums[high]);
                high += 1;
            } else if low >= 0 {
                res.push(nums[low_us] * nums[low_us]);
                low -= 1;
            } else if high < nums.len() {
                res.push(nums[high] * nums[high]);
                high += 1;
            }
        }

        res
    }
}

fn main() {
    let nums1: Vec<i32> = vec![1, 2, 3, 4, 5];
    let res1: Vec<i32> = Solution::sorted_squares(nums1);
    println!("{:?}", res1);

    let nums2: Vec<i32> = vec![-4, -1, 0, 3, 10];
    let res2: Vec<i32> = Solution::sorted_squares(nums2);
    println!("{:?}", res2);

    let nums3: Vec<i32> = vec![-7, -3, 2, 3, 11];
    let res3: Vec<i32> = Solution::sorted_squares(nums3);
    println!("{:?}", res3);
}
