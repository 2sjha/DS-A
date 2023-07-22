/*
https://leetcode.com/problems/knight-probability-in-chessboard/

On an n x n chessboard, a knight starts at the cell (row, column) and attempts to make exactly k
moves. The rows and columns are 0-indexed, so the top-left cell is (0, 0), and the bottom-right cell
is (n - 1, n - 1).

A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in
a cardinal direction, then one cell in an orthogonal direction.

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if
the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly k moves or has moved off the chessboard.

Return the probability that the knight remains on the board after it has stopped moving.


Example 1:

Input: n = 3, k = 2, row = 0, column = 0
Output: 0.06250
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.

Example 2:

Input: n = 1, k = 0, row = 0, column = 0
Output: 1.00000


Constraints:

    1 <= n <= 25
    0 <= k <= 100
    0 <= row, column <= n - 1
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    unordered_map<int, unordered_map<int, unordered_map<int, double>>> prob;

    bool outOfBounds(int n, int row, int col) { return row < 0 || row >= n || col < 0 || col >= n; }

    double doMoves(int curr_row, int curr_col, int n, int moves_count, int k) {
        if (prob.count(curr_row) && prob[curr_row].count(curr_col) &&
            prob[curr_row][curr_col].count(moves_count)) {
            return prob[curr_row][curr_col][moves_count];
        }

        if (outOfBounds(n, curr_row, curr_col)) {
            return 0;
        }

        if (moves_count == k) {
            return 1;
        }

        double this_prob = doMoves(curr_row + 1, curr_col + 2, n, moves_count + 1, k);
        this_prob += doMoves(curr_row + 1, curr_col - 2, n, moves_count + 1, k);
        this_prob += doMoves(curr_row + 2, curr_col + 1, n, moves_count + 1, k);
        this_prob += doMoves(curr_row + 2, curr_col - 1, n, moves_count + 1, k);
        this_prob += doMoves(curr_row - 1, curr_col + 2, n, moves_count + 1, k);
        this_prob += doMoves(curr_row - 1, curr_col - 2, n, moves_count + 1, k);
        this_prob += doMoves(curr_row - 2, curr_col + 1, n, moves_count + 1, k);
        this_prob += doMoves(curr_row - 2, curr_col - 1, n, moves_count + 1, k);

        prob[curr_row][curr_col][moves_count] = this_prob / 8;
        return prob[curr_row][curr_col][moves_count];
    }

  public:
    double knightProbability(int n, int k, int row, int column) {
        double total_moves_until_stop = (double)0;
        double on_board_after_stop = (double)0;

        prob[row][column][0] = doMoves(row, column, n, 0, k);

        return prob[row][column][0];
    }
};

int main() {
    Solution sol;
    double res;
    int n, k, row, col;

    n = 3;
    k = 2;
    row = 0;
    col = 0;
    res = sol.knightProbability(n, k, row, col);
    cout << res << endl;
    assert(res == 0.06250);

    n = 8;
    k = 30;
    row = 6;
    col = 4;
    res = sol.knightProbability(n, k, row, col);
    cout << res << endl;
    return 0;
}