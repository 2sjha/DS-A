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

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        
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

    return 000000;
}