/*
https://leetcode.com/problems/n-th-tribonacci-number

The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given `n`, return the value of Tn.


**Example 1:**

**Input:** n = 4
**Output:** 4
**Explanation:**
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

**Example 2:**

**Input:** n = 25
**Output:** 1389537


**Constraints:**

* `0 <= n <= 37`
* The answer is guaranteed to fit within a 32-bit integer, ie. `answer <= 2^31 - 1`.
*/

struct Solution;
impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        let mut t0: i32 = 0;
        let mut t1: i32 = 1;
        let mut t2: i32 = 1;
        if n == 0 {
            t0
        } else if n == 1 {
            t1
        } else if n == 2 {
            t2
        } else {
            let mut t3: i32;
            for _i in 3..=n {
                t3 = t2 + t1 + t0;
                t0 = t1;
                t1 = t2;
                t2 = t3;
            }

            t2
        }
    }
}

fn main() {
    let n_1: i32 = 4;
    let expected_1: i32 = 4;
    let output_1: i32 = Solution::tribonacci(n_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let n_2: i32 = 25;
    let expected_2: i32 = 1389537;
    let output_2: i32 = Solution::tribonacci(n_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
