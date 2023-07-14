/*
https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference

Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.

A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.


Example 1:

Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].

Example 2:

Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.

Example 3:

Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].


Constraints:

    1 <= arr.length <= 10^5
    -10^4 <= arr[i], difference <= 10^4
*/

struct Solution;
impl Solution {
    pub fn longest_subsequence(arr: Vec<i32>, difference: i32) -> i32 {
        let n = arr.len();
        let mut dp = vec![0; 40001];

        let mut t: i32;
        let mut u: i32;

        for i in 0..n {
            t = arr[i] + 20000;
            u = t - difference;
            dp[t as usize] = 1 + dp[u as usize];
        }

        let mut max = 1;
        for i in 0..n {
            t = arr[i] + 20000;
            max = std::cmp::max(max, dp[t as usize]);
        }

        max
    }
}

fn main() {
    let mut res: i32;
    let mut nums: Vec<i32>;
    let mut diff: i32;

    nums = vec![1,2,3,4];
    diff = 1;
    res = Solution::longest_subsequence(nums, diff);
    println!("{:?}", res);
    assert!(res == 4);

    nums = vec![1,3,5,7];
    diff = 1;
    res = Solution::longest_subsequence(nums, diff);
    println!("{:?}", res);
    assert!(res == 1);

    nums = vec![1,5,7,8,5,3,4,2,1];
    diff = -2;
    res = Solution::longest_subsequence(nums, diff);
    println!("{:?}", res);
    assert!(res == 4);
}
