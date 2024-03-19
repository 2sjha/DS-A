/*
https://leetcode.com/problems/task-scheduler

You are given an array of CPU `tasks`, each represented by letters A to Z, and a cooling time, `n`. Each cycle or
interval allows the completion of one task. Tasks can be completed in any order, but there's a constraint: **identical**
tasks must be separated by at least `n` intervals due to cooling time.

​Return the *minimum number of intervals* required to complete all tasks.


**Example 1:**

**Input:** tasks = ["A","A","A","B","B","B"], n = 2

**Output:** 8

**Explanation:** A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.

After completing task A, you must wait two cycles before doing A again. The same applies to task B. In the 3^{rd}
interval, neither A nor B can be done, so you idle. By the 4^{th} cycle, you can do A again as 2 intervals have passed.

**Example 2:**

**Input:** tasks = ["A","C","A","B","D","B"], n = 1

**Output:** 6

**Explanation:** A possible sequence is: A -> B -> C -> D -> A -> B.

With a cooling interval of 1, you can repeat a task after just one other task.

**Example 3:**

**Input:** tasks = ["A","A","A", "B","B","B"], n = 3

**Output:** 10

**Explanation:** A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.

There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to idling twice
between repetitions of these tasks.


**Constraints:**

* `1 <= tasks.length <= 10⁴`
* `tasks[i]` is an uppercase English letter.
* `0 <= n <= 100`
*/

struct Solution;
impl Solution {
    fn all_tasks_done(freq: &Vec<i32>) -> bool {
        for i in 0..26 {
            if freq[i] > 0 {
                return false;
            }
        }
        return true;
    }
    pub fn least_interval(tasks: Vec<char>, n: i32) -> i32 {
        let mut freq: Vec<i32> = vec![0; 26];
        for t in tasks {
            freq[t as usize - 'A' as usize] += 1;
        }

        let mut res: i32 = 0;
        loop {
            freq.sort();
            freq.reverse();
            let mut curr: i32 = 0;
            for i in 0..26 {
                if freq[i] > 0 {
                    curr += 1;
                    freq[i] -= 1;
                }
                if curr > n {
                    break;
                }
            }
            res += curr;
            if Self::all_tasks_done(&freq) {
                break;
            }
            res += std::cmp::max(0, n + 1 - curr);
        }

        res
    }
}

fn main() {
	let tasks_1: Vec<char> = vec!['A','A','A','B','B','B'];
	let n_1: i32 = 2;
	let expected_1: i32 = 8;
	let output_1: i32 = Solution::least_interval(tasks_1, n_1);
	println!("{:?}", output_1);
	assert!(output_1 == expected_1);

	let tasks_2: Vec<char> = vec!['A','C','A','B','D','B'];
	let n_2: i32 = 1;
	let expected_2: i32 = 6;
	let output_2: i32 = Solution::least_interval(tasks_2, n_2);
	println!("{:?}", output_2);
	assert!(output_2 == expected_2);

	let tasks_3: Vec<char> = vec!['A','A','A', 'B','B','B'];
	let n_3: i32 = 3;
	let expected_3: i32 = 10;
	let output_3: i32 = Solution::least_interval(tasks_3, n_3);
	println!("{:?}", output_3);
	assert!(output_3 == expected_3);

}
