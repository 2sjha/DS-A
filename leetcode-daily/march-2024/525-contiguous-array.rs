/*
https://leetcode.com/problems/contiguous-array

Given a binary array `nums`, return *the maximum length of a contiguous subarray with an equal number of *`0`* and *`1`.


**Example 1:**

**Input:** nums = [0,1]
**Output:** 2
**Explanation:** [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

**Example 2:**

**Input:** nums = [0,1,0]
**Output:** 2
**Explanation:** [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `nums[i]` is either `0` or `1`.
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    pub fn find_max_length(mut nums: Vec<i32>) -> i32 {
        let n: usize = nums.len();
        for i in 0..n {
            if nums[i] == 0 {
                nums[i] = -1;
            }
        }

        let mut res: usize = 0;
        let mut sum: i32 = 0;
        let mut min_len_subarrays: HashMap<i32, usize> = HashMap::new();
        min_len_subarrays.insert(0, 0);

        for i in 0..n {
            sum += nums[i];

            if min_len_subarrays.get(&sum).is_some() {
                res = std::cmp::max(
                    res,
                    i + 1 - min_len_subarrays.get(&sum).unwrap(),
                );
            }

            if min_len_subarrays.get(&sum).is_none() {
                min_len_subarrays.insert(sum, i + 1);
            }
        }

        res as i32
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![0, 1];
    let expected_1: i32 = 2;
    let output_1: i32 = Solution::find_max_length(nums_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![0, 1, 0];
    let expected_2: i32 = 2;
    let output_2: i32 = Solution::find_max_length(nums_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
