/*
https://leetcode.com/problems/longest-ideal-subsequence

You are given a string `s` consisting of lowercase letters and an integer `k`. We call a string `t` **ideal** if the
following conditions are satisfied:

* `t` is a **subsequence** of the string `s`.
* The absolute difference in the alphabet order of every two **adjacent** letters in `t` is less than or equal to `k`.

Return *the length of the **longest** ideal string*.

A **subsequence** is a string that can be derived from another string by deleting some or no characters without changing
the order of the remaining characters.

**Note** that the alphabet order is not cyclic. For example, the absolute difference in the alphabet order of `'a'` and
`'z'` is `25`, not `1`.


**Example 1:**

**Input:** s = "acfgbd", k = 2
**Output:** 4
**Explanation:** The longest ideal string is "acbd". The length of this string is 4, so 4 is returned.
Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet order.

**Example 2:**

**Input:** s = "abcd", k = 3
**Output:** 4
**Explanation:** The longest ideal string is "abcd". The length of this string is 4, so 4 is returned.


**Constraints:**

* `1 <= s.length <= 10⁵`
* `0 <= k <= 25`
* `s` consists of lowercase English letters.
*/

struct Solution;
impl Solution {
    fn get_char_idx(last_char: char) -> usize {
        if last_char == '.' {
            0
        } else {
            (last_char as u8 - 'a' as u8 + 1) as usize
        }
    }

    pub fn longest_ideal_string(s: String, k: i32) -> i32 {
        let n: usize = s.len();
        let s_chars: Vec<char> = s.chars().collect();
        let mut dp: Vec<Vec<i32>> = vec![vec![0; 27]; n + 1];
        for i in (0..=n - 1).rev() {
            let s_idx_char: char = s_chars[i];
            for j in 0..=26 {
                let last_char: char;
                if j == 0 {
                    last_char = '.';
                } else {
                    last_char = ('a' as u8 + j - 1) as char;
                }

                if last_char != '.'
                    && i16::abs(last_char as i16 - s_idx_char as i16) > k as i16
                {
                    dp[i][j as usize] = dp[i + 1][j as usize];
                } else {
                    dp[i][j as usize] = i32::max(
                        dp[i + 1][j as usize],
                        1 + dp[i + 1][Self::get_char_idx(s_idx_char)],
                    );
                }
            }
        }

        dp[0][0]
    }
}

fn main() {
    let s_1: String = "acfgbd".to_string();
    let k_1: i32 = 2;
    let expected_1: i32 = 4;
    let output_1: i32 = Solution::longest_ideal_string(s_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "abcd".to_string();
    let k_2: i32 = 3;
    let expected_2: i32 = 4;
    let output_2: i32 = Solution::longest_ideal_string(s_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
