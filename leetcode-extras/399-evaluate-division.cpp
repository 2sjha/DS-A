/*
https://leetcode.com/problems/evaluate-division

You are given an array of variable pairs equations and an array of real numbers values, where
equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a
string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must
find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in
division by zero and that there is no contradiction.


Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
[["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]] Output:
[6.00000,0.50000,-1.00000,1.00000,-1.00000] Explanation: Given: a / b = 2.0, b / c = 3.0 queries
are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? return: [6.0, 0.5, -1.0, 1.0, -1.0 ]

Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries =
[["a","c"],["c","b"],["bc","cd"],["cd","bc"]] Output: [3.75000,0.40000,5.00000,0.20000]

Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]


Constraints:

    1 <= equations.length <= 20
    equations[i].length == 2
    1 <= Ai.length, Bi.length <= 5
    values.length == equations.length
    0.0 < values[i] <= 20.0
    1 <= queries.length <= 20
    queries[i].length == 2
    1 <= Cj.length, Dj.length <= 5
    Ai, Bi, Cj, Dj consist of lower case English letters and digits.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    pair<bool, double> reachable(unordered_map<string, vector<pair<string, double>>> &graph,
                                 unordered_map<string, bool> &visited, string u, string v) {
        if (u == v) {
            return {true, 1.0};
        }
        if (visited[u]) {
            return {false, -1.0};
        }
        visited[u] = true;
        bool found = false;
        double value = -1.0;
        pair<bool, double> tmp;
        for (auto edge : graph[u]) {
            if (!visited[edge.first]) {
                tmp = reachable(graph, visited, edge.first, v);
                found |= tmp.first;
                if (found) {
                    value = tmp.second * edge.second;
                    break;
                }
            }
        }

        return {found, value};
    }

  public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values,
                                vector<vector<string>> &queries) {
        int n = queries.size();
        vector<double> res = vector<double>(n, -1.0);

        // build graph
        unordered_map<string, vector<pair<string, double>>> graph;
        int m = equations.size();
        string u, v;
        double weight;

        for (int i = 0; i < m; ++i) {
            u = equations[i][0];
            v = equations[i][1];
            weight = values[i];

            if (!graph.count(u)) {
                graph[u] = vector<pair<string, double>>();
            }
            if (!graph.count(v)) {
                graph[v] = vector<pair<string, double>>();
            }

            graph[u].push_back({v, weight});
            graph[v].push_back({u, 1 / weight});
        }

        // evaluate queries
        pair<bool, double> res_i;
        unordered_map<string, bool> visited;
        for (int i = 0; i < n; ++i) {
            u = queries[i][0];
            v = queries[i][1];

            if (!graph.count(u) || !graph.count(v)) {
                res[i] = -1.0;
            } else {
                visited.clear();
                res_i = reachable(graph, visited, u, v);
                if (res_i.first) {
                    res[i] = res_i.second;
                }
            }
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<double> res;

    vector<vector<string>> equations1 = {{"a", "b"}, {"b", "c"}};
    vector<double> values1 = {2.0, 3.0};
    vector<vector<string>> queries1 = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    res = sol.calcEquation(equations1, values1, queries1);
    printArray(res);
    assert(res == vector<double>({6.00000, 0.50000, -1.00000, 1.00000, -1.00000}));

    vector<vector<string>> equations2 = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
    vector<double> values2 = {1.5, 2.5, 5.0};
    vector<vector<string>> queries2 = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
    res = sol.calcEquation(equations2, values2, queries2);
    printArray(res);
    assert(res == vector<double>({3.75000, 0.40000, 5.00000, 0.20000}));

    vector<vector<string>> equations3 = {{"a", "b"}};
    vector<double> values3 = {0.5};
    vector<vector<string>> queries3 = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
    res = sol.calcEquation(equations3, values3, queries3);
    printArray(res);
    assert(res == vector<double>({0.50000, 2.00000, -1.00000, -1.00000}));

    return 0;
}