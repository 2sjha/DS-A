/*
https://leetcode.com/problems/insert-interval

You are given an array of non-overlapping intervals `intervals` where `intervals[i] = [starti, endi]` represent the
start and the end of the `i^{th}` interval and `intervals` is sorted in ascending order by `starti`. You are also given
an interval `newInterval = [start, end]` that represents the start and end of another interval.

Insert `newInterval` into `intervals` such that `intervals` is still sorted in ascending order by `starti` and
`intervals` still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return `intervals`* after the insertion*.

**Note** that you don't need to modify `intervals` in-place. You can make a new array and return it.


**Example 1:**

**Input:** intervals = [[1,3],[6,9]], newInterval = [2,5]
**Output:** [[1,5],[6,9]]

**Example 2:**

**Input:** intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
**Output:** [[1,2],[3,10],[12,16]]
**Explanation:** Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].


**Constraints:**

* `0 <= intervals.length <= 10⁴`
* `intervals[i].length == 2`
* `0 <= starti <= endi <= 10⁵`
* `intervals` is sorted by `starti` in **ascending** order.
* `newInterval.length == 2`
* `0 <= start <= end <= 10⁵`
*/

struct Solution;
impl Solution {
    fn overlap(interval_a: &Vec<i32>, interval_b: &Vec<i32>) -> bool {
        // Symmetric merge check
        // A[0]--------------A[1]
        //        B[0] --------------B[1]
        (interval_b[0] >= interval_a[0] && interval_b[0] <= interval_a[1])
            || (interval_a[0] >= interval_b[0]
                && interval_a[0] <= interval_b[1])
    }

    fn merge_intervals(interval: &Vec<i32>, merged_interval: &mut Vec<i32>) {
        merged_interval[0] = i32::min(merged_interval[0], interval[0]);
        merged_interval[1] = i32::max(merged_interval[1], interval[1]);
    }

    pub fn insert(
        intervals: Vec<Vec<i32>>,
        new_interval: Vec<i32>,
    ) -> Vec<Vec<i32>> {
        let mut new_intervals: Vec<Vec<i32>> = Vec::new();
        let mut merged_interval: Vec<i32> = new_interval.clone();
        let n: usize = intervals.len();

        for i in 0..n {
            // Keep a running merged interval and check its overlap with current interval
            // If yes merge intervals
            if Self::overlap(&intervals[i], &merged_interval) {
                Self::merge_intervals(&intervals[i], &mut merged_interval);
            } else {
                // If merged interval doesnt overlap then check if it starts earlier than current interval
                // because final list must also be sorted.
                if merged_interval[0] < intervals[i][0] {
                    // If yes push both
                    new_intervals.push(merged_interval.clone());
                    new_intervals.push(intervals[i].clone());
                    // Mark that this merged interval has been pushed and it shouldnt be pushed again
                    merged_interval[0] = 1_000_01;
                } else {
                    new_intervals.push(intervals[i].clone());
                }
            }
        }
        if merged_interval[0] != 1_000_01 {
            new_intervals.push(merged_interval);
        }

        new_intervals
    }
}

fn main() {
    let intervals_1: Vec<Vec<i32>> = vec![vec![1, 3], vec![6, 9]];
    let new_interval_1: Vec<i32> = vec![2, 5];
    let expected_1: Vec<Vec<i32>> = vec![vec![1, 5], vec![6, 9]];
    let output_1: Vec<Vec<i32>> = Solution::insert(intervals_1, new_interval_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let intervals_2: Vec<Vec<i32>> = vec![
        vec![1, 2],
        vec![3, 5],
        vec![6, 7],
        vec![8, 10],
        vec![12, 16],
    ];
    let new_interval_2: Vec<i32> = vec![4, 8];
    let expected_2: Vec<Vec<i32>> = vec![vec![1, 2], vec![3, 10], vec![12, 16]];
    let output_2: Vec<Vec<i32>> = Solution::insert(intervals_2, new_interval_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
