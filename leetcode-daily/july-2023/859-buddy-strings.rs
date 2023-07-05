/*
https://leetcode.com/problems/buddy-strings/

Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.

Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].

    For example, swapping at indices 0 and 2 in "abcd" results in "cbad".


Example 1:

Input: s = "ab", goal = "ba"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.

Example 2:

Input: s = "ab", goal = "ab"
Output: false
Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in "ba" != goal.

Example 3:

Input: s = "aa", goal = "aa"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.


Constraints:

    1 <= s.length, goal.length <= 2 * 10^4
    s and goal consist of lowercase letters.
*/

struct Solution;
impl Solution {
    fn repeating_chars(s: &Vec<char>) -> bool {
        let mut chars: Vec<usize> = vec![0; 26];
        let n: usize = s.len();

        for i in 0..n {
            chars[(s[i] as usize) - 97] += 1;
            if chars[(s[i] as usize) - 97] > 1 {
                return true;
            }
        }

        return false;
    }

    pub fn buddy_strings(s: String, goal: String) -> bool {
        if s.len() != goal.len() {
            return false;
        }

        let n: usize = s.len();
        let mut diff: usize = 0;
        let mut diff_idx: Vec<usize> = Vec::new();

        let s_copy: Vec<char> = s.chars().collect();
        let goal_copy: Vec<char> = goal.chars().collect();

        for i in 0..n {
            if s_copy[i] != goal_copy[i] {
                diff += 1;
                diff_idx.push(i);

                if diff > 2 {
                    break;
                }
            }
        }

        if diff > 2 || diff == 1 {
            return false;
        } else if diff == 2 {
            if s_copy[diff_idx[0]] == goal_copy[diff_idx[1]]
                && s_copy[diff_idx[1]] == goal_copy[diff_idx[0]]
            {
                return true;
            } else {
                return false;
            }
        } else {
            return Self::repeating_chars(&s_copy);
        }
    }
}

fn main() {
    let mut res: bool;

    let s1: String = "ab".to_string();
    let goal1: String = "ba".to_string();
    res = Solution::buddy_strings(s1, goal1);
    println!("{:?}", res);
    assert!(res == true);

    let s2: String = "ab".to_string();
    let goal2: String = "ab".to_string();
    res = Solution::buddy_strings(s2, goal2);
    println!("{:?}", res);
    assert!(res == false);

    let s3: String = "aa".to_string();
    let goal3: String = "aa".to_string();
    res = Solution::buddy_strings(s3, goal3);
    println!("{:?}", res);
    assert!(res == true);
}
