/*
https://leetcode.com/problems/sum-of-left-leaves

Given the `root` of a binary tree, return *the sum of all left leaves.*

A **leaf** is a node with no children. A **left leaf** is a leaf that is the left child of another
node.


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

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int sumLeftLeaves(TreeNode *root, int sumSofar) {
        if (root == nullptr)
            return sumSofar;

        if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
            return sumSofar + root->left->val + sumLeftLeaves(root->right, sumSofar);
        } else {
            return sumSofar + sumLeftLeaves(root->left, sumSofar) +
                   sumLeftLeaves(root->right, sumSofar);
        }
    }

  public:
    int sumOfLeftLeaves(TreeNode *root) { return sumLeftLeaves(root, 0); }
};

int main() {
    Solution sol;

    TreeNode *root_1 = new TreeNode(3);
    root_1->left = new TreeNode(9);
    root_1->right = new TreeNode(20);
    root_1->right->left = new TreeNode(15);
    root_1->right->right = new TreeNode(7);
    int expected_1 = 24;
    int output_1 = sol.sumOfLeftLeaves(root_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    TreeNode *root_2 = new TreeNode(1);
    int expected_2 = 0;
    int output_2 = sol.sumOfLeftLeaves(root_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}