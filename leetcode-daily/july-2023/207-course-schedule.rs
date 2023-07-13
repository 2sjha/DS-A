/*
https://leetcode.com/problems/course-schedule/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

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
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.


Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.
*/

// The idea to detect cycles in a directed graph is to have 2 visited arrays,
// One for normal DFS, and other to check if a vertex has an edge to another vertex which is in its dfs stack
struct Solution;
impl Solution {
    fn dfs_detect_cycle(
        n: usize,
        u: usize,
        graph: &Vec<Vec<usize>>,
        mut visited: &mut Vec<bool>,
        mut rec_stack: &mut Vec<bool>,
    ) -> bool {
        if visited[u] && rec_stack[u] {
            return true;
        } else if visited[u] {
            return false;
        }

        visited[u] = true;
        rec_stack[u] = true;

        let mut cycle: bool = false;
        for v in graph[u].iter() {
            cycle |= Self::dfs_detect_cycle(
                n,
                *v,
                &graph,
                &mut visited,
                &mut rec_stack,
            );
        }
        rec_stack[u] = false;

        return cycle;
    }

    pub fn can_finish(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> bool {
        let n: usize = num_courses as usize;
        let mut graph: Vec<Vec<usize>> = vec![vec![]; n];
        let mut visited: Vec<bool> = vec![false; n];
        let mut rec_stack: Vec<bool> = vec![false; n];

        for prereq in prerequisites.iter() {
            graph[prereq[0] as usize].push(prereq[1] as usize);
        }

        let mut all: bool = true;
        for i in 0..n {
            all &= !Self::dfs_detect_cycle(
                n,
                i,
                &graph,
                &mut visited,
                &mut rec_stack,
            );
            if !all {
                break;
            }
        }

        return all;
    }
}

fn main() {
    let mut res: bool;
    let mut num_courses: i32;
    let mut prerequisites: Vec<Vec<i32>>;

    num_courses = 2;
    prerequisites = vec![vec![1, 0]];
    res = Solution::can_finish(num_courses, prerequisites);
    println!("{:?}", res);
    assert!(res == true);

    num_courses = 2;
    prerequisites = vec![vec![1, 0], vec![0, 1]];
    res = Solution::can_finish(num_courses, prerequisites);
    println!("{:?}", res);
    assert!(res == false);

    num_courses = 5;
    prerequisites = vec![vec![1, 4], vec![2, 4], vec![3, 1], vec![3, 2]];
    res = Solution::can_finish(num_courses, prerequisites);
    println!("{:?}", res);
    assert!(res == true);
}
