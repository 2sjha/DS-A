/*
https://leetcode.com/problems/number-of-students-unable-to-eat-lunch

The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers
`0` and `1` respectively. All students stand in a queue. Each student either prefers square or
circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are
placed in a **stack**. At each step:

* If the student at the front of the queue **prefers** the sandwich on the top of the stack, they
will **take it** and leave the queue.
* Otherwise, they will **leave it** and go to the queue's end.

This continues until none of the queue students want to take the top sandwich and are thus unable to
eat.

You are given two integer arrays `students` and `sandwiches` where `sandwiches[i]` is the type of
the `i^{​​​​​​th}` sandwich in the stack (`i = 0` is the top of the stack) and
`students[j]` is the preference of the `j^{​​​​​​th}` student in the initial queue (`j =
0` is the front of the queue). Return *the number of students that are unable to eat.*


**Example 1:**

**Input:** students = [1,1,0,0], sandwiches = [0,1,0,1]
**Output:** 0**
Explanation:**
- Front student leaves the top sandwich and returns to the end of the line making students =
[1,0,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students =
[0,0,1,1].
- Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches
= [1,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students =
[1,1,0].
- Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches =
[0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
- Front student takes the top sandwich and leaves the line making students = [1] and sandwiches =
[1].
- Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
Hence all students are able to eat.

**Example 2:**

**Input:** students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
**Output:** 3


**Constraints:**

* `1 <= students.length, sandwiches.length <= 100`
* `students.length == sandwiches.length`
* `sandwiches[i]` is `0` or `1`.
* `students[i]` is `0` or `1`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int countStudents(vector<int> &students, vector<int> &sandwiches) {
        int n = students.size();
        queue<int> q;
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            st.push(sandwiches[n - 1 - i]);
            q.push(students[i]);
        }

        bool no_one_wants;
        while (true) {
            no_one_wants = true;
            for (int i = 0; i < q.size() && !q.empty(); ++i) {
                if (st.top() == q.front()) {
                    st.pop();
                    no_one_wants = false;
                } else {
                    q.push(q.front());
                }
                q.pop();
            }

            if (no_one_wants || q.empty()) {
                break;
            }
        }

        return (int)q.size();
    }
};

int main() {
    Solution sol;

    vector<int> students_1 = {1, 1, 0, 0};
    vector<int> sandwiches_1 = {0, 1, 0, 1};
    int expected_1 = 0;
    int output_1 = sol.countStudents(students_1, sandwiches_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> students_2 = {1, 1, 1, 0, 0, 1};
    vector<int> sandwiches_2 = {1, 0, 0, 0, 1, 1};
    int expected_2 = 3;
    int output_2 = sol.countStudents(students_2, sandwiches_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}