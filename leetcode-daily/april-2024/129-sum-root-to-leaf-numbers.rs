/*
https://leetcode.com/problems/sum-root-to-leaf-numbers

You are given the `root` of a binary tree containing digits from `0` to `9` only.

Each root-to-leaf path in the tree represents a number.

* For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.

Return *the total sum of all root-to-leaf numbers*. Test cases are generated so that the answer will fit in a **32-bit**
integer.

A **leaf** node is a node with no children.


**Example 1:**

**Input:** root = [1,2,3]
**Output:** 25
**Explanation:**
The root-to-leaf path `1->2` represents the number `12`.
The root-to-leaf path `1->3` represents the number `13`.
Therefore, sum = 12 + 13 = `25`.

**Example 2:**

**Input:** root = [4,9,0,5,1]
**Output:** 1026
**Explanation:**
The root-to-leaf path `4->9->5` represents the number 495.
The root-to-leaf path `4->9->1` represents the number 491.
The root-to-leaf path `4->0` represents the number 40.
Therefore, sum = 495 + 491 + 40 = `1026`.


**Constraints:**

* The number of nodes in the tree is in the range `[1, 1000]`.
* `0 <= Node.val <= 9`
* The depth of the tree will not exceed `10`.
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
    fn vec_to_i32(digits: &Vec<i32>) -> i32 {
        let mut num: i32 = 0;
        for d in digits {
            num = num * 10 + d;
        }
        num
    }

    fn dfs(
        root: &Option<Rc<RefCell<TreeNode>>>,
        digits: &mut Vec<i32>,
        sum: &mut i32,
    ) {
        if let Some(node) = root {
            let node = node.borrow();

            digits.push(node.val);
            if node.left.is_none() && node.right.is_none() {
                *sum += Self::vec_to_i32(digits);
            } else {
                Self::dfs(&node.left, digits, sum);
                Self::dfs(&node.right, digits, sum);
            }

            digits.pop();
        }
    }

    pub fn sum_numbers(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut sum: i32 = 0;
        let mut digits: Vec<i32> = Vec::new();
        Self::dfs(&root, &mut digits, &mut sum);

        sum
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
    let root_1: Option<Rc<RefCell<TreeNode>>> =
        new_node(1, new_node(2, None, None), new_node(3, None, None));
    let expected_1: i32 = 25;
    let output_1: i32 = Solution::sum_numbers(root_1);
    println!("{}", output_1);
    assert!(output_1 == expected_1);

    let root_2 = new_node(
        4,
        new_node(9, new_node(5, None, None), new_node(1, None, None)),
        new_node(0, None, None),
    );
    let expected_2: i32 = 1026;
    let output_2: i32 = Solution::sum_numbers(root_2);
    println!("{}", output_2);
    assert!(output_2 == expected_2);
}
