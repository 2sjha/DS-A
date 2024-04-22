/*
https://leetcode.com/problems/open-the-lock

You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: `'0', '1', '2',
'3', '4', '5', '6', '7', '8', '9'`. The wheels can rotate freely and wrap around: for example we can
turn `'9'` to be `'0'`, or `'0'` to be
`'9'`. Each move consists of turning one wheel one slot.

The lock initially starts at `'0000'`, a string representing the state of the 4 wheels.

You are given a list of `deadends` dead ends, meaning if the lock displays any of these codes, the
wheels of the lock will stop turning and you will be unable to open it.

Given a `target` representing the value of the wheels that will unlock the lock, return the minimum
total number of turns required to open the lock, or -1 if it is impossible.


**Example 1:**

**Input:** deadends = ["0201","0101","0102","1212","2002"], target = "0202"
**Output:** 6
**Explanation:**
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" ->
"0202". Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

**Example 2:**

**Input:** deadends = ["8888"], target = "0009"
**Output:** 1
**Explanation:** We can turn the last wheel in reverse to move from "0000" -> "0009".

**Example 3:**

**Input:** deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
**Output:** -1
**Explanation:** We cannot reach the target without getting stuck.


**Constraints:**

* `1 <= deadends.length <= 500`
* `deadends[i].length == 4`
* `target.length == 4`
* target **will not be** in the list `deadends`.
* `target` and `deadends[i]` consist of digits only.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    vector<string> getOptions(string &s) {
        vector<string> res;
        for (int i = 0; i < 4; ++i) {
            string s1 = s;
            string s2 = s;

            if (s[i] == '0') {
                s1[i] = '1';
                s2[i] = '9';
            } else if (s[i] == '9') {
                s1[i] = '0';
                s2[i] = '8';
            } else {
                s1[i] = s[i] + 1;
                s2[i] = s[i] - 1;
            }

            res.push_back(s1);
            res.push_back(s2);
        }

        return res;
    }

    unordered_map<string, vector<string>> createOptions() {
        unordered_map<string, vector<string>> options;
        for (int i = 0; i < 10000; ++i) {
            string s;
            if (i < 10) {
                s = "000" + to_string(i);
            } else if (i < 100) {
                s = "00" + to_string(i);
            } else if (i < 1000) {
                s = "0" + to_string(i);
            } else {
                s = to_string(i);
            }

            options[s] = getOptions(s);
        }

        return options;
    }

  public:
    int openLock(vector<string> &deadends, string target) {
        unordered_map<string, vector<string>> options = createOptions();
        set<string> dead_ends;
        for (string d : deadends) {
            dead_ends.insert(d);
        }

        int res = -1;
        if (dead_ends.count("0000"))
            return res;

        unordered_set<string> visited;
        queue<pair<string, int>> bfs_q;
        bfs_q.push({"0000", 0});
        pair<string, int> curr;
        while (!bfs_q.empty()) {
            curr = bfs_q.front();
            bfs_q.pop();

            if (visited.count(curr.first))
                continue;

            visited.insert(curr.first);
            if (curr.first == target) {
                res = curr.second;
                break;
            } else {
                for (string o : options[curr.first]) {
                    if (!visited.count(o) && !dead_ends.count(o)) {
                        bfs_q.push({o, curr.second + 1});
                    }
                }
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<string> deadends_1 = {"0201", "0101", "0102", "1212", "2002"};
    string target_1 = "0202";
    int expected_1 = 6;
    int output_1 = sol.openLock(deadends_1, target_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<string> deadends_2 = {"8888"};
    string target_2 = "0009";
    int expected_2 = 1;
    int output_2 = sol.openLock(deadends_2, target_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    vector<string> deadends_3 = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    string target_3 = "8888";
    int expected_3 = -1;
    int output_3 = sol.openLock(deadends_3, target_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}