/*
https://leetcode.com/problems/binary-tree-maximum-path-sum/

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has
an edge connecting them. A node can only appear in the sequence at most once. Note that the path
does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path.


Example 1:

Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

Example 2:

Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.


Constraints:

    The number of nodes in the tree is in the range [1, 3 * 104].
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
private:
    int maxInVec(vector<int> v, int start, int end) {
        int maxi = INT_MIN;
        for(int i = start; i <= end; ++i) {
            maxi = max(maxi, v[i]);
        }
        return maxi;
    }

    vector<int> maxPathSumUtil(TreeNode* root) {
        if(root == NULL) {
            return {-1001, -1001, -1001, -1001, -1001, -1001};
        }

        vector<int> res = {-1001, -1001, root->val, -1001, -1001, root->val};    
        vector<int> left = maxPathSumUtil(root->left);
        res[0] = maxInVec(left, 0, 5);
        res[1] = maxInVec(left, 1, 3) + root->val;

        vector<int> right = maxPathSumUtil(root->right);
        res[4] = maxInVec(right, 0, 5);
        res[3] = maxInVec(right, 1, 3) + root->val;

        res[5] = maxInVec(left, 1, 3) + root->val + maxInVec(right, 1, 3);

        return res;
    }

public:
    int maxPathSum(TreeNode* root) {
        return maxInVec(maxPathSumUtil(root), 0, 5);
    }
};

int main() {
    Solution sol;
    int res;

    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    res = sol.maxPathSum(root1);
    cout << res << endl;
    assert(res == 6);

    TreeNode* root2 = new TreeNode(-10);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(20);
    root2->right->left = new TreeNode(15);
    root2->right->right = new TreeNode(7);
    res = sol.maxPathSum(root2);
    cout << res << endl;
    assert(res == 42);

    TreeNode* root3 = new TreeNode(-3);
    res = sol.maxPathSum(root3);
    cout << res << endl;
    assert(res == -3);

    TreeNode* root4 = new TreeNode(2);
    root4->left = new TreeNode(-1);
    res = sol.maxPathSum(root4);
    cout << res << endl;
    assert(res == 2);

    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(-2);
    root5->right = new TreeNode(3);
    res = sol.maxPathSum(root5);
    cout << res << endl;
    assert(res == 4);

    TreeNode* root6 = new TreeNode(1);
    root6->left = new TreeNode(-2);
    root6->right = new TreeNode(-3);
    root6->right->left = new TreeNode(-2);
    root6->left->left = new TreeNode(1);
    root6->left->right = new TreeNode(3);
    root6->left->left->left = new TreeNode(-1);
    res = sol.maxPathSum(root6);
    cout << res << endl;
    assert(res == 3);

    TreeNode* root7 = new TreeNode(5);
    root7->left = new TreeNode(4);
    root7->right = new TreeNode(8);
    root7->right->left = new TreeNode(13);
    root7->right->right = new TreeNode(4);
    root7->right->right->right = new TreeNode(1);
    root7->left->left = new TreeNode(11);
    root7->left->left->left = new TreeNode(7);
    root7->left->left->right = new TreeNode(2);
    res = sol.maxPathSum(root7);
    cout << res << endl;
    assert(res == 48);

    return 0;
}