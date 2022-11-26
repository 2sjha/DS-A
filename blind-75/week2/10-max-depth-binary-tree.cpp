/*
https://leetcode.com/problems/maximum-depth-of-binary-tree/


Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down
to the farthest leaf node.


Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:

Input: root = [1,null,2]
Output: 2


Constraints:

    The number of nodes in the tree is in the range [0, 104].
    -100 <= Node.val <= 100
*/
#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
  private:
    int recur(TreeNode* root, int curr_depth) {
        if (root == nullptr) {
            return curr_depth;
        }

        return max(recur(root->left, curr_depth + 1), recur(root->right, curr_depth + 1));
    }

  public:
    int maxDepth(TreeNode* root) { return recur(root, 0); }
};