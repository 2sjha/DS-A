/*
https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/

We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's transfer
season, and some employees want to change the building they reside in.

You are given an array requests where requests[i] = [fromi, toi] represents an employee's request to
transfer from building fromi to building toi.

All buildings are full, so a list of requests is achievable only if for each building, the net
change in employee transfers is zero. This means the number of employees leaving is equal to the
number of employees moving in. For example if n = 3 and two employees are leaving building 0, one is
leaving building 1, and one is leaving building 2, there should be two employees moving to building
0, one employee moving to building 1, and one employee moving to building 2.

Return the maximum number of achievable requests.


Example 1:

Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
Output: 5
Explantion: Let's see the requests:
From building 0 we have employees x and y and both want to move to building 1.
From building 1 we have employees a and b and they want to move to buildings 2 and 0 respectively.
From building 2 we have employee z and they want to move to building 0.
From building 3 we have employee c and they want to move to building 4.
From building 4 we don't have any requests.
We can achieve the requests of users x and b by swapping their places.
We can achieve the requests of users y, a and z by swapping the places in the 3 buildings.

Example 2:

Input: n = 3, requests = [[0,0],[1,2],[2,1]]
Output: 3
Explantion: Let's see the requests:
From building 0 we have employee x and they want to stay in the same building 0.
From building 1 we have employee y and they want to move to building 2.
From building 2 we have employee z and they want to move to building 1.
We can achieve all the requests.

Example 3:

Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
Output: 4


Constraints:

    1 <= n <= 20
    1 <= requests.length <= 16
    requests[i].length == 2
    0 <= fromi, toi < n
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool validTransfers(vector<int> &buildings) {
        bool all_zero = true;
        for (int i : buildings) {
            if (i != 0) {
                all_zero = false;
                break;
            }
        }

        if (all_zero) {
            return true;
        } else {
            return false;
        }
    }

    int maxReq(int n, vector<vector<int>> &requests, vector<int> buildings, int start,
               int satisfyCnt) {
        int from, to;
        int res = -1;
        for (int i = start; i < requests.size(); ++i) {
            from = requests[i][0];
            to = requests[i][1];

            // Satisfy this req
            buildings[from]--;
            buildings[to]++;
            res = max(res, maxReq(n, requests, buildings, i + 1, satisfyCnt + 1));

            // Dont Satisfy this req
            buildings[from]++;
            buildings[to]--;
        }

        if (validTransfers(buildings)) {
            res = max(res, satisfyCnt);
        }
        return res;
    }

  public:
    int maximumRequests(int n, vector<vector<int>> &requests) {
        vector<int> buildings(n, 0);

        return maxReq(n, requests, buildings, 0, 0);
    }
};

int main() {
    Solution sol;
    int res;

    int n1 = 5;
    vector<vector<int>> requests1 = {{0, 1}, {1, 0}, {0, 1}, {1, 2}, {2, 0}, {3, 4}};
    res = sol.maximumRequests(n1, requests1);
    cout << res << endl;
    assert(res == 5);

    int n2 = 3;
    vector<vector<int>> requests2 = {{0, 0}, {1, 2}, {2, 1}};
    res = sol.maximumRequests(n2, requests2);
    cout << res << endl;
    assert(res == 3);

    int n3 = 4;
    vector<vector<int>> requests3 = {{0, 3}, {3, 1}, {1, 2}, {2, 0}};
    res = sol.maximumRequests(n3, requests3);
    cout << res << endl;
    assert(res == 3);

    return 0;
}