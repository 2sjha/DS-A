/*
https://leetcode.com/problems/word-search-ii

Given an `m x n` `board` of characters and a list of strings `words`, return *all words on the
board*.

Each word must be constructed from letters of sequentially adjacent cells, where **adjacent cells**
are horizontally or vertically neighboring. The same letter cell may not be used more than once in a
word.


**Example 1:**

**Input:** board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words
= ["oath","pea","eat
","rain"]
**Output:** ["eat","oath"]

**Example 2:**

**Input:** board = [["a","b"],["c","d"]], words = ["abcb"]
**Output:** []


**Constraints:**

* `m == board.length`
* `n == board[i].length`
* `1 <= m, n <= 12`
* `board[i][j]` is a lowercase English letter.
* `1 <= words.length <= 3 * 10⁴`
* `1 <= words[i].length <= 10`
* `words[i]` consists of lowercase English letters.
* All the strings of `words` are unique.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

struct TrieNode {
    vector<TrieNode *> edges;
    bool word_end;

    TrieNode() {
        word_end = false;
        edges = vector<TrieNode *>(26, nullptr);
    }
};

void addWord(TrieNode *trie_root, vector<char> &word) {
    TrieNode *curr = trie_root;
    for (int i = 0; i < word.size(); ++i) {
        if (curr->edges[word[i] - 'a'] == nullptr) {
            curr->edges[word[i] - 'a'] = new TrieNode();
        }
        curr = curr->edges[word[i] - 'a'];
    }
    curr->word_end = true;
}

bool search(TrieNode *trie_root, string word) {
    TrieNode *curr = trie_root;
    for (int i = 0; i < word.length(); ++i) {
        if (curr->edges[word[i] - 'a'] == nullptr)
            return false;
        else
            curr = curr->edges[word[i] - 'a'];
    }

    return curr->word_end;
}

class Solution {
  private:
    TrieNode *trie_root = nullptr;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void addAllWords(TrieNode *trie_root, vector<vector<char>> &board, int i, int j, int m, int n,
                     vector<char> &prev_word, int max_word_len) {
        if (prev_word.size() == max_word_len)
            return;

        prev_word.push_back(board[i][j]);
        addWord(trie_root, prev_word);

        char prev = board[i][j];
        board[i][j] = '.';

        for (int di = 0; di < 4; di++) {
            if (i + directions[di][0] < 0 || i + directions[di][0] >= m)
                continue;
            if (j + directions[di][1] < 0 || j + directions[di][1] >= n)
                continue;

            if (board[i + directions[di][0]][j + directions[di][1]] != '.') {
                addAllWords(trie_root, board, i + directions[di][0], j + directions[di][1], m, n,
                            prev_word, max_word_len);
            }
        }

        prev_word.pop_back();
        board[i][j] = prev;
    }

  public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
        int max_word_len = 0;
        for (int i = 0; i < words.size(); ++i) {
            max_word_len = max(max_word_len, (int)words[i].length());
        }

        // make trie from the chars in the board in a DFS manner
        this->trie_root = new TrieNode();
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<char> empty;
                addAllWords(trie_root, board, i, j, m, n, empty, max_word_len);
            }
        }

        // search words in trie
        int words_sz = words.size();
        set<string> res_set;
        for (int i = 0; i < words_sz; ++i) {
            if (search(trie_root, words[i])) {
                res_set.insert(words[i]);
            }
        }

        vector<string> res;
        for (string w : res_set) {
            res.push_back(w);
        }
        return res;
    }
};

int main() {

    Solution sol_1;
    vector<vector<char>> board_1 = {
        {'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};
    vector<string> words_1 = {"oath", "pea", "eat", "rain"};
    vector<string> expected_1 = {"eat", "oath"};
    vector<string> output_1 = sol_1.findWords(board_1, words_1);
    printArray(output_1);
    assert(output_1 == expected_1);

    Solution sol_2;
    vector<vector<char>> board_2 = {{'a', 'b'}, {'c', 'd'}};
    vector<string> words_2 = {"abcb"};
    vector<string> expected_2 = {};
    vector<string> output_2 = sol_2.findWords(board_2, words_2);
    printArray(output_2);
    assert(output_2 == expected_2);

    Solution sol_3;
    vector<vector<char>> board_3 = {{'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
                                    {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'}};
    vector<string> words_3 = {"a",      "aa",      "aaa",      "aaaa",      "aaaaa",
                              "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"};
    vector<string> expected_3 = {"a",      "aa",      "aaa",      "aaaa",      "aaaaa",
                                 "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"};
    vector<string> output_3 = sol_3.findWords(board_3, words_3);
    printArray(output_3);
    assert(output_3 == expected_3);
    return 0;
}