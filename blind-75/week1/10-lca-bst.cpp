/*
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree

Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in
the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two
nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to
be a descendant of itself).”

Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to
the LCA definition.

Example 3:
Input: root = [2,1], p = 2, q = 1
Output: 2

Constraints:
    The number of nodes in the tree is in the range [2, 105].
    -109 <= Node.val <= 109
    All Node.val are unique.
    p != q
    p and q will exist in the BST.
 */

#include <iostream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
  private:
    bool find_path(TreeNode* root, TreeNode* node, std::vector<TreeNode*>& path_node) {
        if (root == nullptr || node == nullptr) {
            return false;
        }
        bool found;
        if (root->val == node->val) {
            path_node.push_back(root);
            found = true;
        } else if (node->val > root->val) {
            found = find_path(root->right, node, path_node);
            if (found) {
                path_node.push_back(root);
            }
        } else {
            found = find_path(root->left, node, path_node);
            if (found) {
                path_node.push_back(root);
            }
        }
        return found;
    }

  public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* lca = nullptr;
        std::vector<TreeNode*> path_p, path_q;
        find_path(root, p, path_p);
        find_path(root, q, path_q);

        int i = path_p.size()-1, j = path_q.size()-1;
        while (i >= 0 && j >= 0) {
            if (path_p[i]->val != path_q[j]->val) {
                break;
            }
            i--;j--;
        }

        lca = path_p[i + 1];
        return lca;

    }
};