/*
https://leetcode.com/problems/rotting-oranges/

You are given an m x n grid where each cell can have one of three values:

    0 representing an empty cell,
    1 representing a fresh orange, or
    2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.


Example 1:

Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.


Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10
    grid[i][j] is 0, 1, or 2.
*/

use std::cmp::max;
use std::cmp::min;
use std::collections::VecDeque;

struct Solution();

impl Solution {
    pub fn bfs(
        grid: &Vec<Vec<i32>>,
        min_times: &mut Vec<Vec<i32>>,
        bfs_q: &mut VecDeque<(usize, usize, i32)>,
        i: usize,
        j: usize,
        m: usize,
        n: usize,
    ) {
        let mut visited: Vec<Vec<bool>> = vec![vec![false; n]; m];
        let mut curr: (usize, usize, i32);
        bfs_q.push_back((i, j, 0));
        min_times[i][j] = 0;

        while !bfs_q.is_empty() {
            curr = bfs_q.pop_front().unwrap();
            min_times[curr.0][curr.1] = min(min_times[curr.0][curr.1], curr.2);

            if visited[curr.0][curr.1] {
                continue;
            }

            visited[curr.0][curr.1] = true;
            if grid[curr.0][curr.1] == 0 {
                continue;
            }

            if curr.0 > 0 && !visited[curr.0 - 1][curr.1] {
                bfs_q.push_back((curr.0 - 1, curr.1, curr.2 + 1));
            }

            if curr.0 < m - 1 && !visited[curr.0 + 1][curr.1] {
                bfs_q.push_back((curr.0 + 1, curr.1, curr.2 + 1));
            }

            if curr.1 > 0 && !visited[curr.0][curr.1 - 1] {
                bfs_q.push_back((curr.0, curr.1 - 1, curr.2 + 1));
            }

            if curr.1 < n - 1 && !visited[curr.0][curr.1 + 1] {
                bfs_q.push_back((curr.0, curr.1 + 1, curr.2 + 1));
            }
        }
    }

    pub fn no_rot(grid: &Vec<Vec<i32>>, m: usize, n: usize) -> bool {
        let mut no_rot: bool = true;
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 2 {
                    no_rot = false;
                }
            }
        }

        no_rot
    }

    pub fn no_fresh(grid: &Vec<Vec<i32>>, m: usize, n: usize) -> bool {
        let mut no_fresh: bool = true;
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 1 {
                    no_fresh = false;
                }
            }
        }

        no_fresh
    }

    pub fn max_time(grid: &Vec<Vec<i32>>, min_times: &Vec<Vec<i32>>, m: usize, n: usize) -> i32 {
        let mut max_time: i32 = 0;

        for i in 0..m {
            for j in 0..n {
                if grid[i][j] != 0 {
                    max_time = max(max_time, min_times[i][j]);
                }
            }
        }

        if max_time == i32::MAX {
            return -1;
        } else {
            return max_time;
        }
    }

    pub fn oranges_rotting(grid: Vec<Vec<i32>>) -> i32 {
        let m: usize = grid.len();
        let n: usize = grid[0].len();
        let mut min_times: Vec<Vec<i32>> = vec![vec![i32::MAX; n]; m];
        let mut bfs_q: VecDeque<(usize, usize, i32)> = VecDeque::new();

        if Self::no_fresh(&grid, m, n) {
            return 0;
        }

        if Self::no_rot(&grid, m, n) {
            return -1;
        }

        // Let those oranges rot!
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 2 {
                    Self::bfs(&grid, &mut min_times, &mut bfs_q, i, j, m, n);
                }
            }
        }

        return Self::max_time(&grid, &min_times, m, n);
    }
}

fn main() {
    let mut res: i32;
    let grid = vec![vec![2, 1, 1], vec![1, 1, 0], vec![0, 1, 1]];
    let grid2 = vec![vec![2, 1, 1], vec![0, 1, 1], vec![1, 0, 1]];
    let grid3 = vec![vec![0, 2]];

    res = Solution::oranges_rotting(grid);
    assert_eq!(4, res);
    println!("{}", res);

    res = Solution::oranges_rotting(grid2);
    assert_eq!(-1, res);
    println!("{}", res);

    res = Solution::oranges_rotting(grid3);
    assert_eq!(0, res);
    println!("{}", res);
}
