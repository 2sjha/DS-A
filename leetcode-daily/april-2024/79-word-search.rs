/*
https://leetcode.com/problems/word-search

Given an `m x n` grid of characters `board` and a string `word`, return `true` *if* `word` *exists in the grid*.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or
vertically neighboring. The same letter cell may not be used more than once.


**Example 1:**

**Input:** board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
**Output:** true

**Example 2:**

**Input:** board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
**Output:** true

**Example 3:**

**Input:** board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
**Output:** false


**Constraints:**

* `m == board.length`
* `n = board[i].length`
* `1 <= m, n <= 6`
* `1 <= word.length <= 15`
* `board` and `word` consists of only lowercase and uppercase English letters.


**Follow up:** Could you use search pruning to make your solution faster with a larger `board`?
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    const DIRECTIONS: [[i32; 2]; 4] = [[0, 1], [0, -1], [1, 0], [-1, 0]];

    fn not_found(
        visited: &mut HashMap<(usize, usize), bool>,
        row: usize,
        col: usize,
    ) -> bool {
        visited.get(&(row, col)).is_none()
            || !*visited.get(&(row, col)).unwrap()
    }

    fn search(
        board: &Vec<Vec<char>>,
        visited: &mut HashMap<(usize, usize), bool>,
        row: usize,
        col: usize,
        m: usize,
        n: usize,
        word: &String,
        idx: usize,
        wordlen: usize,
    ) -> bool {
        if idx == wordlen - 1 {
            return true;
        }

        let mut res: bool = false;
        visited.insert((row, col), true);
        for dir in Self::DIRECTIONS {
            if row as i32 + dir[0] < 0 || row as i32 + dir[0] >= m as i32 {
                continue;
            }
            if col as i32 + dir[1] < 0 || col as i32 + dir[1] >= n as i32 {
                continue;
            }

            if board[(row as i32 + dir[0]) as usize]
                [(col as i32 + dir[1]) as usize]
                == word.chars().nth(idx + 1).unwrap()
                && Self::not_found(
                    visited,
                    (row as i32 + dir[0]) as usize,
                    (col as i32 + dir[1]) as usize,
                )
            {
                res |= Self::search(
                    board,
                    visited,
                    (row as i32 + dir[0]) as usize,
                    (col as i32 + dir[1]) as usize,
                    m,
                    n,
                    word,
                    idx + 1,
                    wordlen,
                );
            }
        }

        visited.insert((row, col), false);
        res
    }

    pub fn exist(board: Vec<Vec<char>>, word: String) -> bool {
        let m: usize = board.len();
        let n: usize = board[0].len();
        let wordlen: usize = word.len();
        let mut visited: HashMap<(usize, usize), bool> = HashMap::new();
        let mut res: bool = false;

        for i in 0..m {
            for j in 0..n {
                if board[i][j] == word.chars().nth(0).unwrap() {
                    if Self::search(
                        &board,
                        &mut visited,
                        i,
                        j,
                        m,
                        n,
                        &word,
                        0,
                        wordlen,
                    ) {
                        res = true;
                        break;
                    }
                }
            }
        }

        res
    }
}

fn main() {
    let board_1: Vec<Vec<char>> = vec![
        vec!['A', 'B', 'C', 'E'],
        vec!['S', 'F', 'C', 'S'],
        vec!['A', 'D', 'E', 'E'],
    ];
    let word_1: String = "ABCCED".to_string();
    let expected_1: bool = true;
    let output_1: bool = Solution::exist(board_1, word_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let board_2: Vec<Vec<char>> = vec![
        vec!['A', 'B', 'C', 'E'],
        vec!['S', 'F', 'C', 'S'],
        vec!['A', 'D', 'E', 'E'],
    ];
    let word_2: String = "SEE".to_string();
    let expected_2: bool = true;
    let output_2: bool = Solution::exist(board_2, word_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let board_3: Vec<Vec<char>> = vec![
        vec!['A', 'B', 'C', 'E'],
        vec!['S', 'F', 'C', 'S'],
        vec!['A', 'D', 'E', 'E'],
    ];
    let word_3: String = "ABCB".to_string();
    let expected_3: bool = false;
    let output_3: bool = Solution::exist(board_3, word_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
