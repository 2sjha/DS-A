/*
https://leetcode.com/problems/word-ladder

A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList`
is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:

* Every adjacent pair of words differs by a single letter.
* Every `si` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in
`wordList`.
* `sk == endWord`

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return *the **number of
words** in the
**shortest transformation sequence** from* `beginWord` *to* `endWord`*, or *`0`* if no such sequence
exists.*


**Example 1:**

**Input:** beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
**Output:** 5
**Explanation:** One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog",
which is 5 words long
.

**Example 2:**

**Input:** beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
**Output:** 0
**Explanation:** The endWord "cog" is not in wordList, therefore there is no valid transformation
sequence.


**Constraints:**

* `1 <= beginWord.length <= 10`
* `endWord.length == beginWord.length`
* `1 <= wordList.length <= 5000`
* `wordList[i].length == beginWord.length`
* `beginWord`, `endWord`, and `wordList[i]` consist of lowercase English letters.
* `beginWord != endWord`
* All the words in `wordList` are **unique**.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool differByOne(string a, string b) {
        int n = a.length();
        int m = b.length();

        if (n != m)
            return false;

        int diff = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] != b[i])
                diff++;
            if (diff > 1)
                return false;
        }

        return diff == 1;
    }

    int shortestTransformation(unordered_map<string, set<string>> &g, string src, string dest) {
        int res = -1;
        unordered_map<string, bool> visited;
        queue<pair<string, int>> bfs_q;
        bfs_q.push({src, 0});

        while (!bfs_q.empty()) {
            pair<string, int> curr = bfs_q.front();
            bfs_q.pop();

            if (curr.first == dest) {
                res = curr.second;
                break;
            }

            if (visited[curr.first])
                continue;

            visited[curr.first] = true;
            for (string w : g[curr.first]) {
                if (!visited[w])
                    bfs_q.push({w, curr.second + 1});
            }
        }

        return res;
    }

  public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        unordered_map<string, set<string>> g;
        int n = wordList.size();
        int res = INT_MAX;

        for (string w : wordList) {
            g[w] = set<string>();
        }

        if (!g.count(endWord))
            return 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (differByOne(wordList[i], wordList[j])) {
                    g[wordList[i]].insert(wordList[j]);
                    g[wordList[j]].insert(wordList[i]);
                }
            }
        }

        if (!g.count(beginWord)) {
            for (auto entry : g) {
                if (differByOne(entry.first, beginWord)) {
                    int tmp = shortestTransformation(g, entry.first, endWord);
                    if (tmp != -1)
                        res = min(res, tmp + 2);
                }
            }
        } else {
            int tmp = shortestTransformation(g, beginWord, endWord);
            if (tmp != -1)
                res = min(res, tmp + 1);
        }

        if (res != INT_MAX)
            return res;
        else
            return 0;
    }
};

int main() {
    Solution sol;

    string beginWord_1 = "hit";
    string endWord_1 = "cog";
    vector<string> wordList_1 = {"hot", "dot", "dog", "lot", "log", "cog"};
    int expected_1 = 5;
    int output_1 = sol.ladderLength(beginWord_1, endWord_1, wordList_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string beginWord_2 = "hit";
    string endWord_2 = "cog";
    vector<string> wordList_2 = {"hot", "dot", "dog", "lot", "log"};
    int expected_2 = 0;
    int output_2 = sol.ladderLength(beginWord_2, endWord_2, wordList_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}