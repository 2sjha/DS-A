/*
https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses

A string is a **valid parentheses string** (denoted **VPS**) if it meets one of the following:

* It is an empty string `""`, or a single character not equal to `"("` or `")"`,
* It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are **VPS**'s, or
* It can be written as `(A)`, where `A` is a **VPS**.

We can similarly define the **nesting depth** `depth(S)` of any VPS `S` as follows:

* `depth("") = 0`
* `depth(C) = 0`, where `C` is a string with a single character not equal to `"("` or `")"`.
* `depth(A + B) = max(depth(A), depth(B))`, where `A` and `B` are **VPS**'s.
* `depth("(" + A + ")") = 1 + depth(A)`, where `A` is a **VPS**.

For example, `""`, `"()()"`, and `"()(()())"` are **VPS**'s (with nesting depths 0, 1, and 2), and `")("` and `"(()"`
are not **VPS**'s.

Given a **VPS** represented as string `s`, return *the **nesting depth** of *`s`.


**Example 1:**

**Input:** s = "(1+(2*3)+((8)/4))+1"
**Output:** 3
**Explanation:** Digit 8 is inside of 3 nested parentheses in the string.

**Example 2:**

**Input:** s = "(1)+((2))+(((3)))"
**Output:** 3


**Constraints:**

* `1 <= s.length <= 100`
* `s` consists of digits `0-9` and characters `'+'`, `'-'`, `'*'`, `'/'`, `'('`, and `')'`.
* It is guaranteed that parentheses expression `s` is a **VPS**.
*/

struct Solution;
impl Solution {
    pub fn max_depth(s: String) -> i32 {
        let mut res: i32 = 0;
        let mut nest: i32 = 0;
        for c in s.chars() {
            if c == '(' {
                nest += 1;
                res = std::cmp::max(res, nest);
            } else if c == ')' {
                nest -= 1;
            }
        }

        res
    }
}

fn main() {
    let s_1: String = "(1+(2*3)+((8)/4))+1".to_string();
    let expected_1: i32 = 3;
    let output_1: i32 = Solution::max_depth(s_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "(1)+((2))+(((3)))".to_string();
    let expected_2: i32 = 3;
    let output_2: i32 = Solution::max_depth(s_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
