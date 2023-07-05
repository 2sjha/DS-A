/*
https://leetcode.com/problems/find-smallest-letter-greater-than-target/

You are given an array of characters letters that is sorted in non-decreasing order, and a character
target. There are at least two different characters in letters.

Return the smallest character in letters that is lexicographically greater than target. If such a
character does not exist, return the first character in letters.


Example 1:

Input: letters = ["c","f","j"], target = "a"
Output: "c"
Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.

Example 2:

Input: letters = ["c","f","j"], target = "c"
Output: "f"
Explanation: The smallest character that is lexicographically greater than 'c' in letters is 'f'.

Example 3:

Input: letters = ["x","x","y","y"], target = "z"
Output: "x"
Explanation: There are no characters in letters that is lexicographically greater than 'z' so we
return letters[0].


Constraints:

    2 <= letters.length <= 104
    letters[i] is a lowercase English letter.
    letters is sorted in non-decreasing order.
    letters contains at least two different characters.
    target is a lowercase English letter.
*/

struct Solution;
impl Solution {
    pub fn next_greatest_letter(letters: Vec<char>, target: char) -> char {
        for l in letters.iter() {
            if *l > target {
                return *l;
            }
        }

        letters[0]
    }
}

fn main() {
    let mut res: char;

    let letters1: Vec<char> = vec!['c', 'f', 'j'];
    let target1: char = 'a';
    res = Solution::next_greatest_letter(letters1, target1);
    println!("{}", res);
    assert!(res == 'c');

    let letters2: Vec<char> = vec!['c', 'f', 'j'];
    let target2: char = 'c';
    res = Solution::next_greatest_letter(letters2, target2);
    println!("{}", res);
    assert!(res == 'f');

    let letters3: Vec<char> = vec!['x', 'x', 'y', 'y'];
    let target3: char = 'z';
    res = Solution::next_greatest_letter(letters3, target3);
    println!("{}", res);
    assert!(res == 'x');
}