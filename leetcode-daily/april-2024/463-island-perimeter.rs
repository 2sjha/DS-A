/*
https://leetcode.com/problems/island-perimeter

You are given `row x col` `grid` representing a map where `grid[i][j] = 1` represents land and `grid[i][j] = 0`
represents water.

Grid cells are connected **horizontally/vertically** (not diagonally). The `grid` is completely surrounded by water, and
there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a
square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the
island.


**Example 1:**

**Input:** grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
**Output:** 16
**Explanation:** The perimeter is the 16 yellow stripes in the image above.

**Example 2:**

**Input:** grid = [[1]]
**Output:** 4

**Example 3:**

**Input:** grid = [[1,0]]
**Output:** 4


**Constraints:**

* `row == grid.length`
* `col == grid[i].length`
* `1 <= row, col <= 100`
* `grid[i][j]` is `0` or `1`.
* There is exactly one island in `grid`.
*/

struct Solution;
impl Solution {
    pub fn island_perimeter(grid: Vec<Vec<i32>>) -> i32 {
        let directions: [(i32, i32); 4] = [(0, 1), (0, -1), (1, 0), (-1, 0)];
        let mut perimeter: i32 = 0;
        let m: usize = grid.len();
        let n: usize = grid[0].len();
        let mut n_i: i32;
        let mut n_j: i32;

        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 1 {
                    for dir in &directions {
                        n_i = i as i32 + dir.0;
                        n_j = j as i32 + dir.1;

                        if n_i < 0
                            || n_i >= m as i32
                            || n_j < 0
                            || n_j >= n as i32
                            || grid[n_i as usize][n_j as usize] == 0
                        {
                            perimeter += 1
                        }
                    }
                }
            }
        }

        perimeter
    }
}

fn main() {
    let grid_1: Vec<Vec<i32>> = vec![
        vec![0, 1, 0, 0],
        vec![1, 1, 1, 0],
        vec![0, 1, 0, 0],
        vec![1, 1, 0, 0],
    ];
    let expected_1: i32 = 16;
    let output_1: i32 = Solution::island_perimeter(grid_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let grid_2: Vec<Vec<i32>> = vec![vec![1]];
    let expected_2: i32 = 4;
    let output_2: i32 = Solution::island_perimeter(grid_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let grid_3: Vec<Vec<i32>> = vec![vec![1, 0]];
    let expected_3: i32 = 4;
    let output_3: i32 = Solution::island_perimeter(grid_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
