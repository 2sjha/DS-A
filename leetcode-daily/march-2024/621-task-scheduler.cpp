/*
https://leetcode.com/problems/task-scheduler

You are given an array of CPU `tasks`, each represented by letters A to Z, and a cooling time, `n`.
Each cycle or interval allows the completion of one task. Tasks can be completed in any order, but
there's a constraint: **identical** tasks must be separated by at least `n` intervals due to cooling
time.

​Return the *minimum number of intervals* required to complete all tasks.


**Example 1:**

**Input:** tasks = ["A","A","A","B","B","B"], n = 2

**Output:** 8

**Explanation:** A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.

After completing task A, you must wait two cycles before doing A again. The same applies to task B.
In the 3^{rd} interval, neither A nor B can be done, so you idle. By the 4^{th} cycle, you can do A
again as 2 intervals have passed.

**Example 2:**

**Input:** tasks = ["A","C","A","B","D","B"], n = 1

**Output:** 6

**Explanation:** A possible sequence is: A -> B -> C -> D -> A -> B.

With a cooling interval of 1, you can repeat a task after just one other task.

**Example 3:**

**Input:** tasks = ["A","A","A", "B","B","B"], n = 3

**Output:** 10

**Explanation:** A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.

There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to
idling twice between repetitions of these tasks.


**Constraints:**

* `1 <= tasks.length <= 10⁴`
* `tasks[i]` is an uppercase English letter.
* `0 <= n <= 100`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    bool allTasksDone(vector<int> &freq) {
        for (int i = 0; i < freq.size(); ++i) {
            if (freq[i] > 0)
                return false;
        }
        return true;
    }

  public:
    int leastInterval(vector<char> &tasks, int n) {
        vector<int> freq(26, 0);
        for (char t : tasks) {
            freq[t - 'A']++;
        }

        int cnt = 0;
        while (true) {
            sort(freq.begin(), freq.end());
            reverse(freq.begin(), freq.end());

            int curr_cycle = 0;
            for (int i = 0; i < 26; ++i) {
                if (freq[i] > 0) {
                    curr_cycle++;
                    freq[i]--;
                }
                if (curr_cycle > n)
                    break;
            }
            cnt += curr_cycle;
            if (allTasksDone(freq))
                break;
            cnt += max(0, n + 1 - curr_cycle);
        }

        return cnt;
    }
};

int main() {
    Solution sol;

    vector<char> tasks_1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n_1 = 2;
    int expected_1 = 8;
    int output_1 = sol.leastInterval(tasks_1, n_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<char> tasks_2 = {'A', 'C', 'A', 'B', 'D', 'B'};
    int n_2 = 1;
    int expected_2 = 6;
    int output_2 = sol.leastInterval(tasks_2, n_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<char> tasks_3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n_3 = 3;
    int expected_3 = 10;
    int output_3 = sol.leastInterval(tasks_3, n_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}