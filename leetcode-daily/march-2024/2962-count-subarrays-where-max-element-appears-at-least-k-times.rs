/*
https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times

You are given an integer array `nums` and a **positive** integer `k`.

Return *the number of subarrays where the **maximum** element of *`nums`* appears **at least** *`k`* times in that
subarray.*

A **subarray** is a contiguous sequence of elements within an array.


**Example 1:**

**Input:** nums = [1,3,2,3,3], k = 2
**Output:** 6
**Explanation:** The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,
3], [2,3,3] and [3,3].

**Example 2:**

**Input:** nums = [1,4,2,1], k = 3
**Output:** 0
**Explanation:** No subarray contains the element 4 at least 3 times.


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `1 <= nums[i] <= 10⁶`
* `1 <= k <= 10⁵`
*/

struct Solution;
impl Solution {
    fn atmost(nums: &Vec<i32>, target: i32) -> i64 {
        let mut res: i64 = 0;
        let mut l: usize = 0;
        let mut r: usize = 0;
        let mut sum: i32 = 0;
        let n: usize = nums.len();

        while r < n {
            sum += nums[r];
            while l <= r && sum > target {
                sum -= nums[l];
                l += 1;
            }

            res += (r - l + 1) as i64;
            r += 1;
        }

        res
    }
    pub fn count_subarrays(mut nums: Vec<i32>, k: i32) -> i64 {
        let mut maxi: i32 = i32::MIN;
        let mut max_count: i32 = 0;
        let n: usize = nums.len();
        for i in 0..n {
            maxi = std::cmp::max(maxi, nums[i]);
            max_count += 1;
        }

        for i in 0..n {
            if nums[i] != maxi {
                nums[i] = 0;
            } else {
                nums[i] = 1;
            }
        }

        Self::atmost(&nums, max_count) - Self::atmost(&nums, k - 1)
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![1, 3, 2, 3, 3];
    let k_1: i32 = 2;
    let expected_1: i64 = 6;
    let output_1: i64 = Solution::count_subarrays(nums_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![1, 4, 2, 1];
    let k_2: i32 = 3;
    let expected_2: i64 = 0;
    let output_2: i64 = Solution::count_subarrays(nums_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
