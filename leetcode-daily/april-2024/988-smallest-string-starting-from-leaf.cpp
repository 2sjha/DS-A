/*
https://leetcode.com/problems/smallest-string-starting-from-leaf

You are given the `root` of a binary tree where each node has a value in the range `[0, 25]`
representing the letters
`'a'` to `'z'`.

Return *the **lexicographically smallest** string that starts at a leaf of this tree and ends at the
root*.

As a reminder, any shorter prefix of a string is **lexicographically smaller**.

* For example, `"ab"` is lexicographically smaller than `"aba"`.

A leaf of a node is a node that has no children.


**Example 1:**

**Input:** root = [0,1,2,3,4,3,4]
**Output:** "dba"

**Example 2:**

**Input:** root = [25,1,3,1,3,0,2]
**Output:** "adz"

**Example 3:**

**Input:** root = [2,2,1,null,1,0,null,0]
**Output:** "abc"


**Constraints:**

* The number of nodes in the tree is in the range `[1, 8500]`.
* `0 <= Node.val <= 25`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void dfs(TreeNode *root, string &res, string &sofar) {
        if (root == nullptr)
            return;

        sofar.push_back(root->val + 'a');
        if (root->left == nullptr && root->right == nullptr) {
            reverse(sofar.begin(), sofar.end());
            if (res == "" || sofar < res) {
                res = sofar;
            }
            reverse(sofar.begin(), sofar.end());
        } else {
            dfs(root->left, res, sofar);
            dfs(root->right, res, sofar);
        }
        sofar.pop_back();
    }

  public:
    string smallestFromLeaf(TreeNode *root) {
        string res = "";
        string sofar = "";
        dfs(root, res, sofar);
        return res;
    }
};

int main() {
    Solution sol;

    TreeNode *root_1 = new TreeNode(0);
    root_1->left = new TreeNode(1);
    root_1->right = new TreeNode(2);
    root_1->left->left = new TreeNode(3);
    root_1->left->right = new TreeNode(4);
    root_1->right->left = new TreeNode(3);
    root_1->right->right = new TreeNode(4);
    string expected_1 = "dba";
    string output_1 = sol.smallestFromLeaf(root_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    TreeNode *root_2 = new TreeNode(25);
    root_2->left = new TreeNode(1);
    root_2->right = new TreeNode(3);
    root_2->left->left = new TreeNode(1);
    root_2->left->right = new TreeNode(3);
    root_2->right->left = new TreeNode(0);
    root_2->right->right = new TreeNode(2);
    string expected_2 = "adz";
    string output_2 = sol.smallestFromLeaf(root_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    TreeNode *root_3 = new TreeNode(2);
    root_3->left = new TreeNode(2);
    root_3->right = new TreeNode(1);
    root_3->left->right = new TreeNode(1);
    root_3->left->right->left = new TreeNode(0);
    root_3->right->left = new TreeNode(0);
    string expected_3 = "abc";
    string output_3 = sol.smallestFromLeaf(root_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}