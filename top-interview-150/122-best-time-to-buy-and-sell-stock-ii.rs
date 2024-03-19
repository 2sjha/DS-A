/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `i^{th}` day.

On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of the stock at any
time. However, you can buy it then immediately sell it on the **same day**.

Find and return *the **maximum** profit you can achieve*.


**Example 1:**

**Input:** prices = [7,1,5,3,6,4]
**Output:** 7
**Explanation:** Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.

**Example 2:**

**Input:** prices = [1,2,3,4,5]
**Output:** 4
**Explanation:** Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.

**Example 3:**

**Input:** prices = [7,6,4,3,1]
**Output:** 0
**Explanation:** There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0
.


**Constraints:**

* `1 <= prices.length <= 3 * 10⁴`
* `0 <= prices[i] <= 10⁴`
*/

struct Solution;
impl Solution {
    fn helper(
        dp: &mut Vec<Vec<i32>>,
        prices: &Vec<i32>,
        idx: usize,
        holding: u8,
    ) -> i32 {
        if idx == prices.len() - 1 {
            if holding == 1 {
                return prices[idx];
            } else {
                return 0;
            }
        }

        if holding == 1 && dp[1][idx] != -1 {
            return dp[1][idx];
        }
        if holding == 0 && dp[0][idx] != -1 {
            return dp[0][idx];
        }

        let profit: i32;
        if holding == 1 {
            profit = std::cmp::max(
                Self::helper(dp, prices, idx + 1, 1),
                prices[idx] + Self::helper(dp, prices, idx + 1, 0),
            );
            dp[1][idx] = profit;
        } else {
            profit = std::cmp::max(
                Self::helper(dp, prices, idx + 1, 0),
                -prices[idx] + Self::helper(dp, prices, idx + 1, 1),
            );
            dp[0][idx] = profit;
        }

        profit
    }

    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n: usize = prices.len();
        let mut dp: Vec<Vec<i32>> = vec![vec![-1; n]; 2];
        Self::helper(&mut dp, &prices, 0, 0)
    }
}

fn main() {
    let prices_1: Vec<i32> = vec![7, 1, 5, 3, 6, 4];
    let expected_1: i32 = 7;
    let output_1: i32 = Solution::max_profit(prices_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let prices_2: Vec<i32> = vec![1, 2, 3, 4, 5];
    let expected_2: i32 = 4;
    let output_2: i32 = Solution::max_profit(prices_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);

    let prices_3: Vec<i32> = vec![7, 6, 4, 3, 1];
    let expected_3: i32 = 0;
    let output_3: i32 = Solution::max_profit(prices_3);
    println!("{:?}", output_3);
    assert!(output_3 == expected_3);
}
