/*
https://leetcode.com/problems/subarray-product-less-than-k

Given an array of integers `nums` and an integer `k`, return *the number of contiguous subarrays where the product of
all the elements in the subarray is strictly less than *`k`.


**Example 1:**

**Input:** nums = [10,5,2,6], k = 100
**Output:** 8
**Explanation:** The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

**Example 2:**

**Input:** nums = [1,2,3], k = 0
**Output:** 0


**Constraints:**

* `1 <= nums.length <= 3 * 10⁴`
* `1 <= nums[i] <= 1000`
* `0 <= k <= 10⁶`
*/

struct Solution;
impl Solution {
    pub fn num_subarray_product_less_than_k(nums: Vec<i32>, k: i32) -> i32 {
        if k <= 0 {
            return 0;
        }

        let mut res: i32 = 0;
        let mut product: i32 = 1;
        let mut l: usize = 0;
        let mut r: usize = 0;
        let n: usize = nums.len();

        while r < n {
            product *= nums[r];

            while l <= r && product >= k {
                product /= nums[l];
                l += 1;
            }

            res += (r - l + 1) as i32;
            r += 1;
        }

        res
    }
}

fn main() {
    let nums_1: Vec<i32> = vec![10, 5, 2, 6];
    let k_1: i32 = 100;
    let expected_1: i32 = 8;
    let output_1: i32 = Solution::num_subarray_product_less_than_k(nums_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let nums_2: Vec<i32> = vec![1, 2, 3];
    let k_2: i32 = 0;
    let expected_2: i32 = 0;
    let output_2: i32 = Solution::num_subarray_product_less_than_k(nums_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
