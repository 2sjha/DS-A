/*
https://leetcode.com/problems/number-of-islands

Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return *the number of
islands*.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may
assume all four edges of the grid are all surrounded by water.


**Example 1:**

**Input:** grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
**Output:** 1

**Example 2:**

**Input:** grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
**Output:** 3


**Constraints:**

* `m == grid.length`
* `n == grid[i].length`
* `1 <= m, n <= 300`
* `grid[i][j]` is `'0'` or `'1'`.
*/

struct Solution;
impl Solution {
    const DIRECTIONS: [(i32, i32); 4] = [(0, 1), (1, 0), (0, -1), (-1, 0)];
    fn conquer_island(grid: &mut Vec<Vec<char>>, row: usize, col: usize) {
        let m: i32 = grid.len() as i32;
        let n: i32 = grid[0].len() as i32;
        let mut st: Vec<(usize, usize)> = vec![(row, col)];

        while st.len() != 0 {
            let curr: (usize, usize) = st.pop().unwrap();
            grid[curr.0][curr.1] = '-';

            for i in 0..4 {
                let n_i: i32 = curr.0 as i32 + Self::DIRECTIONS[i].0;
                let n_j: i32 = curr.1 as i32 + Self::DIRECTIONS[i].1;

                if n_i < 0 || n_i >= m || n_j < 0 || n_j >= n {
                    continue;
                }

                let n_i: usize = n_i as usize;
                let n_j: usize = n_j as usize;
                if grid[n_i][n_j] == '-' {
                    continue;
                }

                if grid[n_i][n_j] == '0' {
                    grid[n_i][n_j] = '-';
                } else {
                    st.push((n_i, n_j));
                }
            }
        }
    }

    pub fn num_islands(mut grid: Vec<Vec<char>>) -> i32 {
        let m: usize = grid.len();
        let n: usize = grid[0].len();
        let mut islands: i32 = 0;
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == '-' {
                    continue;
                }

                if grid[i][j] == '0' {
                    grid[i][j] = '-';
                } else {
                    Self::conquer_island(&mut grid, i, j);
                    islands += 1;
                }
            }
        }

        islands
    }
}

fn main() {
    let grid_1: Vec<Vec<char>> = vec![
        vec!['1', '1', '1', '1', '0'],
        vec!['1', '1', '0', '1', '0'],
        vec!['1', '1', '0', '0', '0'],
        vec!['0', '0', '0', '0', '0'],
    ];
    let expected_1: i32 = 1;
    let output_1: i32 = Solution::num_islands(grid_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let grid_2: Vec<Vec<char>> = vec![
        vec!['1', '1', '0', '0', '0'],
        vec!['1', '1', '0', '0', '0'],
        vec!['0', '0', '1', '0', '0'],
        vec!['0', '0', '0', '1', '1'],
    ];
    let expected_2: i32 = 3;
    let output_2: i32 = Solution::num_islands(grid_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
