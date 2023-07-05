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
    fn add_ones(n: i32) -> i64 {
        if n <= 0 {
            return 0;
        }

        n as i64
    }

    fn get_sum_until(n: i32) -> i64 {
        if n <= 0 {
            return 0;
        }

        ((n as i64 * (n + 1) as i64) / 2) as i64
    }

    fn square(val: i32) -> i64 {
        (val as i64 * val as i64) as i64
    }

    fn get_max_sum_with_val(val: i32, index: i32, n: i32) -> i32 {
        let sq = Self::square(val);
        let l_crop = Self::get_sum_until(val - (index + 1));
        let r_crop = Self::get_sum_until(val - n + index);
        let l_ones = Self::add_ones(index + 1 - val);
        let r_ones = Self::add_ones(n - index - val);

        let sum: i64 = sq - l_crop - r_crop + l_ones + r_ones;

        if sum > (i32::MAX as i64) {
            return 0;
        } else {
            return sum as i32;
        }
    }

    pub fn max_value(n: i32, index: i32, max_sum: i32) -> i32 {
        let mut val: i64 = 1;
        let mut low: i64 = 1;
        let mut high: i64 = i32::MAX as i64;
        let mut sum: i32;
        let mut next_sum: i32;

        while low < high {
            val = (low + high) / 2;
            sum = Self::get_max_sum_with_val(val as i32, index, n);
            next_sum = Self::get_max_sum_with_val(val as i32 + 1, index, n);

            if sum == 0 {
                high = val;
            } else if sum <= max_sum && next_sum > max_sum {
                break;
            } else if sum <= max_sum && next_sum <= max_sum {
                low = val;
            } else {
                high = val;
            }
        }

        val as i32
    }
}

fn main() {
    let mut res: i32;
    let mut n: i32;
    let mut index: i32;
    let mut max_sum: i32;

    n = 4;
    index = 2;
    max_sum = 6;
    res = Solution::max_value(n, index, max_sum);
    println!("{}", res);
    assert!(res == 2);

    n = 6;
    index = 1;
    max_sum = 10;
    res = Solution::max_value(n, index, max_sum);
    println!("{}", res);
    assert!(res == 3);

    n = 3;
    index = 2;
    max_sum = 18;
    res = Solution::max_value(n, index, max_sum);
    println!("{}", res);
    assert!(res == 7);

    n = 4;
    index = 0;
    max_sum = 4;
    res = Solution::max_value(n, index, max_sum);
    println!("{}", res);
    assert!(res == 1);

    n = 4;
    index = 0;
    max_sum = 6;
    res = Solution::max_value(n, index, max_sum);
    println!("{}", res);
    assert!(res == 2);

    n = 9;
    index = 4;
    max_sum = 764086444;
    res = Solution::max_value(n, index, max_sum);
    println!("{}", res);
    assert!(res == 84898496);
}
