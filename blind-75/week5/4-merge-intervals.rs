/*
https://leetcode.com/problems/merge-intervals/

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
and return an array of the non-overlapping intervals that cover all the intervals in the input.


Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


Constraints:

    1 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 104
*/

struct Solution();
impl Solution {
    fn overlap(curr: Vec<i32>, next: Vec<i32>) -> bool {
        let curr_end: i32 = curr[1];
        let next_start: i32 = next[0];
        let next_end: i32 = next[1];

        (next_start < curr_end) || (next_end < curr_end)
    }

    pub fn merge(intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut merged: Vec<Vec<i32>> = Vec::new();

        for i in 0..intervals.len() {
            let mut curr_interval: Vec<i32> = intervals[i];
            if i < intervals.len() - 1 {
                let next_interval: Vec<i32> = intervals[i + 1];
                if Self::overlap(curr_interval, next_interval) {
                    curr_interval[0] = std::cmp::min(curr_interval[0], next_interval[0]);
                    curr_interval[1] = std::cmp::max(curr_interval[1], next_interval[1]);
                }
            } else {
                merged.push(curr_interval.to_vec());
            }
        }

        merged
    }
}

fn main() {
    let intervals1: Vec<Vec<i32>> = vec![vec![1, 3], vec![2, 6], vec![8, 10], vec![15, 18]];
    let res1: Vec<Vec<i32>> = Solution::merge(intervals1);
    println!("{:#?}", res1);

    let intervals2: Vec<Vec<i32>> = vec![vec![1, 3], vec![2, 6], vec![8, 10], vec![15, 18]];
    let res2: Vec<Vec<i32>> = Solution::merge(intervals2);
    println!("{:#?}", res2);
}
