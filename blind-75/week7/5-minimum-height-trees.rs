/*
https://leetcode.com/problems/minimum-height-trees/

A tree is an undirected graph in which any two vertices are connected by exactly one path. In other
words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai,
bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can
choose any node of the tree as the root. When you select a node x as the root, the result tree has
height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called
minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and
a leaf.


Example 1:

Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is
the only MHT.

Example 2:

Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]


Constraints:

    1 <= n <= 2 * 104
    edges.length == n - 1
    0 <= ai, bi < n
    ai != bi
    All the pairs (ai, bi) are distinct.
    The given input is guaranteed to be a tree and there will be no repeated edges.
*/

struct Solution;
impl Solution {
    fn dfs_target(
        node: usize,
        target_node: usize,
        graph: &Vec<Vec<usize>>,
        visited: &mut Vec<bool>,
        path: &mut Vec<usize>,
    ) -> bool {
        if visited[node] {
            return false;
        }

        if node == target_node {
            path.push(node);
            return true;
        }

        visited[node] = true;
        let pushed_idx: usize = path.len();
        path.push(node);
        let mut found: bool = false;
        for adjacent_node in &graph[node] {
            if !visited[*adjacent_node] {
                found = found
                    || Self::dfs_target(
                        *adjacent_node,
                        target_node,
                        graph,
                        visited,
                        path,
                    );
            }
        }

        if !found {
            path.remove(pushed_idx);
        }

        found
    }

    fn dfs(
        node: usize,
        graph: &Vec<Vec<usize>>,
        visited: &mut Vec<bool>,
        dist: &mut Vec<usize>,
    ) {
        if visited[node] {
            return;
        }

        visited[node] = true;
        for adjacent_node in &graph[node] {
            dist[*adjacent_node] =
                std::cmp::min(dist[*adjacent_node], dist[node] + 1);
            if !visited[*adjacent_node] {
                Self::dfs(*adjacent_node, graph, visited, dist);
            }
        }
    }

    pub fn find_min_height_trees(n: i32, edges: Vec<Vec<i32>>) -> Vec<i32> {
        let mut graph: Vec<Vec<usize>> = vec![vec![]; n as usize];
        let mut res: Vec<i32> = vec![];

        for edge in edges {
            graph[edge[0] as usize].push(edge[1] as usize);
            graph[edge[1] as usize].push(edge[0] as usize);
        }

        // Find Leaf Node on the Diameter path using DFS
        // Start DFS from node 0.
        let mut visited: Vec<bool> = vec![false; n as usize];
        let mut dist: Vec<usize> = vec![usize::MAX; n as usize];
        dist[0] = 0;
        Self::dfs(0, &graph, &mut visited, &mut dist);

        let mut max_dist: usize = usize::MIN;
        let mut max_dist_leaf_node: usize = 0;
        for i in 0..(n as usize) {
            if dist[i] > max_dist {
                max_dist = dist[i];
                max_dist_leaf_node = i;
            }
        }

        // Do another DFS from the diameter node to find the length of the diameter path
        visited = vec![false; n as usize];
        dist = vec![usize::MAX; n as usize];
        dist[max_dist_leaf_node] = 0;
        Self::dfs(max_dist_leaf_node, &graph, &mut visited, &mut dist);

        // Find Length of the diameter path
        max_dist = usize::MIN;
        let mut diameter_node: usize = 0;
        for i in 0..(n as usize) {
            if dist[i] > max_dist {
                max_dist = dist[i];
                diameter_node = i;
            }
        }

        // Find midpoints and return MHT roots
        visited = vec![false; n as usize];
        let mut diameter_path: Vec<usize> = Vec::new();
        Self::dfs_target(
            max_dist_leaf_node,
            diameter_node,
            &graph,
            &mut visited,
            &mut diameter_path,
        );

        if diameter_path.len() % 2 == 0 {
            res.push(diameter_path[(diameter_path.len() / 2) - 1] as i32);
            res.push(diameter_path[diameter_path.len() / 2] as i32);
        } else {
            res.push(diameter_path[diameter_path.len() / 2] as i32);
        }

        res
    }
}

fn main() {
    let mut res: Vec<i32>;
    let mut n: i32;
    let mut edges: Vec<Vec<i32>>;

    n = 4;
    edges = vec![vec![1, 0], vec![1, 2], vec![1, 3]];
    res = Solution::find_min_height_trees(n, edges);
    println!("{:?}", res);
    // assert!(res == vec![1]);

    n = 6;
    edges = vec![vec![3, 0], vec![3, 1], vec![3, 2], vec![3, 4], vec![5, 4]];
    res = Solution::find_min_height_trees(n, edges);
    println!("{:?}", res);
    // assert!(res == vec![3, 4]);

    n = 10;
    edges = vec![
        vec![0, 3],
        vec![1, 3],
        vec![2, 3],
        vec![4, 3],
        vec![5, 3],
        vec![4, 6],
        vec![4, 7],
        vec![5, 8],
        vec![5, 9],
    ];
    res = Solution::find_min_height_trees(n, edges);
    println!("{:?}", res);
    // assert!(res == vec![3]);
}
