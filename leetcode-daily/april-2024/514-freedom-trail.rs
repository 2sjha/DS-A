/*
https://leetcode.com/problems/freedom-trail

In the video game Fallout 4, the quest **"Road to Freedom"** requires players to reach a metal dial called the
**"Freedom Trail Ring"** and use the dial to spell a specific keyword to open the door.

Given a string `ring` that represents the code engraved on the outer ring and another string `key` that represents the
keyword that needs to be spelled, return *the minimum number of steps to spell all the characters in the keyword*.

Initially, the first character of the ring is aligned at the `"12:00"` direction. You should spell all the characters in
`key` one by one by rotating `ring` clockwise or anticlockwise to make each character of the string key aligned at the
`"12:00"` direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character `key[i]`:

1. You can rotate the ring clockwise or anticlockwise by one place, which counts as **one step**. The final purpose of
   the rotation is to align one of `ring`'s characters at the `"12:00"` direction, where this character must equal
   `key[i]`.
2. If the character `key[i]` has been aligned at the `"12:00"` direction, press the center button to spell, which also
   counts as **one step**. After the pressing, you could begin to spell the next character in the key (next stage).
   Otherwise, you have finished all the spelling.


**Example 1:**

**Input:** ring = "godding", key = "gd"
**Output:** 4
**Explanation:**
For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddi
nggo".
Also, we need 1 more step for spelling.
So the final output is 4.

**Example 2:**

**Input:** ring = "godding", key = "godding"
**Output:** 13


**Constraints:**

* `1 <= ring.length, key.length <= 100`
* `ring` and `key` consist of only lower case English letters.
* It is guaranteed that `key` could always be spelled by rotating `ring`.
*/

struct Solution;
impl Solution {
    fn clockwise_steps(
        ring: &Vec<char>,
        ring_idx_top: usize,
        key_char: char,
    ) -> (i32, usize) {
        for i in ring_idx_top..ring.len() {
            if ring[i] == key_char {
                return ((i - ring_idx_top) as i32, i);
            }
        }

        for i in 0..ring_idx_top {
            if ring[i] == key_char {
                return ((ring.len() - ring_idx_top + i) as i32, i);
            }
        }

        (-1, 0)
    }

    fn anti_clockwise_steps(
        ring: &Vec<char>,
        ring_idx_top: usize,
        key_char: char,
    ) -> (i32, usize) {
        for i in (0..=ring_idx_top).rev() {
            if ring[i] == key_char {
                return ((ring_idx_top - i) as i32, i);
            }
        }

        for i in (ring_idx_top..ring.len()).rev() {
            if ring[i] == key_char {
                return ((ring.len() - i + ring_idx_top) as i32, i);
            }
        }

        (-1, 0)
    }

    fn rotate_steps(
        dp: &mut Vec<Vec<i32>>,
        ring: &Vec<char>,
        key: &Vec<char>,
        key_idx: usize,
        ring_idx_top: usize,
    ) -> i32 {
        if key_idx == key.len() {
            return 0;
        }

        if dp[ring_idx_top][key_idx] != 0 {
            return dp[ring_idx_top][key_idx];
        }

        if ring[ring_idx_top] == key[key_idx] {
            dp[ring_idx_top][key_idx] = 1 + Self::rotate_steps(
                dp,
                ring,
                key,
                key_idx + 1,
                ring_idx_top,
            );
        } else {
            let clockwise: (i32, usize) =
                Self::clockwise_steps(ring, ring_idx_top, key[key_idx]);
            let anticlockwise: (i32, usize) =
                Self::anti_clockwise_steps(ring, ring_idx_top, key[key_idx]);

            dp[ring_idx_top][key_idx] = i32::min(
                clockwise.0
                    + 1
                    + Self::rotate_steps(
                        dp,
                        ring,
                        key,
                        key_idx + 1,
                        clockwise.1,
                    ),
                anticlockwise.0
                    + 1
                    + Self::rotate_steps(
                        dp,
                        ring,
                        key,
                        key_idx + 1,
                        anticlockwise.1,
                    ),
            );
        }

        dp[ring_idx_top][key_idx]
    }

    pub fn find_rotate_steps(ring: String, key: String) -> i32 {
        let mut dp: Vec<Vec<i32>> = vec![vec![0; key.len()]; ring.len()];
        let ring: Vec<char> = ring.chars().collect();
        let key: Vec<char> = key.chars().collect();
        Self::rotate_steps(&mut dp, &ring, &key, 0, 0)
    }
}

fn main() {
    let ring_1: String = "godding".to_string();
    let key_1: String = "gd".to_string();
    let expected_1: i32 = 4;
    let output_1: i32 = Solution::find_rotate_steps(ring_1, key_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let ring_2: String = "godding".to_string();
    let key_2: String = "godding".to_string();
    let expected_2: i32 = 13;
    let output_2: i32 = Solution::find_rotate_steps(ring_2, key_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
