/*
https://leetcode.com/problems/subarrays-with-k-different-integers

Given an integer array `nums` and an integer `k`, return *the number of **good subarrays** of *`nums`.

A **good array** is an array where the number of different integers in that array is exactly `k`.

* For example, `[1,2,3,1,2]` has `3` different integers: `1`, `2`, and `3`.

A **subarray** is a **contiguous** part of an array.


**Example 1:**

**Input:** nums = [1,2,1,2,3], k = 2
**Output:** 7
**Explanation:** Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,
1,2]

**Example 2:**

**Input:** nums = [1,2,1,3,4], k = 3
**Output:** 3
**Explanation:** Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].


**Constraints:**

* `1 <= nums.length <= 2 * 10⁴`
* `1 <= nums[i], k <= nums.length`
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    fn subarrays_with_atmost_k_distinct(nums: &Vec<i32>, k: i32) -> i32 {
        let mut freq: HashMap<i32, usize> = HashMap::new();
        let mut l: usize = 0;
        let mut r: usize = 0;
        let mut res: usize = 0;
        let n: usize = nums.len();

        while r < n {
            if freq.get(&nums[r]).is_some() {
                freq.insert(nums[r], 1 + freq.get(&nums[r]).unwrap());
            } else {
                freq.insert(nums[r], 1);
            }

            while l <= r && freq.len() > k as usize {
                if *freq.get(&nums[l]).unwrap() == 1 {
                    freq.remove(&nums[l]);
                } else {
                    freq.insert(nums[l], freq.get(&nums[l]).unwrap() - 1);
                }
                l += 1;
            }

            res += r - l + 1;
            r += 1;
        }

        res as i32
    }

    pub fn subarrays_with_k_distinct(nums: Vec<i32>, k: i32) -> i32 {
        Self::subarrays_with_atmost_k_distinct(&nums, k)
            - Self::subarrays_with_atmost_k_distinct(&nums, k - 1)
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![1, 2, 1, 2, 3];
    let k_1: i32 = 2;
    let expected_1: i32 = 7;
    let output_1: i32 = Solution::subarrays_with_k_distinct(nums_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![1, 2, 1, 3, 4];
    let k_2: i32 = 3;
    let expected_2: i32 = 3;
    let output_2: i32 = Solution::subarrays_with_k_distinct(nums_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
