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

class Solution {
  private:
    unordered_map<int, long long> substree_sum;

    pair<long long, bool> dfs(unordered_map<int, set<int>> &g, vector<int> &values, int i) {
        // Check if this is a leaf node
        if (g[i].empty()) {
            return {0, false};
        }

        // Returns sum for children and whether to take root or not
        long long sum = 0;
        bool take_root_for_score = true;

        for (int j : g[i]) {
            auto child = dfs(g, values, j);
            if (child.first == 0) {
                if (values[i] < values[j]) {
                    take_root_for_score = false;
                } else if (child.second) {
                    sum += values[j];
                }
            } else {
                if (values[i] < values[j]) {
                    take_root_for_score = false;
                } else {
                    sum += child.first;
                }
            }
        }

        if(!take_root_for_score
         || (sum == 0 && get_sum_subtree(g, values, i) > values[i])
        ) {
            sum = get_sum_subtree(g, values, i);
        } else {
            sum += values[i];
        }

        return {sum, take_root_for_score};
    }

    long long get_sum_subtree(unordered_map<int, set<int>> &g, vector<int> &values, int i) {
        if (substree_sum[i] != -1)
            return substree_sum[i];

        long long sum = 0;
        for (int j : g[i]) {
            sum += values[j];
            sum += get_sum_subtree(g, values, j);
        }
        substree_sum[i] = sum;
        return substree_sum[i];
    }

    void convert_to_dag(unordered_map<int, set<int>> &g, int i) {
        for (int j : g[i]) {
            g[j].erase(i);
        }
        for (int j : g[i]) {
            convert_to_dag(g, j);
        }
    }

  public:
    long long maximumScoreAfterOperations(vector<vector<int>> &edges, vector<int> &values) {
        int n = values.size();
        unordered_map<int, set<int>> g;

        // Init empty graph
        for (int i = 0; i < n; ++i) {
            g[i] = set<int>();
            substree_sum[i] = -1;
        }

        // Setup graph
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];

            g[u].insert(v);
            g[v].insert(u);
        }

        convert_to_dag(g, 0);
        pair<long long, bool> res = dfs(g, values, 0);

        return res.first;
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

    vector<vector<int>> edges9 = {{3,1},{0,2},{0,3}};
    vector<int> values9 = {21,12,19,5};
    res = sol.maximumScoreAfterOperations(edges9, values9);
    cout << res << endl;
    assert(res == 36);

    return 0;
}