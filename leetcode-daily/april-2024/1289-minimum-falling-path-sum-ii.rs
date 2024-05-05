/*
https://leetcode.com/problems/minimum-falling-path-sum-ii

Given an `n x n` integer matrix `grid`, return *the minimum sum of a **falling path with non-zero shifts***.

A **falling path with non-zero shifts** is a choice of exactly one element from each row of `grid` such that no two
elements chosen in adjacent rows are in the same column.


**Example 1:**

**Input:** grid = [[1,2,3],[4,5,6],[7,8,9]]
**Output:** 13
**Explanation:**
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.

**Example 2:**

**Input:** grid = [[7]]
**Output:** 7


**Constraints:**

* `n == grid.length == grid[i].length`
* `1 <= n <= 200`
* `-99 <= grid[i][j] <= 99`
*/

use std::collections::BTreeSet;

struct Solution;
impl Solution {
    pub fn min_falling_path_sum(grid: Vec<Vec<i32>>) -> i32 {
        let n: usize = grid.len();
        let mut sums: Vec<BTreeSet<(i32, usize)>> = vec![BTreeSet::new(); n];

        for j in 0..n {
            sums[n - 1].insert((grid[n - 1][j], j));
        }

        let mut i: i32 = n as i32 - 2;
        while i >= 0 {
            for j in 0..n {
                let mut sums_iter = sums[i as usize + 1].iter();
                let mut min_val: (i32, usize) = *sums_iter.next().unwrap();
                if min_val.1 == j {
                    min_val = *sums_iter.next().unwrap();
                }
                sums[i as usize].insert((grid[i as usize][j] + min_val.0, j));
            }
            i -= 1;
        }

        sums[0].first().unwrap().0
    }
}

fn main() {
    let grid_1: Vec<Vec<i32>> =
        vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]];
    let expected_1: i32 = 13;
    let output_1: i32 = Solution::min_falling_path_sum(grid_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let grid_2: Vec<Vec<i32>> = vec![vec![7]];
    let expected_2: i32 = 7;
    let output_2: i32 = Solution::min_falling_path_sum(grid_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
