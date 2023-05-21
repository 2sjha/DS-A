/*
https://leetcode.com/problems/number-of-islands/

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.


Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1


Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3


Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.
*/

use std::collections::VecDeque;

struct Solution();

impl Solution {
    pub fn bfs(
        grid: &Vec<Vec<char>>,
        visited: &mut Vec<Vec<bool>>,
        bfs_q: &mut VecDeque<(usize, usize)>,
        i: usize,
        j: usize,
        m: usize,
        n: usize,
    ) {
        let mut curr: (usize, usize);
        bfs_q.push_back((i, j));

        while !bfs_q.is_empty() {
            curr = bfs_q.pop_front().unwrap();

            if visited[curr.0][curr.1] {
                continue;
            }

            visited[curr.0][curr.1] = true;
            if grid[curr.0][curr.1] == '0' {
                continue;
            }

            if curr.0 > 0 && !visited[curr.0 - 1][curr.1] {
                bfs_q.push_back((curr.0 - 1, curr.1));
            }

            if curr.0 < m - 1 && !visited[curr.0 + 1][curr.1] {
                bfs_q.push_back((curr.0 + 1, curr.1));
            }

            if curr.1 > 0 && !visited[curr.0][curr.1 - 1] {
                bfs_q.push_back((curr.0, curr.1 - 1));
            }

            if curr.1 < n - 1 && !visited[curr.0][curr.1 + 1] {
                bfs_q.push_back((curr.0, curr.1 + 1));
            }
        }
    }

    pub fn num_islands(grid: Vec<Vec<char>>) -> i32 {
        let mut num_islands: i32 = 0;
        let m: usize = grid.len();
        let n: usize = grid[0].len();
        let mut visited: Vec<Vec<bool>> = vec![vec![false; n]; m];
        let mut bfs_q: VecDeque<(usize, usize)> = VecDeque::new();

        for i in 0..m {
            for j in 0..n {
                if visited[i][j] {
                    continue;
                }

                if grid[i][j] == '0' {
                    visited[i][j] = true;
                } else if grid[i][j] == '1' {
                    Self::bfs(&grid, &mut visited, &mut bfs_q, i, j, m, n);
                    num_islands += 1;
                }
            }
        }

        num_islands
    }
}

fn main() {
    let mut res: i32;
    let grid = vec![
        vec!['1', '1', '1', '1', '0'],
        vec!['1', '1', '0', '1', '0'],
        vec!['1', '1', '0', '0', '0'],
        vec!['0', '0', '0', '0', '0'],
    ];
    let grid2 = vec![
        vec!['1', '1', '0', '0', '0'],
        vec!['1', '1', '0', '0', '0'],
        vec!['0', '0', '1', '0', '0'],
        vec!['0', '0', '0', '1', '1'],
    ];
    let grid3 = vec![
        vec![
            '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1',
            '0', '1', '1',
        ],
        vec![
            '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1',
            '1', '1', '0',
        ],
        vec![
            '1', '0', '1', '1', '1', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0',
            '1', '1', '1',
        ],
        vec![
            '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1',
            '0', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '0',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1',
            '1', '1', '0',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1',
            '1', '0', '0',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
        vec![
            '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
            '1', '1', '1',
        ],
    ];

    res = Solution::num_islands(grid);
    assert_eq!(2, res);
    println!("{}", res);

    res = Solution::num_islands(grid2);
    assert_eq!(3, res);
    println!("{}", res);

    res = Solution::num_islands(grid3);
    assert_eq!(1, res);
    println!("{}", res);
}
