/*
https://leetcode.com/problems/decode-ways

A message containing letters from `A-Z` can be **encoded** into numbers using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"

To **decode** an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the
mapping above (there may be multiple ways). For example, `"11106"` can be mapped into:

* `"AAJF"` with the grouping `(1 1 10 6)`
* `"KJF"` with the grouping `(11 10 6)`

Note that the grouping `(1 11 06)` is invalid because `"06"` cannot be mapped into `'F'` since `"6"` is different from
`"06"`.

Given a string `s` containing only digits, return *the **number** of ways to **decode** it*.

The test cases are generated so that the answer fits in a **32-bit** integer.


**Example 1:**

**Input:** s = "12"
**Output:** 2
**Explanation:** "12" could be decoded as "AB" (1 2) or "L" (12).

**Example 2:**

**Input:** s = "226"
**Output:** 3
**Explanation:** "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

**Example 3:**

**Input:** s = "06"
**Output:** 0
**Explanation:** "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06").


**Constraints:**

* `1 <= s.length <= 100`
* `s` contains only digits and may contain leading zero(s).
*/

struct Solution;
impl Solution {
    fn decode(dp: &mut Vec<i32>, v: &Vec<char>, idx: usize) -> i32 {
        if (idx == v.len() - 1 && v[idx] != '0') || idx >= v.len() {
            return 1;
        }

        if dp[idx] != -1_000_000 {
            return dp[idx];
        }

        let mut res: i32 = 0;
        if v[idx] >= '3' {
            res = Self::decode(dp, v, idx + 1);
        } else if v[idx] == '0' {
            res = -1_000_000;
        } else if v[idx] == '1' {
            if idx < v.len() - 1 && v[idx + 1] == '0' {
                res = Self::decode(dp, v, idx + 2);
            } else {
                res =
                    Self::decode(dp, v, idx + 1) + Self::decode(dp, v, idx + 2);
            }
        } else if v[idx] == '2' {
            if idx < v.len() - 1 && v[idx + 1] == '0' {
                res = Self::decode(dp, v, idx + 2);
            } else if idx < v.len() - 1 && v[idx + 1] >= '7' {
                res = Self::decode(dp, v, idx + 1);
            } else {
                res =
                    Self::decode(dp, v, idx + 1) + Self::decode(dp, v, idx + 2);
            }
        }

        if res < 0 {
            return 0;
        } else {
            return res;
        }
    }

    pub fn num_decodings(s: String) -> i32 {
        let mut v: Vec<char> = Vec::new();
        let mut dp: Vec<i32> = vec![-1_000_000; s.len()];
        for c in s.chars() {
            v.push(c);
        }

        Self::decode(&mut dp, &v, 0)
    }
}

fn main() {
    let s_1: String = "12".to_string();
    let expected_1: i32 = 2;
    let output_1: i32 = Solution::num_decodings(s_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "226".to_string();
    let expected_2: i32 = 3;
    let output_2: i32 = Solution::num_decodings(s_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let s_3: String = "06".to_string();
    let expected_3: i32 = 0;
    let output_3: i32 = Solution::num_decodings(s_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);

    let s_4: String = "100".to_string();
    let expected_4: i32 = 0;
    let output_4: i32 = Solution::num_decodings(s_4);
    println!("{:?}", output_4);
    assert!(output_4 == expected_4);
}
