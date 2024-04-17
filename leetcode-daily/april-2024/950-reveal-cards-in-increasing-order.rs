/*
https://leetcode.com/problems/reveal-cards-in-increasing-order

You are given an integer array `deck`. There is a deck of cards where every card has a unique integer. The integer on
the `i^{th}` card is `deck[i]`.

You can order the deck in any order you want. Initially, all the cards start face down (unrevealed) in one deck.

You will do the following steps repeatedly until all cards are revealed:

1. Take the top card of the deck, reveal it, and take it out of the deck.
2. If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.

Return *an ordering of the deck that would reveal the cards in increasing order*.

**Note** that the first entry in the answer is considered to be the top of the deck.


**Example 1:**

**Input:** deck = [17,13,11,2,3,5,7]
**Output:** [2,13,3,11,5,17,7]
**Explanation:**
We get the deck in the order [17,13,11,2,3,5,7] (this order does not matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.

**Example 2:**

**Input:** deck = [1,1000]
**Output:** [1,1000]


**Constraints:**

* `1 <= deck.length <= 1000`
* `1 <= deck[i] <= 10⁶`
* All the values of `deck` are **unique**.
*/

use std::collections::VecDeque;

struct Solution;
impl Solution {
    pub fn deck_revealed_increasing(mut deck: Vec<i32>) -> Vec<i32> {
        let n: usize = deck.len();
        deck.sort();

        if n <= 2 {
            return deck;
        }

        let mut reveal_order: Vec<usize> = vec![0; n];
        let mut res: Vec<i32> = vec![0; n];
        let mut dq: VecDeque<usize> = VecDeque::new();

        for i in 0..n {
            dq.push_back(i);
        }

        let mut i: usize = 0;
        while dq.len() != 0 {
            reveal_order[i] = *dq.front().unwrap();
            dq.pop_front();
            i += 1;

            if dq.len() != 0 {
                dq.push_back(*dq.front().unwrap());
                dq.pop_front();
            }
        }

        for i in 0..n {
            res[reveal_order[i]] = deck[i];
        }

        res
    }
}

fn main() {
    let deck_1: Vec<i32> = vec![17, 13, 11, 2, 3, 5, 7];
    let expected_1: Vec<i32> = vec![2, 13, 3, 11, 5, 17, 7];
    let output_1: Vec<i32> = Solution::deck_revealed_increasing(deck_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let deck_2: Vec<i32> = vec![1, 1000];
    let expected_2: Vec<i32> = vec![1, 1000];
    let output_2: Vec<i32> = Solution::deck_revealed_increasing(deck_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
