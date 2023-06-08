/*
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary
tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.


Example 1:

Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]


Constraints:

    1 <= preorder.length <= 3000
    inorder.length == preorder.length
    -3000 <= preorder[i], inorder[i] <= 3000
    preorder and inorder consist of unique values.
    Each value of inorder also appears in preorder.
    preorder is guaranteed to be the preorder traversal of the tree.
    inorder is guaranteed to be the inorder traversal of the tree.
*/

#include "./../../printutils.h"
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
  private:
    int get_idx(vector<int> &traversal, int start, int end, int val) {
        for (int i = start; i <= end; ++i) {
            if (traversal[i] == val) {
                return i;
            }
        }

        return -1;
    }

  public:
    TreeNode *buildTree(vector<int> &preorder, int pre_start, int pre_end, vector<int> &inorder,
                        int in_start, int in_end) {
        if (pre_start < 0 || in_start < 0 || pre_end >= preorder.size() ||
            in_end >= inorder.size() || pre_start > pre_end || in_start > in_end) {
            return nullptr;
        }

        int root_val = preorder[pre_start];
        int root_in_idx = get_idx(inorder, in_start, in_end, root_val);
        int left_subtree_node_count = root_in_idx - in_start;
        int right_subtree_node_count = in_end - root_in_idx;

        TreeNode *root = new TreeNode(root_val);
        root->left = buildTree(preorder, pre_start + 1, pre_start + left_subtree_node_count,
                               inorder, in_start, root_in_idx - 1);
        root->right = buildTree(preorder, pre_start + 1 + left_subtree_node_count, pre_end, inorder,
                                root_in_idx + 1, in_end);
        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    void inorder(TreeNode *root, vector<int> &check_inorder) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, check_inorder);
        check_inorder.push_back(root->val);
        inorder(root->right, check_inorder);
    }
};

int main() {
    Solution sol;
    TreeNode *root;

    vector<int> preorder1 = {2};
    vector<int> inorder1 = {2};
    root = sol.buildTree(preorder1, inorder1);
    vector<int> check_inorder;
    sol.inorder(root, check_inorder);
    printArray(inorder1);
    printArray(check_inorder);

    vector<int> preorder2 = {3, 9, 20, 15, 7};
    vector<int> inorder2 = {9, 3, 15, 20, 7};
    root = sol.buildTree(preorder2, inorder2);
    check_inorder.clear();
    sol.inorder(root, check_inorder);
    printArray(inorder2);
    printArray(check_inorder);

    vector<int> preorder3 = {3, 9, 18, 10, 6, 20, 15, 7, 8};
    vector<int> inorder3 = {18, 9, 10, 6, 3, 15, 20, 8, 7};
    root = sol.buildTree(preorder3, inorder3);
    check_inorder.clear();
    sol.inorder(root, check_inorder);
    printArray(inorder3);
    printArray(check_inorder);

    return 0;
}