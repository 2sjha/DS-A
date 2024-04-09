/*
https://leetcode.com/problems/time-needed-to-buy-tickets

There are `n` people in a line queuing to buy tickets, where the `0^{th}` person is at the **front** of the line and the
`(n - 1)^{th}` person is at the **back** of the line.

You are given a **0-indexed** integer array `tickets` of length `n` where the number of tickets that the `i^{th}` person
would like to buy is `tickets[i]`.

Each person takes **exactly 1 second** to buy a ticket. A person can only buy **1 ticket at a time** and has to go back
to **the end** of the line (which happens **instantaneously**) in order to buy more tickets. If a person does not have
any tickets left to buy, the person will **leave **the line.

Return *the **time taken** for the person at position *`k`* ****(0-indexed)* ***to finish buying tickets*.


**Example 1:**

**Input:** tickets = [2,3,2], k = 2
**Output:** 6
**Explanation:**
- In the first pass, everyone in the line buys a ticket and the line becomes [1, 2, 1].
- In the second pass, everyone in the line buys a ticket and the line becomes [0, 1, 0].
The person at position 2 has successfully bought 2 tickets and it took 3 + 3 = 6 seconds.

**Example 2:**

**Input:** tickets = [5,1,1,1], k = 0
**Output:** 8
**Explanation:**
- In the first pass, everyone in the line buys a ticket and the line becomes [4, 0, 0, 0].
- In the next 4 passes, only the person in position 0 is buying tickets.
The person at position 0 has successfully bought 5 tickets and it took 4 + 1 + 1 + 1 + 1 = 8 seconds.


**Constraints:**

* `n == tickets.length`
* `1 <= n <= 100`
* `1 <= tickets[i] <= 100`
* `0 <= k < n`
*/

struct Solution;
impl Solution {
    pub fn time_required_to_buy(mut tickets: Vec<i32>, k: i32) -> i32 {
        let n: usize = tickets.len();
        let mut res: i32 = 0;
        let k: usize = k as usize;

        while tickets[k] != 0 {
            for i in 0..n {
                if tickets[i] != 0 {
                    res += 1;
                    tickets[i] = tickets[i] - 1;
                }

                if i == k && tickets[k] == 0 {
                    break;
                }
            }
        }

        res
    }
}

fn main() {
    let tickets_1: Vec<i32> = vec![2, 3, 2];
    let k_1: i32 = 2;
    let expected_1: i32 = 6;
    let output_1: i32 = Solution::time_required_to_buy(tickets_1, k_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let tickets_2: Vec<i32> = vec![5, 1, 1, 1];
    let k_2: i32 = 0;
    let expected_2: i32 = 8;
    let output_2: i32 = Solution::time_required_to_buy(tickets_2, k_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
