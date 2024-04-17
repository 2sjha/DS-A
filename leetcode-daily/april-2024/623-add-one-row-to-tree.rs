/*
https://leetcode.com/problems/add-one-row-to-tree

Given the `root` of a binary tree and two integers `val` and `depth`, add a row of nodes with value `val` at the given
depth `depth`.

Note that the `root` node is at depth `1`.

The adding rule is:

* Given the integer `depth`, for each not null tree node `cur` at the depth `depth - 1`, create two tree nodes with
  value `val` as `cur`'s left subtree root and right subtree root.
* `cur`'s original left subtree should be the left subtree of the new left subtree root.
* `cur`'s original right subtree should be the right subtree of the new right subtree root.
* If `depth == 1` that means there is no depth `depth - 1` at all, then create a tree node with value `val` as the new
  root of the whole original tree, and the original tree is the new root's left subtree.


**Example 1:**

**Input:** root = [4,2,6,3,1,5], val = 1, depth = 2
**Output:** [4,1,1,2,null,null,6,3,1,5]

**Example 2:**

**Input:** root = [4,2,null,3,1], val = 1, depth = 3
**Output:** [4,2,null,1,1,3,null,null,1]


**Constraints:**

* The number of nodes in the tree is in the range `[1, 10⁴]`.
* The depth of the tree is in the range `[1, 10⁴]`.
* `-100 <= Node.val <= 100`
* `-10⁵ <= val <= 10⁵`
* `1 <= depth <= the depth of tree + 1`
*/

use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

type Node = Option<Rc<RefCell<TreeNode>>>;
struct Solution;
impl Solution {
    pub fn add_one_row(
        root: Option<Rc<RefCell<TreeNode>>>,
        val: i32,
        depth: i32,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        if depth == 1 {
            let mut new_root = TreeNode::new(val);
            new_root.left = root;
            return Some(Rc::new(RefCell::new(new_root)));
        }

        let old_root = Rc::clone(root.as_ref().unwrap());
        let mut bfs_q: VecDeque<(Node, usize)> = VecDeque::new();
        bfs_q.push_back((root, 1));

        while bfs_q.len() != 0 {
            let curr = bfs_q.pop_front().unwrap();

            if curr.1 == depth as usize - 1 {
                if let Some(node) = curr.0 {
                    let mut node = node.borrow_mut();
                    let left = &node.left;
                    let right = &node.right;

                    let mut node_1 = TreeNode::new(val);
                    let mut node_2 = TreeNode::new(val);
                    node_1.left = left.clone();
                    node_2.right = right.clone();

                    node.left = Some(Rc::new(RefCell::new(node_1)));
                    node.right = Some(Rc::new(RefCell::new(node_2)));
                }
            } else {
                if let Some(node) = curr.0 {
                    let node = node.borrow();
                    if node.left.is_some() {
                        let left = &node.left;
                        bfs_q.push_back((left.clone(), curr.1 + 1));
                    }

                    if node.right.is_some() {
                        let right = &node.right;
                        bfs_q.push_back((right.clone(), curr.1 + 1));
                    }
                }
            }
        }

        Some(old_root)
    }
}

fn new_node(val: i32, left: Node, right: Node) -> Node {
    Some(Rc::new(RefCell::new(TreeNode {
        val: val,
        left: left,
        right: right,
    })))
}

fn main() {
    let root_1: Node = new_node(
        4,
        new_node(2, new_node(3, None, None), new_node(1, None, None)),
        new_node(6, new_node(5, None, None), None),
    );
    let val_1: i32 = 1;
    let depth_1: i32 = 2;
    let output_1: Node = Solution::add_one_row(root_1, val_1, depth_1);
    println!("{:?}\n", output_1);

    let root_2: Node = new_node(
        4,
        new_node(2, new_node(3, None, None), new_node(1, None, None)),
        None,
    );
    let val_2: i32 = 1;
    let depth_2: i32 = 3;
    let output_2: Node = Solution::add_one_row(root_2, val_2, depth_2);
    println!("{:?}\n", output_2);
}
