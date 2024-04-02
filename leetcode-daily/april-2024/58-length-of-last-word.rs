/*
https://leetcode.com/problems/length-of-last-word

Given a string `s` consisting of words and spaces, return *the length of the **last** word in the string.*

A **word** is a maximal substring consisting of non-space characters only.


**Example 1:**

**Input:** s = "Hello World"
**Output:** 5
**Explanation:** The last word is "World" with length 5.

**Example 2:**

**Input:** s = "   fly me   to   the moon  "
**Output:** 4
**Explanation:** The last word is "moon" with length 4.

**Example 3:**

**Input:** s = "luffy is still joyboy"
**Output:** 6
**Explanation:** The last word is "joyboy" with length 6.


**Constraints:**

* `1 <= s.length <= 10⁴`
* `s` consists of only English letters and spaces `' '`.
* There will be at least one word in `s`.
*/

struct Solution;
impl Solution {
    pub fn length_of_last_word(s: String) -> i32 {
        let mut len: usize = 0;
        let mut prev: usize = 0;
        for c in s.chars() {
            if c == ' ' {
                if len != 0 {
                    prev = len;
                }
                len = 0;
            } else {
                len += 1;
            }
        }

        if len != 0 {
            len as i32
        } else {
            prev as i32
        }
    }
}

fn main() {
    let s_1: String = "Hello World".to_string();
    let expected_1: i32 = 5;
    let output_1: i32 = Solution::length_of_last_word(s_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "   fly me   to   the moon  ".to_string();
    let expected_2: i32 = 4;
    let output_2: i32 = Solution::length_of_last_word(s_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let s_3: String = "luffy is still joyboy".to_string();
    let expected_3: i32 = 6;
    let output_3: i32 = Solution::length_of_last_word(s_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
