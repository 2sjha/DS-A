/*
https://leetcode.com/problems/smallest-string-starting-from-leaf

You are given the `root` of a binary tree where each node has a value in the range `[0, 25]` representing the letters
`'a'` to `'z'`.

Return *the **lexicographically smallest** string that starts at a leaf of this tree and ends at the root*.

As a reminder, any shorter prefix of a string is **lexicographically smaller**.

* For example, `"ab"` is lexicographically smaller than `"aba"`.

A leaf of a node is a node that has no children.


**Example 1:**

**Input:** root = [0,1,2,3,4,3,4]
**Output:** "dba"

**Example 2:**

**Input:** root = [25,1,3,1,3,0,2]
**Output:** "adz"

**Example 3:**

**Input:** root = [2,2,1,null,1,0,null,0]
**Output:** "abc"


**Constraints:**

* The number of nodes in the tree is in the range `[1, 8500]`.
* `0 <= Node.val <= 25`
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
    fn smallest_string_leaf(
        node: &Option<Rc<RefCell<TreeNode>>>,
        res: &mut String,
        sofar: &mut String,
    ) {
        if let Some(subtree_root) = node {
            let node = subtree_root.borrow();
            sofar.push((node.val as u8 + 'a' as u8) as char);

            if node.left.is_none() && node.right.is_none() {
                let tmp = sofar.clone();
                let tmp = tmp.chars().rev().collect::<String>();
                if res.len() == 0 || tmp < *res {
                    *res = tmp;
                }
            } else {
                Self::smallest_string_leaf(&node.left, res, sofar);
                Self::smallest_string_leaf(&node.right, res, sofar);
            }

            sofar.pop();
        }
    }

    pub fn smallest_from_leaf(root: Option<Rc<RefCell<TreeNode>>>) -> String {
        let mut res = String::new();
        let mut sofar = String::new();
        Self::smallest_string_leaf(&root, &mut res, &mut sofar);

        res
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
        0,
        new_node(1, new_node(3, None, None), new_node(4, None, None)),
        new_node(2, new_node(3, None, None), new_node(4, None, None)),
    );
    let expected_1: String = String::from("dba");
    let output_1: String = Solution::smallest_from_leaf(root_1);
    println!("{}", output_1);
    assert!(output_1 == expected_1);

    let root_2: Option<Rc<RefCell<TreeNode>>> = new_node(
        25,
        new_node(1, new_node(1, None, None), new_node(3, None, None)),
        new_node(3, new_node(0, None, None), new_node(2, None, None)),
    );
    let expected_2: String = String::from("adz");
    let output_2: String = Solution::smallest_from_leaf(root_2);
    println!("{}", output_2);
    assert!(output_2 == expected_2);

    let root_1: Option<Rc<RefCell<TreeNode>>> = new_node(
        2,
        new_node(2, None, new_node(1, new_node(0, None, None), None)),
        new_node(1, new_node(0, None, None), None),
    );
    let expected_1: String = String::from("abc");
    let output_1: String = Solution::smallest_from_leaf(root_1);
    println!("{}", output_1);
    assert!(output_1 == expected_1);
}
