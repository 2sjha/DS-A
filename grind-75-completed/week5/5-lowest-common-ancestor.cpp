/*
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two
nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to
be a descendant of itself).”


Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to
the LCA definition.

Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1


Constraints:

    The number of nodes in the tree is in the range [2, 105].
    -109 <= Node.val <= 109
    All Node.val are unique.
    p != q
    p and q will exist in the tree.
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  private:
    bool getPath(vector<TreeNode *> &path, TreeNode *root, TreeNode *node) {
        if (root == nullptr) {
            return false;
        }

        if (root->val == node->val) {
            path.push_back(node);
            return true;
        }

        bool found_l = getPath(path, root->left, node);
        bool found_r = getPath(path, root->right, node);
        if (found_l || found_r) {
            path.push_back(root);
        }
        return found_l || found_r;
    }

  public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        vector<TreeNode *> path_p = vector<TreeNode *>();
        getPath(path_p, root, p);
        reverse(path_p.begin(), path_p.end());
        vector<TreeNode *> path_q = vector<TreeNode *>();
        getPath(path_q, root, q);
        reverse(path_q.begin(), path_q.end());

        int len_p = path_p.size();
        int len_q = path_q.size();

        int i = 0;
        for (; i < min(len_p, len_q); ++i) {
            if (path_p[i]->val != path_q[i]->val) {
                return path_p[i - 1];
            }
        }

        if (len_p < len_q) {
            return path_p[i - 1];
        } else {
            return path_q[i - 1];
        }
    }
};

int main() {
    Solution sol;

    // [3,5,1,6,2,0,8,null,null,7,4]
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    root->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    TreeNode *res = sol.lowestCommonAncestor(root, new TreeNode(5), new TreeNode(1));
    cout << res->val << endl;

    res = sol.lowestCommonAncestor(root, new TreeNode(5), new TreeNode(4));
    cout << res->val << endl;

    TreeNode *root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    res = sol.lowestCommonAncestor(root2, new TreeNode(1), new TreeNode(2));
    cout << res->val << endl;

    return 0;
}
