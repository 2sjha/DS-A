/*
https://leetcode.com/problems/find-all-groups-of-farmland

You are given a **0-indexed** `m x n` binary matrix `land` where a `0` represents a hectare of forested land and a `1`
represents a hectare of farmland.

To keep the land organized, there are designated rectangular areas of hectares that consist **entirely** of farmland.
These rectangular areas are called **groups**. No two groups are adjacent, meaning farmland in one group is **not**
four-directionally adjacent to another farmland in a different group.

`land` can be represented by a coordinate system where the top left corner of `land` is `(0, 0)` and the bottom right
corner of `land` is `(m-1, n-1)`. Find the coordinates of the top left and bottom right corner of each **group** of
farmland. A **group** of farmland with a top left corner at `(r1, c1)` and a bottom right corner at `(r2, c2)` is
represented by the 4-length array `[r1, c1, r2, c2].`

Return *a 2D array containing the 4-length arrays described above for each **group** of farmland in *`land`*. If there
are no groups of farmland, return an empty array. You may return the answer in **any order***.


**Example 1:**

**Input:** land = [[1,0,0],[0,1,1],[0,1,1]]
**Output:** [[0,0,0,0],[1,1,2,2]]
**Explanation:**
The first group has a top left corner at land[0][0] and a bottom right corner at land[0][0].
The second group has a top left corner at land[1][1] and a bottom right corner at land[2][2].

**Example 2:**

**Input:** land = [[1,1],[1,1]]
**Output:** [[0,0,1,1]]
**Explanation:**
The first group has a top left corner at land[0][0] and a bottom right corner at land[1][1].

**Example 3:**

**Input:** land = [[0]]
**Output:** []
**Explanation:**
There are no groups of farmland.


**Constraints:**

* `m == land.length`
* `n == land[i].length`
* `1 <= m, n <= 300`
* `land` consists of only `0`'s and `1`'s.
* Groups of farmland are **rectangular** in shape.
*/

struct Solution;
impl Solution {
    const DIRECTIONS: [(i32, i32); 4] = [(0, 1), (0, -1), (1, 0), (-1, 0)];
    fn find_coordinates(
        land: &mut Vec<Vec<i32>>,
        row: i32,
        col: i32,
    ) -> Vec<i32> {
        let m: usize = land.len();
        let n: usize = land[0].len();
        let mut st: Vec<(i32, i32)> = vec![(row, col)];
        let mut min_i: i32 = i32::MAX;
        let mut min_j: i32 = i32::MAX;
        let mut max_i: i32 = i32::MIN;
        let mut max_j: i32 = i32::MIN;

        while st.len() != 0 {
            let curr: (i32, i32) = st.pop().unwrap();
            land[curr.0 as usize][curr.1 as usize] = 2;
            min_i = i32::min(min_i, curr.0);
            min_j = i32::min(min_j, curr.1);
            max_i = i32::max(max_i, curr.0);
            max_j = i32::max(max_j, curr.1);

            for i in 0..4 {
                let n_i: i32 = curr.0 + Self::DIRECTIONS[i].0;
                let n_j: i32 = curr.1 + Self::DIRECTIONS[i].1;

                if n_i < 0 || n_i >= m as i32 || n_j < 0 || n_j >= n as i32 {
                    continue;
                }

                if land[n_i as usize][n_j as usize] == 2
                    || land[n_i as usize][n_j as usize] == 0
                {
                    continue;
                } else {
                    st.push((n_i, n_j));
                }
            }
        }

        vec![min_i, min_j, max_i, max_j]
    }

    pub fn find_farmland(mut land: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let m: usize = land.len();
        let n: usize = land[0].len();
        let mut res: Vec<Vec<i32>> = Vec::new();

        for i in 0..m {
            for j in 0..n {
                if land[i][j] == 0 || land[i][j] == 2 {
                    continue;
                } else {
                    res.push(Self::find_coordinates(
                        &mut land, i as i32, j as i32,
                    ));
                }
            }
        }

        res
    }
}

fn main() {
    let land_1: Vec<Vec<i32>> =
        vec![vec![1, 0, 0], vec![0, 1, 1], vec![0, 1, 1]];
    let expected_1: Vec<Vec<i32>> = vec![vec![0, 0, 0, 0], vec![1, 1, 2, 2]];
    let output_1: Vec<Vec<i32>> = Solution::find_farmland(land_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let land_2: Vec<Vec<i32>> = vec![vec![1, 1], vec![1, 1]];
    let expected_2: Vec<Vec<i32>> = vec![vec![0, 0, 1, 1]];
    let output_2: Vec<Vec<i32>> = Solution::find_farmland(land_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let land_3: Vec<Vec<i32>> = vec![vec![0]];
    let expected_3: Vec<Vec<i32>> = vec![];
    let output_3: Vec<Vec<i32>> = Solution::find_farmland(land_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
