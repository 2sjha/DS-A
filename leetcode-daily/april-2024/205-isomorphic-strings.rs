/*
https://leetcode.com/problems/isomorphic-strings

Given two strings `s` and `t`, *determine if they are isomorphic*.

Two strings `s` and `t` are isomorphic if the characters in `s` can be replaced to get `t`.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two
characters may map to the same character, but a character may map to itself.


**Example 1:**

**Input:** s = "egg", t = "add"
**Output:** true

**Example 2:**

**Input:** s = "foo", t = "bar"
**Output:** false

**Example 3:**

**Input:** s = "paper", t = "title"
**Output:** true


**Constraints:**

* `1 <= s.length <= 5 * 10⁴`
* `t.length == s.length`
* `s` and `t` consist of any valid ascii character.
*/

struct Solution;
impl Solution {
    pub fn is_isomorphic(s: String, t: String) -> bool {
        let n: usize = s.len();
        if t.len() != n {
            return false;
        }

        let s_chars: Vec<char> = s.chars().collect();
        let t_chars: Vec<char> = t.chars().collect();
        let mut s_t_mapping: Vec<char> = vec!['\0'; 128];
        let mut s_mapped: Vec<bool> = vec![false; 128];
        let mut t_mapped: Vec<bool> = vec![false; 128];
        for i in 0..n {
            if s_t_mapping[s_chars[i] as usize] == '\0' {
                if s_mapped[s_chars[i] as usize] {
                    return false;
                }
                if t_mapped[t_chars[i] as usize] {
                    return false;
                }
                s_t_mapping[s_chars[i] as usize] = t_chars[i];
                s_mapped[s_chars[i] as usize] = true;
                t_mapped[t_chars[i] as usize] = true;
            }

            if s_t_mapping[s_chars[i] as usize] != t_chars[i] {
                return false;
            }
        }

        true
    }
}

fn main() {
    let s_1: String = "egg".to_string();
    let t_1: String = "add".to_string();
    let expected_1: bool = true;
    let output_1: bool = Solution::is_isomorphic(s_1, t_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "foo".to_string();
    let t_2: String = "bar".to_string();
    let expected_2: bool = false;
    let output_2: bool = Solution::is_isomorphic(s_2, t_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let s_3: String = "paper".to_string();
    let t_3: String = "title".to_string();
    let expected_3: bool = true;
    let output_3: bool = Solution::is_isomorphic(s_3, t_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
