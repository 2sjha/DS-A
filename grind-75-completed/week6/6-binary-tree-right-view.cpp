/*
https://leetcode.com/problems/binary-tree-right-side-view/

Given the root of a binary tree, imagine yourself standing on the right side of it, return the
values of the nodes you can see ordered from top to bottom.


Example 1:

Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:

Input: root = [1,null,3]
Output: [1,3]

Example 3:

Input: root = []
Output: []


Constraints:

    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100
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
    vector<int> rightSideView(TreeNode *root) {
        vector<int> ans;
        map<int, int> r_map;
        queue<pair<TreeNode *, int>> bfs_q;
        bfs_q.push({root, 0});

        while (!bfs_q.empty()) {
            pair<TreeNode *, int> curr = bfs_q.front();
            bfs_q.pop();

            TreeNode *curr_node = curr.first;
            int lvl = curr.second;

            if (curr_node == nullptr) {
                continue;
            }

            if (r_map.find(lvl) == r_map.end()) {
                r_map[lvl] = curr_node->val;
            } else {
                r_map[lvl] = curr_node->val;
            }

            if (curr_node->left != nullptr) {
                bfs_q.push({curr_node->left, lvl + 1});
            }
            if (curr_node->right != nullptr) {
                bfs_q.push({curr_node->right, lvl + 1});
            }
        }

        for (auto entry : r_map) {
            ans.push_back(entry.second);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> res;

    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->right = new TreeNode(5);
    root1->right->right = new TreeNode(4);
    res = sol.rightSideView(root1);
    printArray(res);

    TreeNode *root2 = new TreeNode(1);
    root2->right = new TreeNode(3);
    res = sol.rightSideView(root2);
    printArray(res);

    TreeNode *root3 = nullptr;
    res = sol.rightSideView(root3);
    printArray(res);

    return 0;
}