/*
https://leetcode.com/problems/all-possible-full-binary-trees/

Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each
tree in the answer must have Node.val == 0.

Each element of the answer is the root node of one possible tree. You may return the final list of
trees in any order.

A full binary tree is a binary tree where each node has exactly 0 or 2 children.


Example 1:

Input: n = 7
Output:
[[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]

Example 2:

Input: n = 3
Output: [[0,0,0]]


Constraints:

    1 <= n <= 20
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    unordered_map<int, vector<TreeNode *>> mp;

  public:
    vector<TreeNode *> allPossibleFBT(int n) {
        if (n % 2 == 0) {
            mp[n] = vector<TreeNode *>();
            return mp[n];
        }

        if (mp.count(n)) {
            return mp[n];
        }

        if (n == 1) {
            mp[1] = {new TreeNode(0)};
            return mp[1];
        } else if (n == 3) {
            TreeNode *r = new TreeNode(0);
            r->left = new TreeNode(0);
            r->right = new TreeNode(0);

            mp[3] = {r};
            return mp[3];
        }

        int left = 1;
        int right;
        vector<TreeNode *> res;
        vector<TreeNode *> left_trees;
        vector<TreeNode *> right_trees;
        while (left < n) {
            right = n - 1 - left;
            left_trees = allPossibleFBT(left);
            right_trees = allPossibleFBT(right);

            for (TreeNode *left_tree : left_trees) {
                for (TreeNode *right_tree : right_trees) {
                    TreeNode *r = new TreeNode(0);
                    r->left = left_tree;
                    r->right = right_tree;
                    res.push_back(r);
                }
            }
            left += 2;
        }

        mp[n] = res;
        return mp[n];
    }
};

int main() {
    Solution sol;
    vector<TreeNode *> res;
    int n;

    n = 7;
    res = sol.allPossibleFBT(n);

    n = 3;
    sol.allPossibleFBT(n);

    return 0;
}