/*
https://leetcode.com/problems/number-of-wonderful-substrings

A **wonderful** string is a string where **at most one** letter appears an **odd** number of times.

* For example, `"ccjjc"` and `"abab"` are wonderful, but `"ab"` is not.

Given a string `word` that consists of the first ten lowercase English letters (`'a'` through `'j'`), return *the
**number of wonderful non-empty substrings** in *`word`*. If the same substring appears multiple times in *`word`*, then
count **each occurrence** separately.*

A **substring** is a contiguous sequence of characters in a string.


**Example 1:**

**Input:** word = "aba"
**Output:** 4
**Explanation:** The four wonderful substrings are underlined below:
- "**a**ba" -> "a"
- "a**b**a" -> "b"
- "ab**a**" -> "a"
- "**aba**" -> "aba"

**Example 2:**

**Input:** word = "aabb"
**Output:** 9
**Explanation:** The nine wonderful substrings are underlined below:
- "**a**abb" -> "a"
- "**aa**bb" -> "aa"
- "**aab**b" -> "aab"
- "**aabb**" -> "aabb"
- "a**a**bb" -> "a"
- "a**abb**" -> "abb"
- "aa**b**b" -> "b"
- "aa**bb**" -> "bb"
- "aab**b**" -> "b"

**Example 3:**

**Input:** word = "he"
**Output:** 2
**Explanation:** The two wonderful substrings are underlined below:
- "he" -> "h"
- "h**e**" -> "e"


**Constraints:**

* `1 <= word.length <= 10⁵`
* `word` consists of lowercase English letters from `'a'` to `'j'`.
*/

struct Solution;
impl Solution {
    fn get_bitmask(freq: &Vec<bool>) -> usize {
        let mut num: usize = 0;
        for i in 0..10 {
            num += freq[9 - i] as usize * usize::pow(2, i as u32);
        }

        num
    }
    pub fn wonderful_substrings(word: String) -> i64 {
        let word: Vec<char> = word.chars().collect();
        let mut bitmasks_count: Vec<u32> = vec![0; 1024];
        let mut freq: Vec<bool> = vec![false; 10];
        let mut res: i64 = 0;
        bitmasks_count[0] = 1;

        for c in word {
            let c_idx: usize = (c as u16 - 'a' as u16) as usize;
            freq[c_idx] = !freq[c_idx];

            let curr_bitmask: usize = Self::get_bitmask(&freq);
            res += bitmasks_count[curr_bitmask] as i64;

            for i in 0..10 {
                freq[i] = !freq[i];

                let one_diff_bitmask: usize = Self::get_bitmask(&freq);
                res += bitmasks_count[one_diff_bitmask] as i64;

                freq[i] = !freq[i];
            }

            bitmasks_count[curr_bitmask] += 1;
        }

        res
    }
}

fn main() {
    let word_1: String = "aba".to_string();
    let expected_1: i64 = 4;
    let output_1: i64 = Solution::wonderful_substrings(word_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let word_2: String = "aabb".to_string();
    let expected_2: i64 = 9;
    let output_2: i64 = Solution::wonderful_substrings(word_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let word_3: String = "he".to_string();
    let expected_3: i64 = 2;
    let output_3: i64 = Solution::wonderful_substrings(word_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
