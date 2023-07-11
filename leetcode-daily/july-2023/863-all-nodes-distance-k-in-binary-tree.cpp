/*
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

Given the root of a binary tree, the value of a target node target, and an integer k, return an
array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.


Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4,
and 1.

Example 2:

Input: root = [1], target = 1, k = 3
Output: []


Constraints:

    The number of nodes in the tree is in the range [1, 500].
    0 <= Node.val <= 500
    All the values Node.val are unique.
    target is the value of one of the nodes in the tree.
    0 <= k <= 1000
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  private:
    void distanceKDownFromTarget(TreeNode *target, int k, set<int> &res) {
        if (target == nullptr)
            return;

        if (k == 0) {
            res.insert(target->val);
            return;
        }

        stack<pair<TreeNode *, int>> dfs_st;
        pair<TreeNode *, int> curr;
        dfs_st.push({target, 0});
        while (!dfs_st.empty()) {
            curr = dfs_st.top();
            dfs_st.pop();

            if (curr.first == nullptr) {
                continue;
            }

            if (curr.second == k) {
                res.insert(curr.first->val);
            }

            if (curr.second < k && curr.first->left) {
                dfs_st.push({curr.first->left, curr.second + 1});
            }
            if (curr.second < k && curr.first->right) {
                dfs_st.push({curr.first->right, curr.second + 1});
            }
        }
    }

    pair<int, bool> distanceKUpFromTarget(TreeNode *root, TreeNode *target, int k, set<int> &res) {
        if (root == nullptr) {
            return {10000, false};
        }
        if (root->val == target->val) {
            return {0, true};
        }

        pair<int, bool> left = distanceKUpFromTarget(root->left, target, k, res);
        pair<int, bool> right = distanceKUpFromTarget(root->right, target, k, res);

        if (!left.second && !right.second) {
            return {10000, false};
        } else if (left.second) {
            if (left.first == k - 1) {
                res.insert(root->val);
                return {k, true};
            } else if (left.first < k - 1) {
                distanceKDownFromTarget(root->right, k - (left.first + 2), res);
            }
            return {left.first + 1, true};
        } else {
            if (right.first == k - 1) {
                res.insert(root->val);
                return {k, true};
            } else if (right.first < k - 1) {
                distanceKDownFromTarget(root->left, k - (right.first + 2), res);
            }
            return {right.first + 1, true};
        }
    }

  public:
    vector<int> distanceK(TreeNode *root, TreeNode *target, int k) {
        set<int> res;
        // distance k nodes down the tree
        distanceKDownFromTarget(target, k, res);

        // distance k nodes up the tree
        distanceKUpFromTarget(root, target, k, res);

        vector<int> res_vec;
        for (int i : res) {
            res_vec.push_back(i);
        }

        return res_vec;
    }
};

int main() {
    Solution sol;
    vector<int> res;
    int k;

    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(5);
    root1->right = new TreeNode(1);
    root1->right->left = new TreeNode(0);
    root1->right->right = new TreeNode(8);
    root1->left->left = new TreeNode(6);
    root1->left->right = new TreeNode(2);
    root1->left->right->left = new TreeNode(7);
    root1->left->right->right = new TreeNode(4);
    res = sol.distanceK(root1, root1->left, 2);
    printArray(res);

    TreeNode *root2 = new TreeNode(1);
    res = sol.distanceK(root2, root2, 3);
    printArray(res);

    TreeNode *root3 = new TreeNode(0);
    root3->right = new TreeNode(1);
    root3->right->left = new TreeNode(2);
    root3->right->right = new TreeNode(5);
    root3->right->left->right = new TreeNode(3);
    root3->right->left->right->right = new TreeNode(4);
    res = sol.distanceK(root3, root3->right->left, 2);
    printArray(res);

    return 0;
}