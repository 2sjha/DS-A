/*
https://leetcode.com/problems/minimum-depth-of-binary-tree/

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the
nearest leaf node.

Note: A leaf is a node with no children.


Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 2

Example 2:

Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5


Constraints:

    The number of nodes in the tree is in the range [0, 105].
    -1000 <= Node.val <= 1000
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  public:
    int minDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        int left = minDepth(root->left);
        int right = minDepth(root->right);

        if (left != 0 && right != 0) {
            return 1 + min(left, right);
        } else if (right == 0) {
            return 1 + left;
        } else {
            return 1 + right;
        }
    }
};

int main() {
    Solution sol;
    int res;

    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    res = sol.minDepth(root1);
    cout << res << endl;
    assert(res == 2);

    TreeNode *root2 = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->right->right = new TreeNode(4);
    root2->right->right->right = new TreeNode(5);
    root2->right->right->right->right = new TreeNode(6);
    res = sol.minDepth(root2);
    cout << res << endl;
    assert(res == 5);

    return 0;
}