/*
https://leetcode.com/problems/maximize-the-confusion-of-an-exam/

A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false.
He wants to confuse the students by maximizing the number of consecutive questions with the same
answer (multiple trues or multiple falses in a row).

You are given a string answerKey, where answerKey[i] is the original answer to the ith question.
In addition, you are given an integer k, the maximum number of times you may perform the following operation:

    Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').

Return the maximum number of consecutive 'T's or 'F's in the answer key
after performing the operation at most k times.


Example 1:

Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
There are four consecutive 'T's.

Example 2:

Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.

Example 3:

Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT".
In both cases, there are five consecutive 'T's.


Constraints:

    n == answerKey.length
    1 <= n <= 5 * 10^4
    answerKey[i] is either 'T' or 'F'
    1 <= k <= n
*/

/*
Idea is to have a sliding window, where you count necessary flips,
so all not-flip chars are counted as consecutive by default
When you exceed flip_limit, shift your window rightwards
*/
struct Solution;
impl Solution {
    fn max_consecutive_tf(s: &Vec<char>, k: i32, tf: char) -> i32 {
        let n: i32 = s.len() as i32;
        let mut max_len: i32 = 0;
        let mut i: i32 = 0;
        let mut flips: i32 = 0;
        let mut left: i32 = 0;

        while i < n {
            if s[i as usize] != tf {
                flips += 1;
            }

            while flips > k {
                if s[left as usize] != tf {
                    flips -= 1;
                }
                left += 1;
            }

            max_len = std::cmp::max(max_len, i - left + 1);
            i += 1;
        }

        max_len
    }

    pub fn max_consecutive_answers(answer_key: String, k: i32) -> i32 {
        let s: Vec<char> = answer_key.chars().collect();

        let mut res: i32 = Self::max_consecutive_tf(&s, k, 'T');
        res = std::cmp::max(res, Self::max_consecutive_tf(&s, k, 'F'));

        res
    }
}

fn main() {
    let mut res: i32;
    let mut answer_key: String;
    let mut k: i32;

    answer_key = String::from("TTFF");
    k = 2;
    res = Solution::max_consecutive_answers(answer_key, k);
    println!("{:?}", res);
    assert!(res == 4);

    answer_key = String::from("TFFT");
    k = 1;
    res = Solution::max_consecutive_answers(answer_key, k);
    println!("{:?}", res);
    assert!(res == 3);

    answer_key = String::from("TTFTTFTT");
    k = 1;
    res = Solution::max_consecutive_answers(answer_key, k);
    println!("{:?}", res);
    assert!(res == 5);

    answer_key = String::from("FFFTTFTTFT");
    k = 3;
    res = Solution::max_consecutive_answers(answer_key, k);
    println!("{:?}", res);
    assert!(res == 8);
}
