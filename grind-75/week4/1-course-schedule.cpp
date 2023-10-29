/*
https://leetcode.com/problems/course-schedule/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are
given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course
bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.


Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.

Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should also have
finished course 1. So it is impossible.


Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.
*/

/*
This question just needs us to detect if a cycle is present
in the generated graph.
We can use Topological Sorting using BFS (Kahn's Algorithm) to produce a topological sort.
If we fail to generate a topo sort, then the graph has a cycle.
https://en.wikipedia.org/wiki/Topological_sorting

Or

We can use DFS to detect a cycle in a graph using 2 visited arrays, perma_visited and tmp_visited.
We use perma_visited normally, marking the vertex as visited after the visit is complete.
But in each DFS visit, we mark the vertex as tmp_visited and then visit all adjacent nodes
recursively like in a normal DFS. In each recursive call, we first check if this node already has a
tmp_visit, which means that a parent node that was tmp_visited has triggered the DFS, and an
adjacent node points to a node in the same DFS call stack. That means there is a cycle. If that
doesn't happen, then after the DFS visit has been completed on all adjacent nodes, we remove the
tmp_visit and mark it as perma_visited.
This is also a method to generate a Topo Sort.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<vector<int>> createGraph(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> adj_list;
        for (int i = 0; i < numCourses; ++i) {
            vector<int> empty_adj_list;
            adj_list.push_back(empty_adj_list);
        }

        for (vector<int> edge : prerequisites) {
            int u = edge[0];
            int v = edge[1];
            adj_list[u].push_back(v);
        }
        return adj_list;
    }

    bool visitDFS(vector<vector<int>> &adj_list, int vertex, vector<bool> &tmp_visited,
                  vector<bool> &perma_visited) {
        if (tmp_visited[vertex] == true) {
            return false;
        }

        tmp_visited[vertex] = true;

        for (int adj_vertex : adj_list[vertex]) {
            if (perma_visited[adj_vertex] == false and
                visitDFS(adj_list, adj_vertex, tmp_visited, perma_visited) == false) {
                return false;
            }
        }

        tmp_visited[vertex] = false;
        perma_visited[vertex] = true;

        return true;
    }

    bool canFinishDFS(vector<vector<int>> adj_list) {
        int n = adj_list.size();
        vector<bool> perma_visited(n, false);
        vector<bool> tmp_visited(n, false);
        bool res = true;

        for (int i = 0; i < n; ++i) {
            if (perma_visited[i] == false and
                visitDFS(adj_list, i, tmp_visited, perma_visited) == false) {
                return false;
            }
        }

        return true;
    }

    bool canFinishBFS(vector<vector<int>> adj_list) {
        int n = adj_list.size();
        vector<int> in_degree(n, 0);

        for (vector<int> adj_vertices : adj_list) {
            for (int v : adj_vertices) {
                in_degree[v]++;
            }
        }

        queue<int> in_degree_0;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                in_degree_0.push(i);
            }
        }

        while (!in_degree_0.empty()) {
            int v = in_degree_0.front();
            in_degree_0.pop();

            for (int adj_v : adj_list[v]) {
                in_degree[adj_v]--;
                if (in_degree[adj_v] == 0) {
                    in_degree_0.push(adj_v);
                }
            }
        }

        for (int in : in_degree) {
            if (in != 0) {
                return false;
            }
        }

        return true;
    }

    bool canFinish(int numCourses, vector<vector<int>> prerequisites) {
        vector<vector<int>> adj_list = createGraph(numCourses, prerequisites);

        return canFinishDFS(adj_list) and canFinishBFS(adj_list);
    }
};

int main() {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}};

    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}, {0, 1}};

    int numCourses = 5;
    vector<vector<int>> prerequisites = {{1, 4}, {2, 4}, {3, 1}, {3, 2}};

    Solution sol;
    bool res = sol.canFinish(numCourses, prerequisites);
    cout << res << endl;
    return 0;
}