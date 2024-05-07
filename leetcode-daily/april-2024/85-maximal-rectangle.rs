/*
https://leetcode.com/problems/maximal-rectangle

Given a `rows x cols` binary `matrix` filled with `0`'s and `1`'s, find the largest rectangle containing only `1`'s and
return *its area*.


**Example 1:**

**Input:** matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
**Output:** 6
**Explanation:** The maximal rectangle is shown in the above picture.

**Example 2:**

**Input:** matrix = [["0"]]
**Output:** 0

**Example 3:**

**Input:** matrix = [["1"]]
**Output:** 1


**Constraints:**

* `rows == matrix.length`
* `cols == matrix[i].length`
* `1 <= row, cols <= 200`
* `matrix[i][j]` is `'0'` or `'1'`.
*/

struct Solution;
impl Solution {
    fn largest_rectangle_area(heights: &Vec<i32>) -> i32 {
        let n: usize = heights.len();
        let mut i: usize = 0;
        let mut begin: usize;
        let mut st: Vec<(usize, i32)> = Vec::new();
        let mut max_area: i32 = 0;

        while i < n {
            begin = i;
            while !st.is_empty() && heights[i] < st[st.len() - 1].1 {
                max_area = i32::max(
                    max_area,
                    (i - st[st.len() - 1].0) as i32 * st[st.len() - 1].1,
                );
                begin = st[st.len() - 1].0;
                st.pop();
            }
            st.push((begin, heights[i]));
            i += 1;
        }

        while !st.is_empty() {
            max_area = i32::max(
                max_area,
                (i - st[st.len() - 1].0) as i32 * st[st.len() - 1].1,
            );
            begin = st[st.len() - 1].0;
            st.pop();
        }

        max_area
    }

    pub fn maximal_rectangle(matrix: Vec<Vec<char>>) -> i32 {
        let m: usize = matrix.len();
        let n: usize = matrix[0].len();
        let mut heights: Vec<Vec<i32>> = vec![vec![0; n]; m];
        let mut h: i32;

        for j in 0..n {
            for i in 0..m {
                h = 0;
                if matrix[i][j] == '1' {
                    if i > 0 && heights[i - 1][j] > 1 {
                        h = heights[i - 1][j] - 1;
                    } else {
                        let mut k: usize = i;
                        while k < m && matrix[k][j] == '1' {
                            h += 1;
                            k += 1;
                        }
                    }
                }
                heights[i][j] = h;
            }
        }

        let mut max_area: i32 = 0;
        for i in 0..m {
            max_area =
                i32::max(max_area, Self::largest_rectangle_area(&heights[i]));
        }

        max_area
    }
}

fn main() {
    let matrix_1: Vec<Vec<char>> = vec![
        vec!['1', '0', '1', '0', '0'],
        vec!['1', '0', '1', '1', '1'],
        vec!['1', '1', '1', '1', '1'],
        vec!['1', '0', '0', '1', '0'],
    ];
    let expected_1: i32 = 6;
    let output_1: i32 = Solution::maximal_rectangle(matrix_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let matrix_2: Vec<Vec<char>> = vec![vec!['0']];
    let expected_2: i32 = 0;
    let output_2: i32 = Solution::maximal_rectangle(matrix_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let matrix_3: Vec<Vec<char>> = vec![vec!['1']];
    let expected_3: i32 = 1;
    let output_3: i32 = Solution::maximal_rectangle(matrix_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
