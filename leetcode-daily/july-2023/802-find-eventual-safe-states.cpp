/*
https://leetcode.com/problems/find-eventual-safe-states/

There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is
represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes
adjacent to node i, meaning there is an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible
path starting from that node leads to a terminal node (or another safe node).

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending
order.


Example 1:
Illustration of graph

Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:

Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.


Constraints:

    n == graph.length
    1 <= n <= 104
    0 <= graph[i].length <= n
    0 <= graph[i][j] <= n - 1
    graph[i] is sorted in a strictly increasing order.
    The graph may contain self-loops.
    The number of edges in the graph will be in the range [1, 4 * 104].
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool dfs_safe(vector<vector<int>> &graph, int u, vector<bool> &visited, vector<bool> &safe) {
        if (visited[u]) {
            return safe[u];
        }

        visited[u] = true;
        bool is_u_safe = true;
        bool is_v_safe;
        for (int v : graph[u]) {
            is_v_safe = dfs_safe(graph, v, visited, safe);
            if (is_v_safe) {
                safe[v] = true;
            }
            is_u_safe = is_u_safe && is_v_safe;
        }

        if (is_u_safe) {
            safe[u] = true;
        }
        return is_u_safe;
    }

  public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        int n = graph.size();
        vector<bool> safe(n, false);

        // Mark terminaal nodes as safe;
        for (int i = 0; i < n; ++i) {
            safe[i] = graph[i].empty();
        }

        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            dfs_safe(graph, i, visited, safe);
        }

        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (safe[i]) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> res;

    vector<vector<int>> graph1 = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    res = sol.eventualSafeNodes(graph1);
    printArray(res);

    vector<vector<int>> graph2 = {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}};
    res = sol.eventualSafeNodes(graph2);
    printArray(res);

    return 0;
}