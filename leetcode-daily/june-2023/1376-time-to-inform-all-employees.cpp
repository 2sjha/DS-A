/*
https://leetcode.com/problems/time-needed-to-inform-all-employees/

A company has n employees with a unique ID for each employee from 0 to n - 1. The head of the
company is the one with headID.

Each employee has one direct manager given in the manager array where manager[i] is the direct
manager of the i-th employee, manager[headID] = -1. Also, it is guaranteed that the subordination
relationships have a tree structure.

The head of the company wants to inform all the company employees of an urgent piece of news. He
will inform his direct subordinates, and they will inform their subordinates, and so on until all
employees know about the urgent news.

The i-th employee needs informTime[i] minutes to inform all of his direct subordinates (i.e., After
informTime[i] minutes, all his direct subordinates can start spreading the news).

Return the number of minutes needed to inform all the employees about the urgent news.


Example 1:

Input: n = 1, headID = 0, manager = [-1], informTime = [0]
Output: 0
Explanation: The head of the company is the only employee in the company.

Example 2:

Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
Output: 1
Explanation: The head of the company with id = 2 is the direct manager of all the employees in the
company and needs 1 minute to inform them all. The tree structure of the employees in the company is
shown.


Constraints:

    1 <= n <= 105
    0 <= headID < n
    manager.length == n
    0 <= manager[i] < n
    manager[headID] == -1
    informTime.length == n
    0 <= informTime[i] <= 1000
    informTime[i] == 0 if employee i has no subordinates.
    It is guaranteed that all the employees can be informed.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    unordered_map<int, vector<int>> orgTree;

  private:
    void build_tree(int n, vector<int> &manager) {
        orgTree = unordered_map<int, vector<int>>();

        for (int i = 0; i < n; ++i) {
            orgTree[i] = vector<int>();
        }

        for (int i = 0; i < n; ++i) {
            if (manager[i] == -1) {
                continue;
            }

            orgTree[manager[i]].push_back(i);
        }
    }

    int dfs(int headId, vector<int> &informTime) {
        int iTime = informTime[headId];
        int max_sub_iTime = 0;
        for (int sub : orgTree[headId]) {
            int sub_iTime = dfs(sub, informTime);
            max_sub_iTime = max(max_sub_iTime, sub_iTime);
        }
        return iTime + max_sub_iTime;
    }

  public:
    int numOfMinutes(int n, int headID, vector<int> &manager, vector<int> &informTime) {
        if (n == 1) {
            return informTime[0];
        }

        build_tree(n, manager);

        return dfs(headID, informTime);
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> manager1 = {-1};
    vector<int> informTime1 = {0};
    res = sol.numOfMinutes(1, 0, manager1, informTime1);
    cout << res << endl;
    assert(res == 0);

    vector<int> manager2 = {2, 2, -1, 2, 2, 2};
    vector<int> informTime2 = {0, 0, 1, 0, 0, 0};
    res = sol.numOfMinutes(6, 2, manager2, informTime2);
    cout << res << endl;
    assert(res == 1);

    return 0;
}