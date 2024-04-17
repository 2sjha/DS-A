/*
https://leetcode.com/problems/sum-of-left-leaves

Given the `root` of a binary tree, return *the sum of all left leaves.*

A **leaf** is a node with no children. A **left leaf** is a leaf that is the left child of another node.


**Example 1:**

**Input:** root = [3,9,20,null,null,15,7]
**Output:** 24
**Explanation:** There are two left leaves in the binary tree, with values 9 and 15 respectively.

**Example 2:**

**Input:** root = [1]
**Output:** 0


**Constraints:**

* The number of nodes in the tree is in the range `[1, 1000]`.
* `-1000 <= Node.val <= 1000`
*/

use std::cell::RefCell;
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

struct Solution;
impl Solution {
    fn check_leaf(node: &Option<Rc<RefCell<TreeNode>>>) -> bool {
        if let Some(curr_node) = node {
            let curr_node = curr_node.borrow();

            return curr_node.left.is_none() && curr_node.right.is_none();
        } else {
            return false;
        }
    }

    fn sum_left_leaves(
        root: &Option<Rc<RefCell<TreeNode>>>,
        sum_so_far: &mut i32,
    ) -> i32 {
        if let Some(node) = root {
            let node = node.borrow();

            if node.left.is_some() && Self::check_leaf(&node.left) {
                *sum_so_far
                    + node.left.as_ref().unwrap().borrow().val
                    + Self::sum_left_leaves(&node.right, sum_so_far)
            } else {
                *sum_so_far
                    + Self::sum_left_leaves(&node.left, sum_so_far)
                    + Self::sum_left_leaves(&node.right, sum_so_far)
            }
        } else {
            *sum_so_far
        }
    }

    pub fn sum_of_left_leaves(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut sum_so_far: i32 = 0;
        Self::sum_left_leaves(&root, &mut sum_so_far)
    }
}

fn new_node(
    val: i32,
    left: Option<Rc<RefCell<TreeNode>>>,
    right: Option<Rc<RefCell<TreeNode>>>,
) -> Option<Rc<RefCell<TreeNode>>> {
    Some(Rc::new(RefCell::new(TreeNode {
        val: val,
        left: left,
        right: right,
    })))
}

fn main() {
    let root_1: Option<Rc<RefCell<TreeNode>>> = new_node(
        3,
        new_node(9, None, None),
        new_node(20, new_node(15, None, None), new_node(7, None, None)),
    );
    let expected_1: i32 = 24;
    let output_1: i32 = Solution::sum_of_left_leaves(root_1);
    println!("{}", output_1);
    assert!(output_1 == expected_1);

    let root_2: Option<Rc<RefCell<TreeNode>>> = new_node(1, None, None);
    let expected_2: i32 = 0;
    let output_2: i32 = Solution::sum_of_left_leaves(root_2);
    println!("{}", output_2);
    assert!(output_2 == expected_2);
}
