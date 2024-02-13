/*
https://leetcode.com/problems/4sum-ii/

Given four integer arrays `nums1`, `nums2`, `nums3`, and `nums4` all of length `n`, return the number of tuples `(i, j,
k, l)` such that:

* `0 <= i, j, k, l < n`
* `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`


**Example 1:**

**Input:** nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
**Output:** 2
**Explanation:**
The two tuples are:
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

**Example 2:**

**Input:** nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
**Output:** 1


**Constraints:**

* `n == nums1.length`
* `n == nums2.length`
* `n == nums3.length`
* `n == nums4.length`
* `1 <= n <= 200`
* `-2²⁸ <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2²⁸`
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    pub fn four_sum_count(
        nums1: Vec<i32>,
        nums2: Vec<i32>,
        nums3: Vec<i32>,
        nums4: Vec<i32>,
    ) -> i32 {
        let n: usize = nums1.len();
        let mut res: i32 = 0;
        let mut mp: HashMap<i32, i32> = HashMap::new();
        let mut target: i32;
        let mut partial_sum: i32;
        for i in 0..n {
            for j in 0..n {
                partial_sum = nums3[i] + nums4[j];
                if mp.get(&partial_sum).is_some() {
                    mp.insert(partial_sum, mp[&partial_sum] + 1);
                } else {
                    mp.insert(partial_sum, 1);
                }
            }
        }

        for k in 0..n {
            for l in 0..n {
                target = -1 * (nums1[k] + nums2[l]);
                if mp.get(&target).is_some() {
                    res += mp.get(&target).unwrap();
                }
            }
        }

        return res;
    }
}

fn main() {
    let nums1_1: Vec<i32> = vec![1, 2];
    let nums2_1: Vec<i32> = vec![-2, -1];
    let nums3_1: Vec<i32> = vec![-1, 2];
    let nums4_1: Vec<i32> = vec![0, 2];
    let expected_1: i32 = 2;
    let output_1: i32 =
        Solution::four_sum_count(nums1_1, nums2_1, nums3_1, nums4_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums1_2: Vec<i32> = vec![0];
    let nums2_2: Vec<i32> = vec![0];
    let nums3_2: Vec<i32> = vec![0];
    let nums4_2: Vec<i32> = vec![0];
    let expected_2: i32 = 1;
    let output_2: i32 =
        Solution::four_sum_count(nums1_2, nums2_2, nums3_2, nums4_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
