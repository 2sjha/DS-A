/*
https://leetcode.com/problems/number-of-students-unable-to-eat-lunch

The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers `0` and `1`
respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a **stack**.
At each step:

* If the student at the front of the queue **prefers** the sandwich on the top of the stack, they will **take it** and
  leave the queue.
* Otherwise, they will **leave it** and go to the queue's end.

This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

You are given two integer arrays `students` and `sandwiches` where `sandwiches[i]` is the type of the `i^{​​​​​​th}` sandwich
in the stack (`i = 0` is the top of the stack) and `students[j]` is the preference of the `j^{​​​​​​th}` student in the
initial queue (`j = 0` is the front of the queue). Return *the number of students that are unable to eat.*


**Example 1:**

**Input:** students = [1,1,0,0], sandwiches = [0,1,0,1]
**Output:** 0**
Explanation:**
- Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
- Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
- Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
- Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
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

use std::collections::VecDeque;

struct Solution;
impl Solution {
    pub fn count_students(students: Vec<i32>, sandwiches: Vec<i32>) -> i32 {
        let n: usize = students.len();
        let mut q: VecDeque<i32> = VecDeque::new();
        let mut st: Vec<i32> = Vec::new();

        for i in 0..n {
            q.push_back(students[i]);
            st.push(sandwiches[n - 1 - i]);
        }

        let mut no_one_wants: bool = false;
        while !no_one_wants && q.len() != 0 {
            no_one_wants = true;
            for _ in 0..q.len() {
                if q.len() == 0 {
                    break;
                }

                if *st.last().unwrap() == *q.front().unwrap() {
                    no_one_wants = false;
                    st.pop();
                } else {
                    q.push_back(*q.front().unwrap());
                }
                q.pop_front();
            }
        }

        q.len() as i32
    }
}

fn main() {
    let students_1: Vec<i32> = vec![1, 1, 0, 0];
    let sandwiches_1: Vec<i32> = vec![0, 1, 0, 1];
    let expected_1: i32 = 0;
    let output_1: i32 = Solution::count_students(students_1, sandwiches_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let students_2: Vec<i32> = vec![1, 1, 1, 0, 0, 1];
    let sandwiches_2: Vec<i32> = vec![1, 0, 0, 0, 1, 1];
    let expected_2: i32 = 3;
    let output_2: i32 = Solution::count_students(students_2, sandwiches_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
