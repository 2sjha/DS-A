/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock

You are given an array `prices` where `prices[i]` is the price of a given stock on the `i^{th}` day.

You want to maximize your profit by choosing a **single day** to buy one stock and choosing a **different day in the
future** to sell that stock.

Return *the maximum profit you can achieve from this transaction*. If you cannot achieve any profit, return `0`.


**Example 1:**

**Input:** prices = [7,1,5,3,6,4]
**Output:** 5
**Explanation:** Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

**Example 2:**

**Input:** prices = [7,6,4,3,1]
**Output:** 0
**Explanation:** In this case, no transactions are done and the max profit = 0.


**Constraints:**

* `1 <= prices.length <= 10⁵`
* `0 <= prices[i] <= 10⁴`
*/

struct Solution;
impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n: usize = prices.len();
        let mut left: Vec<i32> = vec![0; n];
        left[0] = i32::MAX;
        let mut profit: i32 = 0;
        for i in 1..n {
            left[i] = std::cmp::min(left[i - 1], prices[i - 1]);
            profit = std::cmp::max(profit, prices[i] - left[i]);
        }

        profit
    }
}

fn main() {
    let prices_1: Vec<i32> = vec![7, 1, 5, 3, 6, 4];
    let expected_1: i32 = 5;
    let output_1: i32 = Solution::max_profit(prices_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let prices_2: Vec<i32> = vec![7, 6, 4, 3, 1];
    let expected_2: i32 = 0;
    let output_2: i32 = Solution::max_profit(prices_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
