/*
https://leetcode.com/problems/number-of-provinces/

There are n cities. Some of them are connected, while some are not. If city a is connected directly
with city b, and city b is connected directly with city c, then city a is connected indirectly with
city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the
group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth
city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.


Example 1:

Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Example 2:

Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3


Constraints:

    1 <= n <= 200
    n == isConnected.length
    n == isConnected[i].length
    isConnected[i][j] is 1 or 0.
    isConnected[i][i] == 1
    isConnected[i][j] == isConnected[j][i]
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    vector<bool> visited;

  private:
    int numReachable(vector<vector<int>> &isConnected, int i) {
        if (visited[i]) {
            return 0;
        }

        queue<int> bfs_q;
        bfs_q.push(i);

        while (!bfs_q.empty()) {
            int curr = bfs_q.front();
            bfs_q.pop();

            if (visited[curr]) {
                continue;
            }
            visited[curr] = true;

            for (int j = 0; j < isConnected.size(); ++j) {
                if (isConnected[curr][j] == 1 and !visited[j]) {
                    bfs_q.push(j);
                }
            }
        }

        return 1;
    }

  public:
    int findCircleNum(vector<vector<int>> &isConnected) {
        visited = vector<bool>();
        for (int i = 0; i < isConnected.size(); ++i) {
            visited.push_back(false);
        }

        int numProvinces = 0;

        for (int i = 0; i < isConnected.size(); ++i) {
            numProvinces += numReachable(isConnected, i);
        }

        return numProvinces;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> isConnected1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    res = sol.findCircleNum(isConnected1);
    cout << res << endl;
    assert(res == 2);

    vector<vector<int>> isConnected2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    res = sol.findCircleNum(isConnected2);
    cout << res << endl;
    assert(res == 3);

    return 0;
}