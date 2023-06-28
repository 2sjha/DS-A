/*
https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/

You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:

    nums.length == n
    nums[i] is a positive integer where 0 <= i < n.
    abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
    The sum of all the elements of nums does not exceed maxSum.
    nums[index] is maximized.

Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.


Example 1:

Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].

Example 2:

Input: n = 6, index = 1,  maxSum = 10
Output: 3


Constraints:

    1 <= n <= maxSum <= 10^9
    0 <= index < n
*/

struct Solution;
impl Solution {
    fn get_sum_until(n: i32) -> i32 {
        if n <= 0 {
            return 0;
        }

        (n * (n + 1)) / 2
    }

    fn crop_sum_left_right(val: i32, index: i32, n: i32) -> i32 {
        val * val - Self::get_sum_until(val - (index + 1)) - Self::get_sum_until(val - n - index)
    }

    fn crop_sum_left(val: i32, index: i32) -> i32 {
        val * val - Self::get_sum_until(val - (index + 1))
    }

    fn crop_sum_right(val: i32, index: i32, n: i32) -> i32 {
        val * val - Self::get_sum_until(val - n - index)
    }

    pub fn max_value(n: i32, index: i32, max_sum: i32) -> i32 {
        let mut max_val: i32 = 1;
        let mut sum: i32 = 0;

        let left: bool = index < n / 2;

        while sum <= max_sum {
            if left {
                sum = std::cmp::max(
                    Self::crop_sum_left(max_val, index),
                    Self::crop_sum_left_right(max_val, index, n),
                );
            } else {
                sum = std::cmp::max(
                    Self::crop_sum_right(max_val, index, n),
                    Self::crop_sum_left_right(max_val, index, n),
                );
            }
            // println!("{}", sum);
            // sum = Self::crop_sum_left_right(max_val, index, n);
            max_val += 1;
        }
        max_val -= 2;

        max_val
    }
}

fn main() {
    let mut res: i32;

    let mut n: i32 = 4;
    let mut index: i32 = 2;
    let mut max_sum: i32 = 6;
    // res = Solution::max_value(n, index, max_sum);
    // println!("{:?}", res);
    // assert!(res == 2);

    // n = 6;
    // index = 1;
    // max_sum = 10;
    // res = Solution::max_value(n, index, max_sum);
    // println!("{:?}", res);
    // assert!(res == 3);

    n = 3;
    index = 2;
    max_sum = 18;
    res = Solution::max_value(n, index, max_sum);
    println!("{:?}", res);
    assert!(res == 7);
}
