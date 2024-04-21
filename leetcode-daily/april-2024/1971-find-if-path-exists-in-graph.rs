/*
https://leetcode.com/problems/find-if-path-exists-in-graph

There is a **bi-directional** graph with `n` vertices, where each vertex is labeled from `0` to `n - 1` (**inclusive**).
The edges in the graph are represented as a 2D integer array `edges`, where each `edges[i] = [ui, vi]` denotes a
bi-directional edge between vertex `ui` and vertex `vi`. Every vertex pair is connected by **at most one** edge, and no
vertex has an edge to itself.

You want to determine if there is a **valid path** that exists from vertex `source` to vertex `destination`.

Given `edges` and the integers `n`, `source`, and `destination`, return `true`* if there is a **valid path** from
*`source`* to *`destination`*, or *`false`* otherwise**.*


**Example 1:**

**Input:** n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
**Output:** true
**Explanation:** There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

**Example 2:**

**Input:** n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
**Output:** false
**Explanation:** There is no path from vertex 0 to vertex 5.


**Constraints:**

* `1 <= n <= 2 * 10⁵`
* `0 <= edges.length <= 2 * 10⁵`
* `edges[i].length == 2`
* `0 <= ui, vi <= n - 1`
* `ui != vi`
* `0 <= source, destination <= n - 1`
* There are no duplicate edges.
* There are no self edges.
*/

struct Solution;
impl Solution {
    pub fn valid_path(
        n: i32,
        edges: Vec<Vec<i32>>,
        source: i32,
        destination: i32,
    ) -> bool {
        let mut g: Vec<Vec<i32>> = vec![vec![]; n as usize];
        for edge in &edges {
            let u: i32 = edge[0];
            let v: i32 = edge[1];
            g[u as usize].push(v);
            g[v as usize].push(u);
        }

        let mut visited: Vec<bool> = vec![false; n as usize];
        let mut st: Vec<i32> = Vec::new();
        st.push(source);

        while st.len() != 0 {
            let curr: i32 = st.pop().unwrap();
            visited[curr as usize] = true;

            if curr == destination {
                return true;
            }

            for v in &g[curr as usize] {
                if !visited[*v as usize] {
                    st.push(*v);
                }
            }
        }

        false
    }
}
fn main() {
    let n_1: i32 = 3;
    let edges_1: Vec<Vec<i32>> = vec![vec![0, 1], vec![1, 2], vec![2, 0]];
    let source_1: i32 = 0;
    let destination_1: i32 = 2;
    let expected_1: bool = true;
    let output_1: bool =
        Solution::valid_path(n_1, edges_1, source_1, destination_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let n_2: i32 = 6;
    let edges_2: Vec<Vec<i32>> =
        vec![vec![0, 1], vec![0, 2], vec![3, 5], vec![5, 4], vec![4, 3]];
    let source_2: i32 = 0;
    let destination_2: i32 = 5;
    let expected_2: bool = false;
    let output_2: bool =
        Solution::valid_path(n_2, edges_2, source_2, destination_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
