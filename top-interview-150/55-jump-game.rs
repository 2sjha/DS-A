/*
https://leetcode.com/problems/jump-game

You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element in
the array represents your maximum jump length at that position.

Return `true`* if you can reach the last index, or *`false`* otherwise*.


**Example 1:**

**Input:** nums = [2,3,1,1,4]
**Output:** true
**Explanation:** Jump 1 step from index 0 to 1, then 3 steps to the last index.

**Example 2:**

**Input:** nums = [3,2,1,0,4]
**Output:** false
**Explanation:** You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossib
le to reach the last index.


**Constraints:**

* `1 <= nums.length <= 10⁴`
* `0 <= nums[i] <= 10⁵`
*/

struct Solution;
impl Solution {
    fn helper(dp: &mut Vec<i32>, nums: &Vec<i32>, idx: usize) -> bool {
        if idx == nums.len() - 1 {
            return true;
        }

        if dp[idx] != -1 {
            return dp[idx] != 0;
        }

        if nums[idx] <= 0 {
            dp[idx] = 0;
            return false;
        }

        let mut jump: bool = false;
        let mut i = idx + 1;
        while i <= idx + (nums[idx] as usize) {
            jump |= Self::helper(dp, nums, i);
            if jump {
                break;
            }
            i+=1;
        }

        if jump {
            dp[idx] = 1;
        } else {
            dp[idx] = 0;
        }

        jump
    }

    pub fn can_jump(nums: Vec<i32>) -> bool {
        let n: usize = nums.len();
        let mut dp: Vec<i32> = vec![-1; n];
        Self::helper(&mut dp, &nums, 0)   
    }
}

fn main() {
	let nums_1: Vec<i32> = vec![2,3,1,1,4];
	let expected_1: bool = true;
	let output_1: bool = Solution::can_jump(nums_1);
	println!("{:?}", output_1);
	assert!(output_1 == expected_1);

	let nums_2: Vec<i32> = vec![3,2,1,0,4];
	let expected_2: bool = false;
	let output_2: bool = Solution::can_jump(nums_2);
	println!("{:?}", output_2);
	assert!(output_2 == expected_2);

}
