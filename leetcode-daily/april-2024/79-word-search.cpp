/*
https://leetcode.com/problems/word-search

Given an `m x n` grid of characters `board` and a string `word`, return `true` *if* `word` *exists
in the grid*.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are
horizontally or vertically neighboring. The same letter cell may not be used more than once.


**Example 1:**

**Input:** board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = 'ABCCED'
**Output:** true

**Example 2:**

**Input:** board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = 'SEE'
**Output:** true

**Example 3:**

**Input:** board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = 'ABCB'
**Output:** false


**Constraints:**

* `m == board.length`
* `n = board[i].length`
* `1 <= m, n <= 6`
* `1 <= word.length <= 15`
* `board` and `word` consists of only lowercase and uppercase English letters.


**Follow up:** Could you use search pruning to make your solution faster with a larger `board`?
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    bool search(vector<vector<char>> &board, unordered_map<int, unordered_map<int, bool>> &visited,
                int row, int col, string &word, int idx) {
        int m = board.size();
        int n = board[0].size();
        if (!visited.count(row)) {
            visited[row] = unordered_map<int, bool>();
        }
        visited[row][col] = true;

        bool res = false;
        if (idx == word.length() - 1) {
            res = true;
        } else {
            for (int i = 0; i < 4; ++i) {
                if (row + directions[i][0] < 0 || row + directions[i][0] >= m)
                    continue;
                if (col + directions[i][1] < 0 || col + directions[i][1] >= n)
                    continue;

                if (board[row + directions[i][0]][col + directions[i][1]] == word[idx + 1] &&
                    (!visited.count(row + directions[i][0]) ||
                     !visited[row + directions[i][0]].count(col + directions[i][1]) ||
                     !visited[row + directions[i][0]][col + directions[i][1]])) {
                    res |= search(board, visited, row + directions[i][0], col + directions[i][1],
                                  word, idx + 1);
                }
            }
        }

        visited[row][col] = false;
        return res;
    }

  public:
    bool exist(vector<vector<char>> &board, string word) {
        int m = board.size();
        int n = board[0].size();
        unordered_map<int, unordered_map<int, bool>> visited;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    if (search(board, visited, i, j, word, 0)) {
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

    vector<vector<char>> board_1 = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word_1 = "ABCCED";
    bool expected_1 = true;
    bool output_1 = sol.exist(board_1, word_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<vector<char>> board_2 = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word_2 = "SEE";
    bool expected_2 = true;
    bool output_2 = sol.exist(board_2, word_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<vector<char>> board_3 = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word_3 = "ABCB";
    bool expected_3 = false;
    bool output_3 = sol.exist(board_3, word_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    vector<vector<char>> board_4 = {{'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
                                    {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
                                    {'A', 'A', 'A', 'A', 'A', 'B'}, {'A', 'A', 'A', 'A', 'B', 'A'}};
    string word_4 = "AAAAAAAAAAAAABB";
    bool expected_4 = false;
    bool output_4 = sol.exist(board_4, word_4);
    cout << output_4 << endl;
    assert(output_4 == expected_4);

    return 0;
}