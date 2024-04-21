/*
https://leetcode.com/problems/find-if-path-exists-in-graph

There is a **bi-directional** graph with `n` vertices, where each vertex is labeled from `0` to `n -
1` (**inclusive**). The edges in the graph are represented as a 2D integer array `edges`, where each
`edges[i] = [ui, vi]` denotes a bi-directional edge between vertex `ui` and vertex `vi`. Every
vertex pair is connected by **at most one** edge, and no vertex has an edge to itself.

You want to determine if there is a **valid path** that exists from vertex `source` to vertex
`destination`.

Given `edges` and the integers `n`, `source`, and `destination`, return `true`* if there is a
**valid path** from
*`source`* to *`destination`*, or *`false`* otherwise**.*


**Example 1:**

**Input:** n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
**Output:** true
**Explanation:** There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

**Example 2:**

**Input:** n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
**Output:** false
**Explanation:** There is no path from vertex 0 to vertex 5.


**Constraints:**

* `1 <= n <= 2 * 10⁵`
* `0 <= edges.length <= 2 * 10⁵`
* `edges[i].length == 2`
* `0 <= ui, vi <= n - 1`
* `ui != vi`
* `0 <= source, destination <= n - 1`
* There are no duplicate edges.
* There are no self edges.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination) {
        vector<vector<int>> g(n, vector<int>());
        int u, v, curr;

        for (auto edge : edges) {
            u = edge[0];
            v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        bool res = false;
        vector<bool> visited(n, false);
        stack<int> st;
        st.push(source);

        while (!st.empty()) {
            curr = st.top();
            st.pop();
            visited[curr] = true;
            if (curr == destination) {
                res = true;
                break;
            }

            for (auto v : g[curr]) {
                if (!visited[v]) {
                    st.push(v);
                }
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    int n_1 = 3;
    vector<vector<int>> edges_1 = {{0, 1}, {1, 2}, {2, 0}};
    int source_1 = 0;
    int destination_1 = 2;
    bool expected_1 = true;
    bool output_1 = sol.validPath(n_1, edges_1, source_1, destination_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    int n_2 = 6;
    vector<vector<int>> edges_2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    int source_2 = 0;
    int destination_2 = 5;
    bool expected_2 = false;
    bool output_2 = sol.validPath(n_2, edges_2, source_2, destination_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}