/*
https://leetcode.com/problems/kth-smallest-element-in-a-bst/

Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed)
of all the values of the nodes in the tree.


Example 1:

Input: root = [3,1,4,null,2], k = 1
Output: 1

Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3


Constraints:

    The number of nodes in the tree is n.
    1 <= k <= n <= 104
    0 <= Node.val <= 104

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need
to find the kth smallest frequently, how would you optimize?
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
    multiset<int> s;
    int k;

    void findKthSmallest(TreeNode *root) {
        if (root == nullptr) {
            return;
        }

        if (s.size() < this->k) {
            s.insert(root->val);
        } else {
            if (root->val < *s.rbegin()) {
                s.erase(--s.end());
                s.insert(root->val);
            }
        }

        findKthSmallest(root->left);
        findKthSmallest(root->right);
    }

  public:
    int kthSmallest(TreeNode *root, int k) {
        this->k = k;
        this->s = multiset<int>();

        findKthSmallest(root);

        return *s.rbegin();
    }
};

int main() {
    Solution sol;
    int res;

    int k = 1;
    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);
    root1->left->right = new TreeNode(2);
    res = sol.kthSmallest(root1, k);
    cout << res << endl;
    assert(res == 1);

    k = 3;
    TreeNode *root2 = new TreeNode(5);
    root2->right = new TreeNode(6);
    root2->left = new TreeNode(3);
    root2->left->right = new TreeNode(4);
    root2->left->left = new TreeNode(2);
    root2->left->left->left = new TreeNode(1);
    res = sol.kthSmallest(root1, k);
    cout << res << endl;
    assert(res == 3);

    return 0;
}