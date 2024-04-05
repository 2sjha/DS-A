/*
https://leetcode.com/problems/make-the-string-great

Given a string `s` of lower and upper case English letters.

A good string is a string which doesn't have **two adjacent characters** `s[i]` and `s[i + 1]` where:

* `0 <= i <= s.length - 2`
* `s[i]` is a lower-case letter and `s[i + 1]` is the same letter but in upper-case or **vice-versa**.

To make the string good, you can choose **two adjacent** characters that make the string bad and remove them. You can
keep doing this until the string becomes good.

Return *the string* after making it good. The answer is guaranteed to be unique under the given constraints.

**Notice** that an empty string is also good.


**Example 1:**

**Input:** s = "leEeetcode"
**Output:** "leetcode"
**Explanation:** In the first step, either you choose i = 1 or i = 2, both will result "leEeetcode" to be reduced to "le
etcode".

**Example 2:**

**Input:** s = "abBAcC"
**Output:** ""
**Explanation:** We have many possible scenarios, and all lead to the same answer. For example:
"abBAcC" --> "aAcC" --> "cC" --> ""
"abBAcC" --> "abBA" --> "aA" --> ""

**Example 3:**

**Input:** s = "s"
**Output:** "s"


**Constraints:**

* `1 <= s.length <= 100`
* `s` contains only lower and upper case English letters.
*/

struct Solution;
impl Solution {
    pub fn make_good(mut s: String) -> String {
        loop {
            if s == "".to_string() {
                return s;
            }

            let mut bad: bool = false;
            let mut i: usize = 0;
            let mut res: String = String::new();
            while i < s.len() - 1 {
                if (s.chars().nth(i + 1).unwrap() as i16
                    - s.chars().nth(i).unwrap() as i16)
                    .abs()
                    == ('A' as i16 - 'a' as i16).abs()
                {
                    i += 2;
                    bad = true;
                } else {
                    res.push(s.chars().nth(i).unwrap());
                    i += 1;
                }
            }
            if i == s.len() - 1 {
                res.push(s.chars().nth(i).unwrap())
            }

            if !bad {
                return res;
            } else {
                s = res;
            }
        }
    }
}

fn main() {
    let s_1: String = "leEeetcode".to_string();
    let expected_1: String = String::from("leetcode");
    let output_1: String = Solution::make_good(s_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "abBAcC".to_string();
    let expected_2: String = String::from("");
    let output_2: String = Solution::make_good(s_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let s_3: String = "s".to_string();
    let expected_3: String = String::from("s");
    let output_3: String = Solution::make_good(s_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
