/*
https://leetcode.com/problems/path-with-maximum-probability/

You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where
edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success
of traversing that edge succProb[i].

Given two nodes start and end, find the path with the maximum probability of success to go from
start to end and return its success probability.

If there is no path from start to end, return 0. Your answer will be accepted if it differs from the
correct answer by at most 1e-5.


Example 1:

Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and
the other has 0.5 * 0.5 = 0.25.

Example 2:

Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000

Example 3:

Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.


Constraints:

    2 <= n <= 10^4
    0 <= start, end < n
    start != end
    0 <= a, b < n
    a != b
    0 <= succProb.length == edges.length <= 2*10^4
    0 <= succProb[i] <= 1
    There is at most one edge between every two nodes.
*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start,
                          int end) {
        unordered_map<int, vector<pair<double, int>>> g;
        vector<int> edge;
        for (int i = 0; i < edges.size(); ++i) {
            edge = edges[i];
            if (g.find(edge[0]) == g.end()) {
                g[edge[0]] = vector<pair<double, int>>();
            }
            if (g.find(edge[1]) == g.end()) {
                g[edge[1]] = vector<pair<double, int>>();
            }
            g[edge[0]].push_back({succProb[i], edge[1]});
            g[edge[1]].push_back({succProb[i], edge[0]});
        }

        priority_queue<pair<double, int>> pq;
        vector<double> probs(n, 0);
        probs[start] = 1;
        pq.push({probs[start], start});

        pair<double, int> curr;
        double curr_u_prob, curr_edge_prob;
        int curr_u, curr_edge_v;
        while (!pq.empty()) {
            curr = pq.top();
            pq.pop();
            curr_u = curr.second;
            curr_u_prob = curr.first;

            for (pair<double, int> edgeWithProb : g[curr_u]) {
                curr_edge_v = edgeWithProb.second;
                curr_edge_prob = edgeWithProb.first;

                if (curr_u_prob * curr_edge_prob > probs[curr_edge_v]) {
                    probs[curr_edge_v] = curr_u_prob * curr_edge_prob;
                    pq.push({probs[curr_edge_v], curr_edge_v});
                }
            }
        }

        return probs[end];
    }
};

int main() {
    Solution sol;
    double res;
    int n, start, end;

    n = 3;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {0, 2}};
    vector<double> succProb1 = {0.5, 0.5, 0.2};
    start = 0;
    end = 2;
    res = sol.maxProbability(n, edges1, succProb1, start, end);
    cout << res << endl;
    assert(res == 0.25);

    n = 3;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {0, 2}};
    vector<double> succProb2 = {0.5, 0.5, 0.3};
    start = 0;
    end = 2;
    res = sol.maxProbability(n, edges2, succProb2, start, end);
    cout << res << endl;
    assert(res == 0.3);

    n = 3;
    vector<vector<int>> edges3 = {{0, 1}};
    vector<double> succProb3 = {0.5};
    start = 0;
    end = 2;
    res = sol.maxProbability(n, edges3, succProb3, start, end);
    cout << res << endl;
    assert(res == 0);

    return 0;
}