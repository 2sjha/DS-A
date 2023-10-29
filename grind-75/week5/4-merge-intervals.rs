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
    fn overlap(curr: &Vec<i32>, next: &Vec<i32>) -> bool {
        (next[0] <= curr[1]) || (next[1] <= curr[1])
    }

    pub fn merge(mut intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut merged: Vec<Vec<i32>> = Vec::new();
        intervals.sort_by(|a, b| a[0].cmp(&b[0]));

        let mut intervals_iter = intervals.iter_mut();
        let mut curr_interval = intervals_iter.next().unwrap();
        for interval in intervals_iter {
            if Self::overlap(&curr_interval, interval) {
                curr_interval[0] = std::cmp::min(curr_interval[0], interval[0]);
                curr_interval[1] = std::cmp::max(curr_interval[1], interval[1]);
            } else {
                merged.push(curr_interval.to_vec());
                curr_interval = interval;
            }
        }
        merged.push(curr_interval.to_vec());

        merged
    }
}

fn main() {
    let intervals1: Vec<Vec<i32>> = vec![vec![1, 3], vec![2, 6], vec![8, 10], vec![15, 18]];
    let res1: Vec<Vec<i32>> = Solution::merge(intervals1);
    println!("{:?}\n", res1);

    let intervals2: Vec<Vec<i32>> = vec![vec![1, 4], vec![4, 5]];
    let res2: Vec<Vec<i32>> = Solution::merge(intervals2);
    println!("{:?}\n", res2);

    let intervals2: Vec<Vec<i32>> = vec![vec![1, 4], vec![0, 1]];
    let res2: Vec<Vec<i32>> = Solution::merge(intervals2);
    println!("{:?}\n", res2);
}
