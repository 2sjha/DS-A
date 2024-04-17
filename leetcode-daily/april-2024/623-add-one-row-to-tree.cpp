/*
https://leetcode.com/problems/add-one-row-to-tree

Given the `root` of a binary tree and two integers `val` and `depth`, add a row of nodes with value
`val` at the given depth `depth`.

Note that the `root` node is at depth `1`.

The adding rule is:

* Given the integer `depth`, for each not null tree node `cur` at the depth `depth - 1`, create two
tree nodes with value `val` as `cur`'s left subtree root and right subtree root.
* `cur`'s original left subtree should be the left subtree of the new left subtree root.
* `cur`'s original right subtree should be the right subtree of the new right subtree root.
* If `depth == 1` that means there is no depth `depth - 1` at all, then create a tree node with
value `val` as the new root of the whole original tree, and the original tree is the new root's left
subtree.


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

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    TreeNode *addOneRow(TreeNode *root, int val, int depth) {
        if (depth == 1) {
            TreeNode *new_root = new TreeNode(val);
            new_root->left = root;
            return new_root;
        }

        pair<TreeNode *, int> curr;
        queue<pair<TreeNode *, int>> bfs_q;
        bfs_q.push({root, 1});
        while (!bfs_q.empty()) {
            curr = bfs_q.front();
            bfs_q.pop();

            if (curr.second == depth - 1) {
                TreeNode *new_left_node = new TreeNode(val);
                new_left_node->left = curr.first->left;
                TreeNode *new_right_node = new TreeNode(val);
                new_right_node->right = curr.first->right;

                curr.first->left = new_left_node;
                curr.first->right = new_right_node;
            } else {
                if (curr.first->left != nullptr) {
                    bfs_q.push({curr.first->left, curr.second + 1});
                }
                if (curr.first->right != nullptr) {
                    bfs_q.push({curr.first->right, curr.second + 1});
                }
            }
        }

        return root;
    }
};

int main() {
    Solution sol;

    TreeNode *root_1 = new TreeNode(4);
    root_1->left = new TreeNode(2);
    root_1->right = new TreeNode(6);
    root_1->right->left = new TreeNode(5);
    root_1->left->left = new TreeNode(3);
    root_1->left->left = new TreeNode(1);
    int val_1 = 1;
    int depth_1 = 2;
    TreeNode *output_1 = sol.addOneRow(root_1, val_1, depth_1);
    printBinaryTree(output_1);

    TreeNode *root_2 = new TreeNode(4);
    root_2->left = new TreeNode(2);
    root_2->left->left = new TreeNode(3);
    root_2->left->right = new TreeNode(1);
    int val_2 = 1;
    int depth_2 = 3;
    TreeNode *output_2 = sol.addOneRow(root_2, val_2, depth_2);
    printBinaryTree(output_2);

    return 0;
}