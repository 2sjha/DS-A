/*
https://leetcode.com/problems/time-needed-to-buy-tickets

There are `n` people in a line queuing to buy tickets, where the `0^{th}` person is at the **front**
of the line and the
`(n - 1)^{th}` person is at the **back** of the line.

You are given a **0-indexed** integer array `tickets` of length `n` where the number of tickets that
the `i^{th}` person would like to buy is `tickets[i]`.

Each person takes **exactly 1 second** to buy a ticket. A person can only buy **1 ticket at a time**
and has to go back to **the end** of the line (which happens **instantaneously**) in order to buy
more tickets. If a person does not have any tickets left to buy, the person will **leave **the line.

Return *the **time taken** for the person at position *`k`* ****(0-indexed)* ***to finish buying
tickets*.


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
The person at position 0 has successfully bought 5 tickets and it took 4 + 1 + 1 + 1 + 1 = 8
seconds.


**Constraints:**

* `n == tickets.length`
* `1 <= n <= 100`
* `1 <= tickets[i] <= 100`
* `0 <= k < n`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int timeRequiredToBuy(vector<int> &tickets, int k) {
        int n = tickets.size();
        int res = 0;
        while (tickets[k] != 0) {
            for (int i = 0; i < n; ++i) {
                if (tickets[i] != 0) {
                    tickets[i]--;
                    res++;
                }
                if (i == k && tickets[k] == 0)
                    break;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> tickets_1 = {2, 3, 2};
    int k_1 = 2;
    int expected_1 = 6;
    int output_1 = sol.timeRequiredToBuy(tickets_1, k_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> tickets_2 = {5, 1, 1, 1};
    int k_2 = 0;
    int expected_2 = 8;
    int output_2 = sol.timeRequiredToBuy(tickets_2, k_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}