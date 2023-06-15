/*
https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so
on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.



Example 1:

Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Example 2:

Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2



Constraints:

    The number of nodes in the tree is in the range [1, 104].
    -105 <= Node.val <= 105


*/

#include "./../printutils.h"
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
    int maxLevelSum(TreeNode *root) {
        queue<pair<TreeNode *, int>> bfs_q;
        pair<TreeNode *, int> curr;
        int currSum = INT_MIN, maxSum = INT_MIN;
        TreeNode *currNode;
        int currLvl, prevLvl = 0, maxSumLvl = 0;

        bfs_q.push({root, 1});
        while (!bfs_q.empty()) {
            curr = bfs_q.front();
            bfs_q.pop();

            if (curr.first == nullptr) {
                continue;
            }

            currLvl = curr.second;
            currNode = curr.first;

            if (currLvl == prevLvl) {
                currSum += currNode->val;
            } else {
                if (maxSum < currSum) {
                    maxSum = currSum;
                    maxSumLvl = prevLvl;
                }
                prevLvl = currLvl;
                currSum = currNode->val;
            }

            if (currNode->left != nullptr) {
                bfs_q.push({currNode->left, currLvl + 1});
            }

            if (currNode->right != nullptr) {
                bfs_q.push({currNode->right, currLvl + 1});
            }
        }

        if (maxSum < currSum) {
            maxSum = currSum;
            maxSumLvl = prevLvl;
        }

        return maxSumLvl;
    }
};

int main() {
    Solution sol;
    int res;

    TreeNode *root1 = new TreeNode(1);
    root1->right = new TreeNode(0);
    root1->left = new TreeNode(7);
    root1->left->left = new TreeNode(7);
    root1->left->right = new TreeNode(-8);

    res = sol.maxLevelSum(root1);
    cout << res << endl;
    assert(res == 2);

    TreeNode *root2 = new TreeNode(989);
    root2->right = new TreeNode(10250);
    root2->right->left = new TreeNode(98693);
    root2->right->right = new TreeNode(-89388);
    root2->right->right->right = new TreeNode(-32127);
    res = sol.maxLevelSum(root2);
    cout << res << endl;
    assert(res == 2);

    return 0;
}