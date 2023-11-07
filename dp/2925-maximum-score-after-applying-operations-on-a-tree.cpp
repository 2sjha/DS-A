/*
https://leetcode.com/contest/weekly-contest-370/problems/maximum-score-after-applying-operations-on-a-tree/

2925. Maximum Score After Applying Operations on a Tree

There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are
given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an
edge between nodes ai and bi in the tree.

You are also given a 0-indexed integer array values of length n, where values[i] is the value
associated with the ith node.

You start with a score of 0. In one operation, you can:

    Pick any node i.
    Add values[i] to your score.
    Set values[i] to 0.

A tree is healthy if the sum of values on the path from the root to any leaf node is different than
zero.

Return the maximum score you can obtain after performing these operations on the tree any number of
times so that it remains healthy.


Example 1:

Input: edges = [[0,1],[0,2],[0,3],[2,4],[4,5]], values = [5,2,5,2,1,1]
Output: 11
Explanation: We can choose nodes 1, 2, 3, 4, and 5. The value of the root is non-zero. Hence, the
sum of values on the path from the root to any leaf is different than zero. Therefore, the tree is
healthy and the score is values[1] + values[2] + values[3] + values[4] + values[5] = 11. It can be
shown that 11 is the maximum score obtainable after any number of operations on the tree.

Example 2:

Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [20,10,9,7,4,3,5]
Output: 40
Explanation: We can choose nodes 0, 2, 3, and 4.
- The sum of values on the path from 0 to 4 is equal to 10.
- The sum of values on the path from 0 to 3 is equal to 10.
- The sum of values on the path from 0 to 5 is equal to 3.
- The sum of values on the path from 0 to 6 is equal to 5.
Therefore, the tree is healthy and the score is values[0] + values[2] + values[3] + values[4] = 40.
It can be shown that 40 is the maximum score obtainable after any number of operations on the tree.


Constraints:

    2 <= n <= 2 * 104
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    values.length == n
    1 <= values[i] <= 109
    The input is generated such that edges represents a valid tree.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Looked up Solution
// To maximize score, we need to minimize the value of nodes in paths to leaf nodes
// So we do that instead, Choose minimum of this node, or sum of children nodes

class Solution {
  private:
    unordered_map<int, pair<int, set<int>>> g;

    long long dfs(int i) {
        if (g[i].second.empty())
            return g[i].first;

        long long sum = 0;
        for (int j : g[i].second) {
            sum += dfs(j);
        }

        return min((long long)g[i].first, sum);
    }

    void convert_to_dag(int i) {
        for (int j : g[i].second) {
            g[j].second.erase(i);
        }
        for (int j : g[i].second) {
            convert_to_dag(j);
        }
    }

    long long get_sum_subtree(int i) {
        long long sum = g[i].first;
        for (int j : g[i].second) {
            sum += get_sum_subtree(j);
        }
        return sum;
    }

  public:
    long long maximumScoreAfterOperations(vector<vector<int>> &edges, vector<int> &values) {
        int n = values.size();

        for (int i = 0; i < n; ++i) {
            g[i] = {values[i], set<int>()};
        }

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            g[u].second.insert(v);
            g[v].second.insert(u);
        }

        convert_to_dag(0);
        long long res = get_sum_subtree(0);
        res -= dfs(0);

        return res;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {2, 3}};
    vector<int> values1 = {5, 4, 1, 2};
    res = sol.maximumScoreAfterOperations(edges1, values1);
    cout << res << endl;
    assert(res == 7);

    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {2, 3}};
    vector<int> values2 = {5, 4, 2, 1};
    res = sol.maximumScoreAfterOperations(edges2, values2);
    cout << res << endl;
    assert(res == 7);

    vector<vector<int>> edges3 = {{0, 1}, {0, 2}, {2, 3}};
    vector<int> values3 = {4, 5, 1, 2};
    res = sol.maximumScoreAfterOperations(edges3, values3);
    cout << res << endl;
    assert(res == 8);

    vector<vector<int>> edges4 = {{0, 1}, {0, 2}, {2, 3}};
    vector<int> values4 = {4, 5, 2, 1};
    res = sol.maximumScoreAfterOperations(edges4, values4);
    cout << res << endl;
    assert(res == 8);

    vector<vector<int>> edges5 = {{7, 0}, {3, 1}, {6, 2}, {4, 3}, {4, 5}, {4, 6}, {4, 7}};
    vector<int> values5 = {2, 16, 23, 17, 22, 21, 8, 6};
    res = sol.maximumScoreAfterOperations(edges5, values5);
    cout << res << endl;
    assert(res == 113);

    vector<vector<int>> edges6 = {{0, 1}, {0, 2}, {0, 3}, {2, 4}, {4, 5}};
    vector<int> values6 = {5, 2, 5, 2, 1, 1};
    res = sol.maximumScoreAfterOperations(edges6, values6);
    cout << res << endl;
    assert(res == 11);

    vector<vector<int>> edges7 = {{0, 1}, {0, 2}};
    vector<int> values7 = {10, 7, 4};
    res = sol.maximumScoreAfterOperations(edges7, values7);
    cout << res << endl;
    assert(res == 11);

    vector<vector<int>> edges8 = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
    vector<int> values8 = {20, 10, 9, 7, 4, 3, 5};
    res = sol.maximumScoreAfterOperations(edges8, values8);
    cout << res << endl;
    assert(res == 40);

    vector<vector<int>> edges9 = {{3, 1}, {0, 2}, {0, 3}};
    vector<int> values9 = {21, 12, 19, 5};
    res = sol.maximumScoreAfterOperations(edges9, values9);
    cout << res << endl;
    assert(res == 36);

    vector<vector<int>> edges10 = {{2, 0}, {4, 1}, {5, 3}, {4, 6}, {2, 4}, {5, 2}, {5, 7}};
    vector<int> values10 = {12, 12, 7, 9, 2, 11, 12, 25};
    res = sol.maximumScoreAfterOperations(edges10, values10);
    cout << res << endl;
    assert(res == 83);

    vector<vector<int>> edges11 = {{1, 0}, {9, 1}, {6, 2}, {7, 4}, {3, 5},
                                   {7, 3}, {9, 6}, {7, 8}, {7, 9}};
    vector<int> values11 = {14, 17, 13, 18, 17, 10, 23, 19, 22, 2};
    res = sol.maximumScoreAfterOperations(edges11, values11);
    cout << res << endl;
    assert(res == 153);

    return 0;
}