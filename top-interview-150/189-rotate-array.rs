/*
https://leetcode.com/problems/rotate-array

Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative.


**Example 1:**

**Input:** nums = [1,2,3,4,5,6,7], k = 3
**Output:** [5,6,7,1,2,3,4]
**Explanation:**
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

**Example 2:**

**Input:** nums = [-1,-100,3,99], k = 2
**Output:** [3,99,-1,-100]
**Explanation:**
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]


**Constraints:**

* `1 <= nums.length <= 10⁵`
* `-2³¹ <= nums[i] <= 2³¹ - 1`
* `0 <= k <= 10⁵`


**Follow up:**

* Try to come up with as many solutions as you can. There are at least **three** different ways to solve this problem.
* Could you do it in-place with `O(1)` extra space?
*/

struct Solution;
impl Solution {
    fn gcd(mut a: usize, mut b: usize) -> usize {
        if a == b {
            return a;
        }
        if b > a {
            std::mem::swap(&mut a, &mut b);
        }
        while b > 0 {
            let temp = a;
            a = b;
            b = temp % b;
        }
        return a;
    }

    fn rotate_elem(
        nums: &mut Vec<i32>,
        n: usize,
        k: usize,
        mut holding_idx: usize,
        mut holding_val: i32,
    ) -> (usize, i32) {
        let rotate_idx: usize = (holding_idx + k) % n;
        let rotate_val: i32 = nums[rotate_idx];

        nums[rotate_idx] = holding_val;
        holding_val = rotate_val;
        holding_idx = rotate_idx;

        (holding_idx, holding_val)
    }

    pub fn rotate(nums: &mut Vec<i32>, k: i32) {
        let n: usize = nums.len();

        if k == 0 {
            return;
        }

        let gcd: usize = Self::gcd(n, k as usize);

        if k != 1 && gcd != 1 {
            for i in 0..gcd as usize {
                let (mut holding_idx, mut holding_val) =
                    Self::rotate_elem(nums, n, k as usize, i, nums[i]);
                while holding_idx != i {
                    (holding_idx, holding_val) = Self::rotate_elem(
                        nums,
                        n,
                        k as usize,
                        holding_idx,
                        holding_val,
                    );
                }
            }
        } else {
            let (mut holding_idx, mut holding_val) =
                Self::rotate_elem(nums, n, k as usize, 0, nums[0]);
            while holding_idx != 0 {
                (holding_idx, holding_val) = Self::rotate_elem(
                    nums,
                    n,
                    k as usize,
                    holding_idx,
                    holding_val,
                );
            }
        }
    }
}

fn main() {
    let mut nums_1: Vec<i32> = vec![1, 2, 3, 4, 5, 6, 7];
    let k_1: i32 = 3;
    let expected_1: Vec<i32> = vec![5, 6, 7, 1, 2, 3, 4];
    Solution::rotate(&mut nums_1, k_1);
    println!("{:?}", nums_1);
    assert!(nums_1 == expected_1);

    let mut nums_2: Vec<i32> = vec![-1, -100, 3, 99];
    let k_2: i32 = 2;
    let expected_2: Vec<i32> = vec![3, 99, -1, -100];
    Solution::rotate(&mut nums_2, k_2);
    println!("{:?}", nums_2);
    assert!(nums_2 == expected_2);

    let mut nums_3: Vec<i32> = vec![1, 2, 3, 4, 5, 6];
    let k_3: i32 = 4;
    let expected_3: Vec<i32> = vec![3, 4, 5, 6, 1, 2];
    Solution::rotate(&mut nums_3, k_3);
    println!("{:?}", nums_3);
    assert!(nums_3 == expected_3);
}
