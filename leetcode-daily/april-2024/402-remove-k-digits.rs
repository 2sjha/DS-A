/*
https://leetcode.com/problems/remove-k-digits

Given string num representing a non-negative integer `num`, and an integer `k`, return *the smallest possible integer
after removing* `k` *digits from* `num`.


**Example 1:**

**Input:** num = "1432219", k = 3
**Output:** "1219"
**Explanation:** Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

**Example 2:**

**Input:** num = "10200", k = 1
**Output:** "200"
**Explanation:** Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

**Example 3:**

**Input:** num = "10", k = 2
**Output:** "0"
**Explanation:** Remove all the digits from the number and it is left with nothing which is 0.


**Constraints:**

* `1 <= k <= num.length <= 10⁵`
* `num` consists of only digits.
* `num` does not have any leading zeros except for the zero itself.
*/

use std::collections::VecDeque;

struct Solution;
impl Solution {
    fn remove_leading_zeroes(num: Vec<char>) -> String {
        let mut i: usize = 0;
        let n: usize = num.len();

        while i < n {
            if num[i] != '0' {
                break;
            }
            i += 1;
        }

        if i == n {
            String::from("0")
        } else {
            let mut res: String = String::new();
            while i < n {
                res.push(num[i]);
                i += 1;
            }
            res
        }
    }

    pub fn remove_kdigits(num: String, k: i32) -> String {
        let mut dq: VecDeque<char> = VecDeque::new();
        let num_chars: Vec<char> = num.chars().collect();
        let n: usize = num.len();
        let mut i: usize = 0;
        let mut del: i32 = 0;

        while i < n {
            if del == k {
                break;
            }

            while !dq.is_empty()
                && del < k
                && *dq.back().unwrap() as u8 > num_chars[i] as u8
            {
                dq.pop_back();
                del += 1;
            }

            dq.push_back(num_chars[i]);
            i += 1;
        }

        if i == n {
            while del < k {
                dq.pop_back();
                del += 1;
            }
        } else {
            while i < n {
                dq.push_back(num_chars[i]);
                i += 1;
            }
        }

        let mut res: Vec<char> = Vec::new();
        while !dq.is_empty() {
            let t = dq.pop_front().unwrap();
            res.push(t);
        }

        Self::remove_leading_zeroes(res)
    }
}

fn main() {
    let num_1: String = "1432219".to_string();
    let k_1: i32 = 3;
    let expected_1: String = String::from("1219");
    let output_1: String = Solution::remove_kdigits(num_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let num_2: String = "10200".to_string();
    let k_2: i32 = 1;
    let expected_2: String = String::from("200");
    let output_2: String = Solution::remove_kdigits(num_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let num_3: String = "10".to_string();
    let k_3: i32 = 2;
    let expected_3: String = String::from("0");
    let output_3: String = Solution::remove_kdigits(num_3, k_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
