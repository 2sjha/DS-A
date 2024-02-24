/*
https://leetcode.com/problems/majority-element/description/

Given an array `nums` of size `n`, return *the majority element*.

The majority element is the element that appears more than `⌊n / 2⌋` times. You may assume that the majority element
always exists in the array.


**Example 1:**

**Input:** nums = [3,2,3]
**Output:** 3

**Example 2:**

**Input:** nums = [2,2,1,1,1,2,2]
**Output:** 2


**Constraints:**

* `n == nums.length`
* `1 <= n <= 5 * 10⁴`
* `-10⁹ <= nums[i] <= 10⁹`


**Follow-up:** Could you solve the problem in linear time and in `O(1)` space?
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    pub fn majority_element(nums: Vec<i32>) -> i32 {
        let n: usize = nums.len();
        let mut mp: HashMap<i32, usize> = HashMap::new();

        for num in nums {
            if mp.contains_key(&num) {
                mp.insert(num, mp[&num] + 1);
            } else {
                mp.insert(num, 1);
            }
            if mp[&num] > n / 2 {
                return num;
            }
        }

        0
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![3, 2, 3];
    let expected_1: i32 = 3;
    let output_1: i32 = Solution::majority_element(nums_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![2, 2, 1, 1, 1, 2, 2];
    let expected_2: i32 = 2;
    let output_2: i32 = Solution::majority_element(nums_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
