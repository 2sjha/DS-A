/*
https://leetcode.com/problems/task-scheduler/

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter
represents a different task. Tasks could be done in any order. Each task is done in one unit of
time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same
tasks (the same letter in the array), that is that there must be at least n units of time between
any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.


Example 1:

Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation:
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.

Example 2:

Input: tasks = ['A','A','A','B','B','B'], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
['A','A','A','B','B','B']
['A','B','A','B','A','B']
['B','B','B','A','A','A']
...
And so on.

Example 3:

Input: tasks = ['A','A','A','A','A','A','B','C','D','E','F','G'], n = 2
Output: 16
Explanation:
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A


Constraints:
    1 <= task.length <= 10^4
    tasks[i] is upper-case English letter.
    The integer n is in the range [0, 100].
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int leastInterval(vector<char> &tasks, int n) {
        map<char, int> tasks_c;
        int idle = 0;

        for (char task : tasks) {
            tasks_c[task]++;
        }

        multiset<int> tasks_n;
        for (auto entry : tasks_c) {
            tasks_n.insert(entry.second);
        }

        while (!tasks_n.empty()) {
            int tasks_done = 0;
            int curr_idle = 0;
            multiset<int> tasks_nc;

            auto iter = tasks_n.rbegin();
            int idx = 0;
            for (; idx < tasks_n.size(); iter++, idx++) {
                if (*iter > 1) {
                    tasks_nc.insert(*iter - 1);
                }

                tasks_done++;
                if (tasks_done == n + 1) {
                    iter++;
                    idx++;
                    break;
                }
            }

            for (; idx < tasks_n.size(); iter++, idx++) {
                tasks_nc.insert(*iter);
            }

            tasks_n = tasks_nc;
            if (!tasks_n.empty() && tasks_done < n + 1) {
                curr_idle = n + 1 - tasks_done;
            }

            idle += curr_idle;
        }

        return tasks.size() + idle;
    }
};

int main() {
    Solution sol;
    int res;

    int n1 = 2;
    vector<char> tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    res = sol.leastInterval(tasks1, n1);
    cout << res << endl;
    assert(res == 8);

    int n2 = 0;
    vector<char> tasks2 = {'A', 'A', 'A', 'B', 'B', 'B'};
    res = sol.leastInterval(tasks2, n2);
    cout << res << endl;
    assert(res == 6);

    int n3 = 2;
    vector<char> tasks3 = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    res = sol.leastInterval(tasks3, n3);
    cout << res << endl;
    assert(res == 16);

    return 0;
}