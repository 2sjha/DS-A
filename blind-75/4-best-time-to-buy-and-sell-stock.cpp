/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different
day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit,
return 0.



Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.



Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 104

*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  public:
	int maxProfit(vector<int>& prices) {
		int max_profit = 0;
		// bool non_increasing_prices = check_non_increasing_prices(prices);
		// if (non_increasing_prices) {
		//     return max_profit;
		// }

		priority_queue<int> max_heap;
		priority_queue<int, vector<int>, greater<int>> min_heap;
		unordered_map<int, int> element_index_map;
		populate_heaps_maps(prices, max_heap, min_heap, element_index_map);

		while (!max_heap.empty() && !min_heap.empty()) {
			int buy = min_heap.top();
			int sell = max_heap.top();
			int profit = sell - buy;

			if (profit < 0) {
				break;
			}

			if (element_index_map[sell] > element_index_map[buy]) {
				max_profit = profit;
				break;
			}

			if() {
				max_heap.pop();
			} else {
				min_heap.pop();
			}
		}

		return max_profit;
	}

  private:
	bool check_non_increasing_prices(vector<int>& prices) {
		int count_increase = 0;
		for (int i = 0; i < prices.size() - 1; i++) {
			if (prices[i + 1] > prices[i]) {
				count_increase++;
				break;
			}
		}

		if (count_increase == 0) {
			return true;
		} else {
			return false;
		}
	}

	void populate_heaps_maps(vector<int>& prices, priority_queue<int>& max_heap,
							 priority_queue<int, vector<int>, greater<int>>& min_heap,
							 unordered_map<int, int>& element_index_map) {

		for (int i = 0; i < prices.size(); i++) {
			max_heap.push(prices[i]);
			min_heap.push(prices[i]);
			element_index_map[prices[i]] = i;
		}
	}
};

int main() {
	Solution sol;
	int n;
	vector<int> stock_prices;

	cout << "Enter n" << endl;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		stock_prices.push_back(temp);
	}

	int res = sol.maxProfit(stock_prices);
	cout << res << endl;

	return 0;
}