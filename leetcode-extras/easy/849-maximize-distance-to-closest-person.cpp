/*
You are given an array representing a row of seats where seats[i] = 1 represents a person sitting in
the ith seat, and seats[i] = 0 represents that the ith seat is empty (0-indexed).

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest person to him is
maximized.

Return that maximum distance to the closest person.


Example 1:

Input: seats = [1,0,0,0,1,0,1]
Output: 2
Explanation:
If Alex sits in the second open seat (i.e. seats[2]), then the closest person has distance 2.
If Alex sits in any other open seat, the closest person has distance 1.
Thus, the maximum distance to the closest person is 2.

Example 2:

Input: seats = [1,0,0,0]
Output: 3
Explanation:
If Alex sits in the last seat (i.e. seats[3]), the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.

Example 3:

Input: seats = [0,1]
Output: 1


Constraints:

    2 <= seats.length <= 2 * 10^4
    seats[i] is 0 or 1.
    At least one seat is empty.
    At least one seat is occupied.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int maxDistToClosest(vector<int> &seats) {
        int n = seats.size();
        vector<int> left(n, 0);
        vector<int> right(n, 0);

        for (int i = 1; i < n; ++i) {
            if (seats[i]) {
                left[i] = 0;
            } else {
                left[i] = left[i - 1] + 1;
            }
        }
        left[0] = 1e5;

        for (int i = n - 2; i >= 0; --i) {
            if (seats[i]) {
                right[i] = 0;
            } else {
                right[i] = right[i + 1] + 1;
            }
        }
        right[n - 1] = 1e5;

        int res = INT_MIN;
        for (int i = 0; i < n; ++i) {
            res = max(res, min(left[i], right[i]));
        }

        return res;
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> seats1 = {1, 0, 0, 0, 1, 0, 1};
    res = sol.maxDistToClosest(seats1);
    cout << res << endl;
    assert(res == 2);

    vector<int> seats2 = {1, 0, 0, 0};
    res = sol.maxDistToClosest(seats2);
    cout << res << endl;
    assert(res == 3);

    vector<int> seats3 = {1, 0};
    res = sol.maxDistToClosest(seats3);
    cout << res << endl;
    assert(res == 1);

    return 0;
}