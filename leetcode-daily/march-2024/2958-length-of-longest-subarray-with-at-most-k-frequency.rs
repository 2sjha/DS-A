/*
https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency

You are given an integer array `nums` and an integer `k`.

The **frequency** of an element `x` is the number of times it occurs in an array.

An array is called **good** if the frequency of each element in this array is **less than or equal** to `k`.

Return *the length of the **longest** **good** subarray of* `nums`*.*

A **subarray** is a contiguous non-empty sequence of elements within an array.


**Example 1:**

**Input:** nums = [1,2,3,1,2,3,1,2], k = 2
**Output:** 6
**Explanation:** The longest possible good subarray is [1,2,3,1,2,3] since the values 1, 2, and 3 occur at most twice in
 this subarray. Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
It can be shown that there are no good subarrays with length more than 6.

**Example 2:**

**Input:** nums = [1,2,1,2,1,2,1,2], k = 1
**Output:** 2
**Explanation:** The longest possible good subarray is [1,2] since the values 1 and 2 occur at most once in this subarra
y. Note that the subarray [2,1] is also good.
It can be shown that there are no good subarrays with length more than 2.

**Example 3:**

**Input:** nums = [5,5,5,5,5,5,5], k = 4
**Output:** 4
**Explanation:** The longest possible good subarray is [5,5,5,5] since the value 5 occurs 4 times in this subarray.
It can be shown that there are no good subarrays with length more than 4.


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `1 <= nums[i] <= 10⁹`
* `1 <= k <= nums.length`
*/

use std::collections::BTreeSet;
use std::collections::HashMap;

struct Solution;
impl Solution {
    pub fn max_subarray_length(nums: Vec<i32>, k: i32) -> i32 {
        let mut seen: HashMap<i32, BTreeSet<usize>> = HashMap::new();
        let mut res: i32 = 0;
        let mut l: usize = 0;
        let mut r: usize = 0;
        let n: usize = nums.len();

        while r < n {
            let seen_indices_opt: Option<&BTreeSet<usize>> = seen.get(&nums[r]);
            if seen_indices_opt.is_some() {
                (*seen.get_mut(&nums[r]).unwrap()).insert(r);
            } else {
                let mut seen_indices: BTreeSet<usize> = BTreeSet::new();
                seen_indices.insert(r);
                seen.insert(nums[r], seen_indices);
            }

            while seen.get(&nums[r]).unwrap().len() > k as usize {
                let first_k_seen: usize =
                    *seen.get(&nums[l]).unwrap().first().unwrap();
                (*seen.get_mut(&nums[l]).unwrap()).remove(&first_k_seen);
                l += 1;
            }

            res = std::cmp::max(res, (r - l + 1) as i32);
            r += 1;
        }

        res
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![1, 2, 3, 1, 2, 3, 1, 2];
    let k_1: i32 = 2;
    let expected_1: i32 = 6;
    let output_1: i32 = Solution::max_subarray_length(nums_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![1, 2, 1, 2, 1, 2, 1, 2];
    let k_2: i32 = 1;
    let expected_2: i32 = 2;
    let output_2: i32 = Solution::max_subarray_length(nums_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let nums_3: Vec<i32> = vec![5, 5, 5, 5, 5, 5, 5];
    let k_3: i32 = 4;
    let expected_3: i32 = 4;
    let output_3: i32 = Solution::max_subarray_length(nums_3, k_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
