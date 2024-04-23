/*
https://leetcode.com/problems/minimum-height-trees

A tree is an undirected graph in which any two vertices are connected by *exactly* one path. In other words, any
connected graph without simple cycles is a tree.

Given a tree of `n` nodes labelled from `0` to `n - 1`, and an array of `n - 1` `edges` where `edges[i] = [ai, bi]`
indicates that there is an undirected edge between the two nodes `ai` and `bi` in the tree, you can choose any node of
the tree as the root. When you select a node `x` as the root, the result tree has height `h`. Among all possible rooted
trees, those with minimum height (i.e. `min(h)`) are called **minimum height trees** (MHTs).

Return *a list of all **MHTs'** root labels*. You can return the answer in **any order**.

The **height** of a rooted tree is the number of edges on the longest downward path between the root and a leaf.


**Example 1:**

**Input:** n = 4, edges = [[1,0],[1,2],[1,3]]
**Output:** [1]
**Explanation:** As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.

**Example 2:**

**Input:** n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
**Output:** [3,4]


**Constraints:**

* `1 <= n <= 2 * 10⁴`
* `edges.length == n - 1`
* `0 <= ai, bi < n`
* `ai != bi`
* All the pairs `(ai, bi)` are distinct.
* The given input is **guaranteed** to be a tree and there will be **no repeated** edges.
*/

struct Solution;
impl Solution {
    fn find_farthest_leaf(g: &Vec<Vec<usize>>, leaf_1: usize) -> (usize, u16) {
        let n: usize = g.len();
        let mut st: Vec<(usize, u16)> = vec![(leaf_1, 0)];
        let mut visited: Vec<bool> = vec![false; n];
        let mut max_dist: u16 = u16::MIN;
        let mut farthest_leaf: usize = leaf_1;

        while st.len() != 0 {
            let curr: (usize, u16) = st.pop().unwrap();
            if visited[curr.0] {
                continue;
            }

            visited[curr.0] = true;
            if g[curr.0].len() == 1 {
                if curr.1 > max_dist {
                    max_dist = curr.1;
                    farthest_leaf = curr.0;
                }
            }

            for v in &g[curr.0] {
                if !visited[*v] {
                    st.push((*v, curr.1 + 1));
                }
            }
        }

        (farthest_leaf, max_dist)
    }

    fn find(
        g: &Vec<Vec<usize>>,
        node: usize,
        target: usize,
        dist_so_far: u16,
        visited: &mut Vec<bool>,
        path: &mut Vec<(usize, u16)>,
    ) -> bool {
        if node == target {
            path.push((node, dist_so_far));
            visited[node] = true;
            true
        } else {
            visited[node] = true;
            let mut found: bool = false;
            for v in &g[node] {
                if !visited[*v] {
                    found |= Self::find(
                        g,
                        *v,
                        target,
                        dist_so_far + 1,
                        visited,
                        path,
                    );
                    if found {
                        path.push((node, dist_so_far));
                        break;
                    }
                }
            }

            found
        }
    }

    fn get_path(
        g: &Vec<Vec<usize>>,
        source: usize,
        target: usize,
    ) -> Vec<(usize, u16)> {
        let mut path: Vec<(usize, u16)> = Vec::new();
        let mut visited: Vec<bool> = vec![false; g.len()];
        Self::find(g, source, target, 0, &mut visited, &mut path);
        path.reverse();
        path
    }

    pub fn find_min_height_trees(n: i32, edges: Vec<Vec<i32>>) -> Vec<i32> {
        if n == 1 {
            return vec![0];
        }

        let n: usize = n as usize;
        let mut g: Vec<Vec<usize>> = vec![vec![]; n];
        for edge in &edges {
            let u: usize = edge[0] as usize;
            let v: usize = edge[1] as usize;
            g[u].push(v);
            g[v].push(u);
        }

        let (leaf_2, _max_dist) = Self::find_farthest_leaf(&g, 0);
        let (leaf_3, max_dist) = Self::find_farthest_leaf(&g, leaf_2);
        let path: Vec<(usize, u16)> = Self::get_path(&g, leaf_2, leaf_3);
        let mut res: Vec<i32> = Vec::new();
        let mut min_height: u16 = u16::MAX;
        for (_node, dist) in &path {
            min_height = std::cmp::min(
                min_height,
                std::cmp::max(*dist, max_dist - *dist),
            );
        }

        for (node, dist) in &path {
            if std::cmp::max(*dist, max_dist - *dist) == min_height {
                res.push(*node as i32);
            }
        }

        res
    }
}

fn main() {
    let n_1: i32 = 4;
    let edges_1: Vec<Vec<i32>> = vec![vec![1, 0], vec![1, 2], vec![1, 3]];
    let mut expected_1: Vec<i32> = vec![1];
    let mut output_1: Vec<i32> = Solution::find_min_height_trees(n_1, edges_1);
    println!("{:?}", output_1);
    output_1.sort();
    expected_1.sort();
    assert!(output_1 == expected_1);

    let n_2: i32 = 6;
    let edges_2: Vec<Vec<i32>> =
        vec![vec![3, 0], vec![3, 1], vec![3, 2], vec![3, 4], vec![5, 4]];
    let mut expected_2: Vec<i32> = vec![3, 4];
    let mut output_2: Vec<i32> = Solution::find_min_height_trees(n_2, edges_2);
    println!("{:?}", output_2);
    output_2.sort();
    expected_2.sort();
    assert!(output_2 == expected_2);

    let n_3: i32 = 7;
    let edges_3: Vec<Vec<i32>> = vec![
        vec![0, 1],
        vec![1, 2],
        vec![1, 3],
        vec![2, 4],
        vec![3, 5],
        vec![4, 6],
    ];
    let mut expected_3: Vec<i32> = vec![2, 1];
    let mut output_3: Vec<i32> = Solution::find_min_height_trees(n_3, edges_3);
    println!("{:?}", output_3);
    output_3.sort();
    expected_3.sort();
    assert!(output_3 == expected_3);
}
