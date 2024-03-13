/*
https://leetcode.com/problems/minimum-window-substring

Given two strings `s` and `t` of lengths `m` and `n` respectively, return *the **minimum window*** ***substring**** of
*`s`* such that every character in *`t`* (**including duplicates**) is included in the window*. If there is no such
substring, return *the empty string *`""`.

The testcases will be generated such that the answer is **unique**.


**Example 1:**

**Input:** s = "ADOBECODEBANC", t = "ABC"
**Output:** "BANC"
**Explanation:** The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

**Example 2:**

**Input:** s = "a", t = "a"
**Output:** "a"
**Explanation:** The entire string s is the minimum window.

**Example 3:**

**Input:** s = "a", t = "aa"
**Output:** ""
**Explanation:** Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.


**Constraints:**

* `m == s.length`
* `n == t.length`
* `1 <= m, n <= 10⁵`
* `s` and `t` consist of uppercase and lowercase English letters.


**Follow up:** Could you find an algorithm that runs in `O(m + n)` time?
*/

use std::collections::HashMap;

struct Solution;
impl Solution {
    fn clear(mp: &mut HashMap<char, usize>) {
        for i in 0..26 {
            mp.insert(char::from(i + 'a' as u8), 0);
        }
        for i in 0..26 {
            mp.insert(char::from(i + 'A' as u8), 0);
        }
    }

    fn check(
        sfreq: &HashMap<char, usize>,
        tfreq: &HashMap<char, usize>,
    ) -> bool {
        let mut c: char;
        for i in 0..26 {
            c = char::from(i + 'a' as u8);
            if tfreq[&c] > sfreq[&c] {
                return false;
            }
        }
        for i in 0..26 {
            c = char::from(i + 'A' as u8);
            if tfreq[&c] > sfreq[&c] {
                return false;
            }
        }

        true
    }

    fn get_frequencies(
        s_chars: &Vec<char>,
        max_len: usize,
        freq: &mut HashMap<char, usize>,
    ) {
        for i in 0..max_len {
            let c: char = s_chars[i];
            freq.insert(c, freq[&c] + 1);
        }
    }

    fn check_window_substring(
        s_chars: &Vec<char>,
        sfreq: &mut HashMap<char, usize>,
        tfreq: &HashMap<char, usize>,
        win_sz: usize,
    ) -> String {
        let m: usize = s_chars.len();
        let mut res: String = String::new();
        if win_sz > m {
            return res;
        }

        Self::clear(sfreq);
        for i in 0..win_sz {
            let c: char = s_chars[i];
            sfreq.insert(c, sfreq[&c] + 1);
        }
        if Self::check(sfreq, tfreq) {
            for i in 0..win_sz {
                let c: char = s_chars[i];
                res.push(c);
            }
            return res;
        }

        if m < 2 {
            return res;
        }

        for i in 1..(m - win_sz + 1) {
            let prev: char = s_chars[i - 1];
            let next: char = s_chars[i + win_sz - 1];
            sfreq.insert(prev, sfreq[&prev] - 1);
            sfreq.insert(next, sfreq[&next] + 1);

            if Self::check(sfreq, tfreq) {
                for j in i..(i + win_sz) {
                    let c: char = s_chars[j];
                    res.push(c);
                }
                return res;
            }
        }

        return res;
    }

    pub fn min_window(s: String, t: String) -> String {
        let m: usize = s.len();
        let n: usize = t.len();
        if n > m {
            return "".to_string();
        }

        let s_chars: Vec<char> = s.chars().collect();
        let t_chars: Vec<char> = t.chars().collect();
        let mut sfreq: HashMap<char, usize> = HashMap::new();
        let mut tfreq: HashMap<char, usize> = HashMap::new();
        Self::clear(&mut sfreq);
        Self::clear(&mut tfreq);
        Self::get_frequencies(&t_chars, n, &mut tfreq);

        if n == m {
            Self::get_frequencies(&s_chars, m, &mut sfreq);

            if Self::check(&sfreq, &tfreq) {
                return s;
            } else {
                return "".to_string();
            }
        }

        let mut low: usize = n;
        let mut high: usize = m;
        let mut mid: usize;
        let mut res: String = "".to_string();

        while low < high {
            mid = low + (high - low) / 2;
            let mid_s: String =
                Self::check_window_substring(&s_chars, &mut sfreq, &tfreq, mid);
            let mid_1s: String =
                Self::check_window_substring(&s_chars, &mut sfreq, &tfreq, mid);
            if mid_s.as_str() != "" && mid_1s.as_str() != "" {
                res = mid_s;
                high = mid;
            } else if mid_s.as_str() == "" && mid_1s.as_str() == "" {
                low = mid + 1;
            } else {
                if mid_s.as_str() != "" {
                    return mid_s.to_string();
                } else {
                    return mid_1s.to_string();
                }
            }
        }

        res
    }
}

fn main() {
    let s_1: String = "ADOBECODEBANC".to_string();
    let t_1: String = "ABC".to_string();
    let expected_1: String = String::from("BANC");
    let output_1: String = Solution::min_window(s_1, t_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let s_2: String = "a".to_string();
    let t_2: String = "a".to_string();
    let expected_2: String = String::from("a");
    let output_2: String = Solution::min_window(s_2, t_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let s_3: String = "abc".to_string();
    let t_3: String = "ac".to_string();
    let expected_3: String = String::from("abc");
    let output_3: String = Solution::min_window(s_3, t_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
