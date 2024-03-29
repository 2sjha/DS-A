/*
https://leetcode.com/problems/binary-subarrays-with-sum

Given a binary array `nums` and an integer `goal`, return *the number of non-empty **subarrays** with a sum* `goal`.

A **subarray** is a contiguous part of the array.


**Example 1:**

**Input:** nums = [1,0,1,0,1], goal = 2
**Output:** 4
**Explanation:** The 4 subarrays are bolded and underlined below:
[**1,0,1**,0,1]
[**1,0,1,0**,1]
[1,**0,1,0,1**]
[1,0,**1,0,1**]

**Example 2:**

**Input:** nums = [0,0,0,0,0], goal = 0
**Output:** 15


**Constraints:**

* `1 <= nums.length <= 3 * 10⁴`
* `nums[i]` is either `0` or `1`.
* `0 <= goal <= nums.length`
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    pub fn num_subarrays_with_sum(nums: Vec<i32>, goal: i32) -> i32 {
        let mut mp: HashMap<i32, i32> = HashMap::new();
        let n: usize = nums.len();
        let mut res: i32 = 0;
        let mut sum: i32 = 0;

        mp.insert(0, 1);
        for i in 0..n {
            sum += nums[i];

            if sum >= goal {
                if mp.get(&(sum - goal)).is_some() {
                    res += mp.get(&(sum - goal)).unwrap();
                }
            }

            if mp.get(&sum).is_some() {
                mp.insert(sum, mp.get(&sum).unwrap() + 1);
            } else {
                mp.insert(sum, 1);
            }
        }

        res
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![1, 0, 1, 0, 1];
    let goal_1: i32 = 2;
    let expected_1: i32 = 4;
    let output_1: i32 = Solution::num_subarrays_with_sum(nums_1, goal_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![0, 0, 0, 0, 0];
    let goal_2: i32 = 0;
    let expected_2: i32 = 15;
    let output_2: i32 = Solution::num_subarrays_with_sum(nums_2, goal_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
