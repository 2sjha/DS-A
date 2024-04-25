/*
https://leetcode.com/problems/minimum-height-trees

A tree is an undirected graph in which any two vertices are connected by *exactly* one path. In
other words, any connected graph without simple cycles is a tree.

Given a tree of `n` nodes labelled from `0` to `n - 1`, and an array of `n - 1` `edges` where
`edges[i] = [ai, bi]` indicates that there is an undirected edge between the two nodes `ai` and `bi`
in the tree, you can choose any node of the tree as the root. When you select a node `x` as the
root, the result tree has height `h`. Among all possible rooted trees, those with minimum height
(i.e. `min(h)`) are called **minimum height trees** (MHTs).

Return *a list of all **MHTs'** root labels*. You can return the answer in **any order**.

The **height** of a rooted tree is the number of edges on the longest downward path between the root
and a leaf.


**Example 1:**

**Input:** n = 4, edges = [[1,0],[1,2],[1,3]]
**Output:** [1]
**Explanation:** As shown, the height of the tree is 1 when the root is the node with label 1 which
is the only MHT.

**Example 2:**

**Input:** n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
**Output:** [3,4]


**Constraints:**

* `1 <= n <= 2 * 10⁴`
* `edges.length == n - 1`
* `0 <= ai, bi < n`
* `ai != bi`
* All the pairs `(ai, bi)` are distinct.
* The given input is **guaranteed** to be a tree and there will be **no repeated** edges.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    pair<int, int> findFarthestLeaf(vector<vector<int>> &g, int src) {
        int n = g.size(), farthest_leaf = src, max_dist = INT_MIN;
        vector<bool> visited(n, false);
        stack<pair<int, int>> st;
        st.push({src, 0});

        while (!st.empty()) {
            pair<int, int> curr = st.top();
            st.pop();

            if (visited[curr.first])
                continue;
            visited[curr.first] = true;
            if (g[curr.first].size() == 1) {
                if (curr.second > max_dist) {
                    farthest_leaf = curr.first;
                    max_dist = curr.second;
                }
            }

            for (int v : g[curr.first]) {
                if (!visited[v]) {
                    st.push({v, curr.second + 1});
                }
            }
        }

        return {farthest_leaf, max_dist};
    }

    bool find(vector<vector<int>> &g, int node, int target, int dist_so_far, vector<int> &visited,
              vector<pair<int, int>> &path) {
        visited[node] = true;
        if (node == target) {
            path.push_back({node, dist_so_far});
            return true;
        } else {
            for (int v : g[node]) {
                if (!visited[v]) {
                    if (find(g, v, target, dist_so_far + 1, visited, path)) {
                        path.push_back({node, dist_so_far});
                        return true;
                    }
                }
            }

            return false;
        }
    }

    vector<pair<int, int>> find_path(vector<vector<int>> &g, int src, int target) {
        int n = g.size();
        vector<int> visited(n, false);
        vector<pair<int, int>> path;
        find(g, src, target, 0, visited, path);
        return path;
    }

  public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
        if (n == 1) {
            return {0};
        }

        vector<vector<int>> g(n, vector<int>());
        for (auto edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        pair<int, int> leaf_1 = findFarthestLeaf(g, 0);
        pair<int, int> leaf_2 = findFarthestLeaf(g, leaf_1.first);
        int max_dist = leaf_2.second;
        vector<pair<int, int>> longest_path = find_path(g, leaf_1.first, leaf_2.first);
        int min_height = INT_MAX;
        for (auto node : longest_path) {
            min_height = min(min_height, max(node.second, max_dist - node.second));
        }

        vector<int> res;
        for (auto node : longest_path) {
            if (max(node.second, max_dist - node.second) == min_height) {
                res.push_back(node.first);
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    int n_1 = 4;
    vector<vector<int>> edges_1 = {{1, 0}, {1, 2}, {1, 3}};
    vector<int> expected_1 = {1};
    vector<int> output_1 = sol.findMinHeightTrees(n_1, edges_1);
    printArray(output_1);
    assert(output_1 == expected_1);

    int n_2 = 6;
    vector<vector<int>> edges_2 = {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
    vector<int> expected_2 = {3, 4};
    vector<int> output_2 = sol.findMinHeightTrees(n_2, edges_2);
    printArray(output_2);
    assert(output_2 == expected_2);

    int n_3 = 2;
    vector<vector<int>> edges_3 = {{0, 1}};
    vector<int> expected_3 = {0, 1};
    vector<int> output_3 = sol.findMinHeightTrees(n_3, edges_3);
    printArray(output_3);
    assert(output_3 == expected_3);

    return 0;
}