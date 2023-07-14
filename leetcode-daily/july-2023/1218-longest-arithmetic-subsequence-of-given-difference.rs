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

// The idea is that you cant know which numbers are gonna be there and finding a subsequence would take more time.
// So you make a dp array of all possible numbers -10^4 to 10^4 as mentioned in the constraints. [this is kinda cheating but ok]
// Added new function which does not use this trick, but it somehow does worse in time and memory performance. lol.
use std::collections::HashMap;

struct Solution;
impl Solution {
    pub fn longest_subsequence(arr: Vec<i32>, difference: i32) -> i32 {
        let n = arr.len();
        let mut dp = vec![0; 20001];

        let mut t: i32;
        let mut u: i32;

        for i in 0..n {
            t = arr[i] + 10000;
            u = t - difference;

            if u >= 0 && u < 20000 {
                dp[t as usize] = 1 + dp[u as usize];
            } else {
                dp[t as usize] = 1;
            }
        }

        let mut max = 1;
        for i in 0..n {
            t = arr[i] + 10000;
            max = std::cmp::max(max, dp[t as usize]);
        }

        max
    }

    pub fn longest_subsequence_2(arr: Vec<i32>, difference: i32) -> i32 {
        let n: usize = arr.len();
        let mut dp: Vec<i32> = vec![0; n];
        let mut s: HashMap<i32, usize> = HashMap::new();

        let mut pushed: bool;
        for i in 0..n {
            if !s.contains_key(&(arr[i])) {
                s.insert(arr[i], i);
                pushed = true;
            } else {
                pushed = false;
            }

            if s.contains_key(&(arr[i] - difference)) {
                dp[i] = 1 + dp[s[&(arr[i] - difference)]];
            } else {
                dp[i] = 1;
            }

            if !pushed {
                s.insert(arr[i], i);
            }
        }

        let mut max: i32 = 1;
        for i in 0..n {
            max = std::cmp::max(max, dp[i]);
        }

        max
    }
}

fn main() {
    let mut res: i32;
    let mut nums: Vec<i32>;
    let mut diff: i32;

    nums = vec![1, 2, 3, 4];
    diff = 1;
    res = Solution::longest_subsequence(nums, diff);
    println!("{:?}", res);
    assert!(res == 4);

    nums = vec![1, 3, 5, 7];
    diff = 1;
    res = Solution::longest_subsequence_2(nums, diff);
    println!("{:?}", res);
    assert!(res == 1);

    nums = vec![1, 5, 7, 8, 5, 3, 4, 2, 1];
    diff = -2;
    res = Solution::longest_subsequence_2(nums, diff);
    println!("{:?}", res);
    assert!(res == 4);
}
