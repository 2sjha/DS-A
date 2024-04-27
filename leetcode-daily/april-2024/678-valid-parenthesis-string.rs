/*
https://leetcode.com/problems/valid-parenthesis-string

Given a string `s` containing only three types of characters: `'('`, `')'` and `'*'`, return `true` *if* `s` *is
**valid***.

The following rules define a **valid** string:

* Any left parenthesis `'('` must have a corresponding right parenthesis `')'`.
* Any right parenthesis `')'` must have a corresponding left parenthesis `'('`.
* Left parenthesis `'('` must go before the corresponding right parenthesis `')'`.
* `'*'` could be treated as a single right parenthesis `')'` or a single left parenthesis `'('` or an empty string `""`.


**Example 1:**

**Input:** s = "()"
**Output:** true

**Example 2:**

**Input:** s = "(*)"
**Output:** true

**Example 3:**

**Input:** s = "(*))"
**Output:** true


**Constraints:**

* `1 <= s.length <= 100`
* `s[i]` is `'('`, `')'` or `'*'`.
*/

use std::collections::VecDeque;

struct Solution;
impl Solution {
    pub fn check_valid_string(s: String) -> bool {
        let mut left: Vec<(char, usize)> = Vec::new();
        let mut right: VecDeque<(char, usize)> = VecDeque::new();
        let mut astr: VecDeque<(char, usize)> = VecDeque::new();
        let n: usize = s.len();
        let s_chars: Vec<char> = s.chars().collect();

        for i in 0..n {
            let c: char = s_chars[i];

            if c == '(' {
                left.push((c, i));
            } else if c == ')' {
                if left.len() == 0 {
                    right.push_back((c, i));
                } else {
                    left.pop();
                }
            } else {
                astr.push_back((c, i));
            }
        }

        while left.len() != 0 && astr.len() != 0 {
            let left_top: (char, usize) = *left.last().unwrap();
            let astr_front: (char, usize) = *astr.front().unwrap();
            let astr_back: (char, usize) = *astr.back().unwrap();

            if left_top.1 < astr_front.1 {
                left.pop();
                astr.pop_front();
            } else if left_top.1 < astr_back.1 {
                left.pop();
                astr.pop_back();
            } else {
                break;
            }
        }

        while right.len() != 0 && astr.len() != 0 {
            let right_front: (char, usize) = *right.front().unwrap();
            let astr_front: (char, usize) = *astr.front().unwrap();
            let astr_back: (char, usize) = *astr.back().unwrap();

            if right_front.1 > astr_front.1 {
                right.pop_front();
                astr.pop_front();
            } else if right_front.1 > astr_back.1 {
                right.pop_front();
                astr.pop_back();
            } else {
                break;
            }
        }

        return left.is_empty() && right.is_empty();
    }
}

fn main() {
    let s_1: String = "()".to_string();
    let expected_1: bool = true;
    let output_1: bool = Solution::check_valid_string(s_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "(*)".to_string();
    let expected_2: bool = true;
    let output_2: bool = Solution::check_valid_string(s_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let s_3: String = "(*))".to_string();
    let expected_3: bool = true;
    let output_3: bool = Solution::check_valid_string(s_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
