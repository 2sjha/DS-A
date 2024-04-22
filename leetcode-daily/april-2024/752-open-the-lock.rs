/*
https://leetcode.com/problems/open-the-lock

You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: `'0', '1', '2', '3', '4', '5', '6',
'7', '8', '9'`. The wheels can rotate freely and wrap around: for example we can turn `'9'` to be `'0'`, or `'0'` to be
`'9'`. Each move consists of turning one wheel one slot.

The lock initially starts at `'0000'`, a string representing the state of the 4 wheels.

You are given a list of `deadends` dead ends, meaning if the lock displays any of these codes, the wheels of the lock
will stop turning and you will be unable to open it.

Given a `target` representing the value of the wheels that will unlock the lock, return the minimum total number of
turns required to open the lock, or -1 if it is impossible.


**Example 1:**

**Input:** deadends = ["0201","0101","0102","1212","2002"], target = "0202"
**Output:** 6
**Explanation:**
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

**Example 2:**

**Input:** deadends = ["8888"], target = "0009"
**Output:** 1
**Explanation:** We can turn the last wheel in reverse to move from "0000" -> "0009".

**Example 3:**

**Input:** deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
**Output:** -1
**Explanation:** We cannot reach the target without getting stuck.


**Constraints:**

* `1 <= deadends.length <= 500`
* `deadends[i].length == 4`
* `target.length == 4`
* target **will not be** in the list `deadends`.
* `target` and `deadends[i]` consist of digits only.
*/

use std::collections::HashMap;
use std::collections::HashSet;
use std::collections::VecDeque;

struct Solution;
impl Solution {
    fn get_options(s: &String) -> Vec<String> {
        let mut res: Vec<String> = Vec::new();
        for i in 0..4 {
            let mut s1: Vec<char> = s.chars().collect();
            let mut s2: Vec<char> = s.chars().collect();
            let c = s.chars().nth(i).unwrap();
            if c == '0' {
                s1[i] = '1';
                s2[i] = '9';
            } else if c == '9' {
                s1[i] = '0';
                s2[i] = '8';
            } else {
                s1[i] = (c as u8 + 1) as char;
                s2[i] = (c as u8 - 1) as char;
            }

            res.push(s1.into_iter().collect());
            res.push(s2.into_iter().collect());
        }
        res
    }

    fn create_options() -> HashMap<String, Vec<String>> {
        let mut mp: HashMap<String, Vec<String>> = HashMap::new();
        for i in 0..10000 {
            let s: String;
            if i < 10 {
                s = "000".to_string() + &i.to_string();
            } else if i < 100 {
                s = "00".to_string() + &i.to_string();
            } else if i < 1000 {
                s = "0".to_string() + &i.to_string();
            } else {
                s = i.to_string();
            }
            let s_options: Vec<String> = Self::get_options(&s);
            mp.insert(s, s_options);
        }

        mp
    }

    pub fn open_lock(deadends: Vec<String>, target: String) -> i32 {
        let mut visited: HashSet<String> = HashSet::new();
        let mut bfs_q: VecDeque<(String, i32)> = VecDeque::new();
        let mut dead_ends: HashSet<String> = HashSet::new();
        let options: HashMap<String, Vec<String>> = Self::create_options();
        let mut res: i32 = -1;

        for dead in deadends {
            dead_ends.insert(dead);
        }
        if dead_ends.contains("0000") {
            return -1;
        }

        bfs_q.push_back(("0000".to_string(), 0));
        while bfs_q.len() != 0 {
            let curr = bfs_q.pop_front().unwrap();

            if visited.contains(&curr.0) {
                continue;
            }

            if target == curr.0 {
                res = curr.1;
                break;
            } else {
                for o in options.get(&curr.0).unwrap() {
                    if !visited.contains(o) && !dead_ends.contains(o) {
                        bfs_q.push_back((o.clone(), curr.1 + 1));
                    }
                }
            }
            visited.insert(curr.0);
        }

        res
    }
}

fn main() {
    let deadends_1: Vec<String> = vec![
        "0201".to_string(),
        "0101".to_string(),
        "0102".to_string(),
        "1212".to_string(),
        "2002".to_string(),
    ];
    let target_1: String = "0202".to_string();
    let expected_1: i32 = 6;
    let output_1: i32 = Solution::open_lock(deadends_1, target_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let deadends_2: Vec<String> = vec!["8888".to_string()];
    let target_2: String = "0009".to_string();
    let expected_2: i32 = 1;
    let output_2: i32 = Solution::open_lock(deadends_2, target_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let deadends_3: Vec<String> = vec![
        "8887".to_string(),
        "8889".to_string(),
        "8878".to_string(),
        "8898".to_string(),
        "8788".to_string(),
        "8988".to_string(),
        "7888".to_string(),
        "9888".to_string(),
    ];
    let target_3: String = "8888".to_string();
    let expected_3: i32 = -1;
    let output_3: i32 = Solution::open_lock(deadends_3, target_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
