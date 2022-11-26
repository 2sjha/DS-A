/*
https://leetcode.com/problems/diameter-of-binary-tree/

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

 

Example 1:

Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

Example 2:

Input: root = [1,2]
Output: 1

 

Constraints:

    The number of nodes in the tree is in the range [1, 104].
    -100 <= Node.val <= 100
*/

#include <algorithm>
#include <iostream>
#include <utility>
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
public:

    pair<int, int> heightNdiameter(TreeNode* root) {
        if(root == nullptr) {
            return {-1,-1};
        }
        pair<int, int> hnd_l = heightNdiameter(root->left);
        pair<int, int> hnd_r = heightNdiameter(root->right);

        pair<int, int> hnd_self;
        hnd_self.first = max(hnd_l.first, hnd_r.first) + 1;
        hnd_self.second = max(max(hnd_l.second, hnd_r.second), hnd_l.first + hnd_r.first + 2);
        return hnd_self;
    }
     
    int diameterOfBinaryTree(TreeNode* root) {
        pair<int, int> res = heightNdiameter(root);
        return res.second;
    }
};

