/*
https://leetcode.com/problems/permutations/

Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.


Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:

Input: nums = [1]
Output: [[1]]


Constraints:

    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of nums are unique.
*/

struct Solution();
impl Solution {
    pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
        if nums.len() == 1 {
            return vec![nums];
        }

        let mut res: Vec<Vec<i32>> = Vec::new();
        for i in 0..nums.len() {
            let mut tmp: Vec<i32> = nums.clone();
            tmp.remove(i);
            let n_1_permuations: Vec<Vec<i32>> = Self::permute(tmp);
            for mut permutation in n_1_permuations {
                permutation.push(nums[i]);
                res.push(permutation);
            }
        }

        res
    }
}

fn main() {
    let nums1: Vec<i32> = vec![1, 2, 3];
    let res1: Vec<Vec<i32>> = Solution::permute(nums1);
    println!("{:#?}", res1);

    let nums2: Vec<i32> = vec![0, 1];
    let res2: Vec<Vec<i32>> = Solution::permute(nums2);
    println!("{:#?}", res2);

    let nums3: Vec<i32> = vec![1];
    let res3: Vec<Vec<i32>> = Solution::permute(nums3);
    println!("{:#?}", res3);
}
