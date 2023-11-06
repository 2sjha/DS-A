/*
https://leetcode.com/problems/dungeon-game/

The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The
dungeon consists of m x n rooms laid out in a 2D grid. Our valiant knight was initially positioned
in the top-left room and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health
point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses
health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic
orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only rightward or downward
in each step.

Return the knight's minimum initial health so that he can rescue the princess.

Note that any room can contain threats or power-ups, even the first room the knight enters and the
bottom-right room where the princess is imprisoned.


Example 1:

Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path:
RIGHT-> RIGHT -> DOWN -> DOWN.

Example 2:

Input: dungeon = [[0]]
Output: 1


Constraints:

    m == dungeon.length
    n == dungeon[i].length
    1 <= m, n <= 200
    -1000 <= dungeon[i][j] <= 1000
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int calculateMinimumHP(vector<vector<int>> &dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> minHealth = vector<vector<int>>(m, vector<int>(n, 0));
        vector<vector<int>> health = vector<vector<int>>(m, vector<int>(n, 0));

        if (dungeon[0][0] > 0) {
            minHealth[0][0] = 1;
            health[0][0] = dungeon[0][0];
        } else {
            minHealth[0][0] = -1 * dungeon[0][0] + 1;
            health[0][0] = 1;
        }

        // first row
        for (int j = 1; j < n; ++j) {
            if (dungeon[0][j] >= 0) {
                minHealth[0][j] = minHealth[0][j - 1];
                health[0][j] = health[0][j - 1] + dungeon[0][j];
            } else {
                minHealth[0][j] = minHealth[0][j - 1] - dungeon[0][j];
                health[0][j] = health[0][j - 1];
            }
        }

        // first column
        for (int i = 1; i < m; ++i) {
            if (dungeon[i][0] >= 0) {
                minHealth[i][0] = minHealth[i - 1][0];
                health[i][0] = health[i - 1][0] + dungeon[i][0];
            } else {
                minHealth[i][0] = minHealth[i - 1][0] - dungeon[i][0];
                health[i][0] = health[i - 1][0];
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (dungeon[i][j] >= 0) {
                    if (minHealth[i - 1][j] < minHealth[i][j - 1]) {
                        minHealth[i][j] = minHealth[i - 1][j];
                        health[i][j] = health[i - 1][j];
                    } else {
                        minHealth[i][j] = minHealth[i][j - 1];
                        health[i][j] = health[i][j - 1];
                    }
                    health[i][j] += dungeon[i][j];
                } else {
                    if (i == m - 1 && j == n - 1) {
                        if (minHealth[i - 1][j] < minHealth[i][j - 1]) {
                            health[i][j] = health[i - 1][j];
                        } else {
                            health[i][j] = health[i][j - 1];
                        }
                        health[i][j] += dungeon[i][j];
                        if (health[i][j] <= 0) {
                            minHealth[i][j] = min(minHealth[i - 1][j], minHealth[i][j - 1]) - dungeon[i][j]; + 1;
                        } else {
                            minHealth[i][j] = min(minHealth[i - 1][j], minHealth[i][j - 1]);
                        }
                    } else {
                        if (minHealth[i - 1][j] < minHealth[i][j - 1]) {
                            minHealth[i][j] = minHealth[i - 1][j];
                            health[i][j] = health[i - 1][j];
                        } else {
                            minHealth[i][j] = minHealth[i][j - 1];
                            health[i][j] = health[i][j - 1];
                        }
                        minHealth[i][j] += -1 * dungeon[i][j];
                    }
                }
            }
        }

        return minHealth[m - 1][n - 1];
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> dungeon1 = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
    res = sol.calculateMinimumHP(dungeon1);
    cout << res << endl;
    assert(res == 7);

    // vector<vector<int>> dungeon2 = {{0}};
    // res = sol.calculateMinimumHP(dungeon2);
    // cout << res << endl;
    // assert(res == 1);

    // vector<vector<int>> dungeon3 = {{-200}};
    // res = sol.calculateMinimumHP(dungeon3);
    // cout << res << endl;
    // assert(res == 201);

    // vector<vector<int>> dungeon4 = {{2, 1}, {1, -1}};
    // res = sol.calculateMinimumHP(dungeon4);
    // cout << res << endl;
    // assert(res == 1);

    // vector<vector<int>> dungeon5 = {{0, 0}, {-5, -4}};
    // res = sol.calculateMinimumHP(dungeon5);
    // cout << res << endl;
    // assert(res == 5);

    return 0;
}