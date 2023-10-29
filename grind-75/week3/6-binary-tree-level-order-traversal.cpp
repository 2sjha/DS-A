/*
https://leetcode.com/problems/binary-tree-level-order-traversal

Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from
left to right, level by level).


Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:

Input: root = [1]
Output: [[1]]

Example 3:

Input: root = []
Output: []


Constraints:

    The number of nodes in the tree is in the range [0, 2000].
    -1000 <= Node.val <= 1000
*/

#include <bits/stdc++.h>
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
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        queue<pair<TreeNode *, int>> bfs_q;
        bfs_q.push({root, 1});

        while (!bfs_q.empty()) {
            pair<TreeNode *, int> front = bfs_q.front();
            bfs_q.pop();

            TreeNode *curr_node = front.first;
            int curr_level = front.second;

            if (curr_node == nullptr) {
                continue;
            }

            while (res.size() < curr_level) {
                vector<int> empty;
                res.push_back(empty);
            }

            res[curr_level - 1].push_back(curr_node->val);

            if (curr_node->left != nullptr) {
                bfs_q.push({curr_node->left, curr_level + 1});
            }

            if (curr_node->right != nullptr) {
                bfs_q.push({curr_node->right, curr_level + 1});
            }
        }

        return res;
    }
};

int main() {
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(6);

    Solution sol;
    vector<vector<int>> res = sol.levelOrder(root);
    for (auto r : res) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}