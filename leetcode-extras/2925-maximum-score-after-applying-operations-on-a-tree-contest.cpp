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
    pair<long long, bool> dfs(unordered_map<int, set<int>> &g, vector<int> &values, int i) {
        // Check if this is a leaf node
        if (g[i].empty()) {
            return {0, false};
        }

        // Returns sum for children and whether to take root or not
        long long sum = 0;
        bool take_root_for_score = false;

        for (int j : g[i]) {
            auto child = dfs(g, values, j);
            if(child.first == 0) {
                if(values[j] < values[i]) {
                    take_root_for_score = true;
                } else {
                    sum += values[j];
                }
            } else {
                
            }
        }
  
        return {sum, take_root_for_score};
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
        vector<int> dp(n, 0);

        // Init empty graph
        for (int i = 0; i < n; ++i) {
            g[i] = set<int>();
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
        if (res.second) {
            res.first += values[0];
        }

        return res.first;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> edges1 = {{7, 0}, {3, 1}, {6, 2}, {4, 3}, {4, 5}, {4, 6}, {4, 7}};
    vector<int> values1 = {2, 16, 23, 17, 22, 21, 8, 6};
    res = sol.maximumScoreAfterOperations(edges1, values1);
    cout << res << endl;
    assert(res == 113);

    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {0, 3}, {2, 4}, {4, 5}};
    vector<int> values2 = {5, 2, 5, 2, 1, 1};
    res = sol.maximumScoreAfterOperations(edges2, values2);
    cout << res << endl;
    assert(res == 11);

    vector<vector<int>> edges3 = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
    vector<int> values3 = {20, 10, 9, 7, 4, 3, 5};
    res = sol.maximumScoreAfterOperations(edges2, values2);
    cout << res << endl;
    assert(res == 40);

    return 0;
}