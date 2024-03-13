/*
https://leetcode.com/problems/word-search/

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are
horizontally or vertically neighboring. The same letter cell may not be used more than once.


Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false


Constraints:

    m == board.length
    n = board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board and word consists of only lowercase and uppercase English letters.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// DFS is obvious but
// I was stuck at detecting chars already traversed/ in dfs stack
// Solution is to change board before stack call and revert it later
class Solution {
  private:
    bool find_word_dfs(vector<vector<char>> &board, string word, int row, int col, int idx) {
        int m = board.size();
        int n = board[0].size();
        int len = word.length();

        if (idx == len - 1) {
            return true;
        }

        board[row][col] = '#';

        bool l = false, r = false, u = false, d = false;

        if (col < n - 1 && board[row][col + 1] == word[idx + 1]) {
            r = find_word_dfs(board, word, row, col + 1, idx + 1);
        }
        if (row < m - 1 && board[row + 1][col] == word[idx + 1]) {
            d = find_word_dfs(board, word, row + 1, col, idx + 1);
        }
        if (col > 0 && board[row][col - 1] == word[idx + 1]) {
            l = find_word_dfs(board, word, row, col - 1, idx + 1);
        }
        if (row > 0 && board[row - 1][col] == word[idx + 1]) {
            u = find_word_dfs(board, word, row - 1, col, idx + 1);
        }
        board[row][col] = word[idx];

        return l || r || u || d;
    }

  public:
    bool exist(vector<vector<char>> &board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    if (find_word_dfs(board, word, i, j, 0)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

int main() {
    Solution sol;
    bool res;

    vector<vector<char>> board1 = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word1 = "ABCCED";
    res = sol.exist(board1, word1);
    cout << res << endl;
    assert(res == true);

    string word2 = "SEE";
    res = sol.exist(board1, word2);
    cout << res << endl;
    assert(res == true);

    string word3 = "ABCB";
    res = sol.exist(board1, word3);
    cout << res << endl;
    assert(res == false);

    vector<vector<char>> board2 = {{'a', 'b'}, {'c', 'd'}};
    string word4 = "acdb";
    res = sol.exist(board2, word4);
    cout << res << endl;
    assert(res == true);

    vector<vector<char>> board4 = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'E', 'S'}, {'A', 'D', 'E', 'E'}};
    string word6 = "ABCESEEEFS";
    res = sol.exist(board4, word6);
    cout << res << endl;
    assert(res == true);

    vector<vector<char>> board3 = {{'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
                                   {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
                                   {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
    string word5 = "AAAAAAAAAAAAAAa";
    res = sol.exist(board3, word5);
    cout << res << endl;
    assert(res == false);

    return 0;
}