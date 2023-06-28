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

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool begin_search(vector<vector<char>> &board, string word, int i, int j) {
        int curr_i, curr_j, curr_idx;
        pair<pair<int, int>, int> curr;
        stack<pair<pair<int, int>, int>> dfs_st;
        vector<pair<int, int>> visited;
        dfs_st.push({{i, j}, 0});
        visited.push_back({i, j});

        while (!dfs_st.empty()) {
            curr = dfs_st.top();
            dfs_st.pop();

            curr_i = curr.first.first;
            curr_j = curr.first.second;
            curr_idx = curr.second;

            if (curr_idx == word.length() - 1) {
                return true;
            }

            bool next_found = false;

            if (curr_i > 0 && !check_visited(visited, curr_i - 1, curr_j) &&
                board[curr_i - 1][curr_j] == word[curr_idx + 1]) {
                dfs_st.push({{curr_i - 1, curr_j}, curr_idx + 1});
                visited.push_back({curr_i - 1, curr_j});
                next_found = true;
            }
            if (curr_j > 0 && !check_visited(visited, curr_i, curr_j - 1) &&
                board[curr_i][curr_j - 1] == word[curr_idx + 1]) {
                dfs_st.push({{curr_i, curr_j - 1}, curr_idx + 1});
                visited.push_back({curr_i, curr_j - 1});
                next_found = true;
            }
            if (curr_i < board.size() - 1 && !check_visited(visited, curr_i + 1, curr_j) &&
                board[curr_i + 1][curr_j] == word[curr_idx + 1]) {
                dfs_st.push({{curr_i + 1, curr_j}, curr_idx + 1});
                visited.push_back({curr_i + 1, curr_j});
                next_found = true;
            }
            if (curr_j < board[0].size() - 1 && !check_visited(visited, curr_i, curr_j + 1) &&
                board[curr_i][curr_j + 1] == word[curr_idx + 1]) {
                dfs_st.push({{curr_i, curr_j + 1}, curr_idx + 1});
                visited.push_back({curr_i, curr_j + 1});
                next_found = true;
            }

            if (!next_found) {
                visited.pop_back();
            }
        }

        return false;
    }

    bool check_visited(vector<pair<int, int>> &visited, int curr_i, int curr_j) {
        for (pair<int, int> cell : visited) {
            if (cell.first == curr_i && cell.second == curr_j) {
                return true;
            }
        }
        return false;
    }

  public:
    bool exist(vector<vector<char>> &board, string word) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == word[0] && begin_search(board, word, i, j)) {
                    return true;
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

    vector<vector<char>> board3 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'E', 'S'},
        {'A', 'D', 'E', 'E'}};
    string word5 = "ABCESEEEFS";
    res = sol.exist(board3, word5);
    cout << res << endl;
    assert(res == true);

    return 0;
}