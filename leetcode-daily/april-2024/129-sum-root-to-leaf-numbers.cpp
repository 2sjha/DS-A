/*
https://leetcode.com/problems/sum-root-to-leaf-numbers

You are given the `root` of a binary tree containing digits from `0` to `9` only.

Each root-to-leaf path in the tree represents a number.

* For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.

Return *the total sum of all root-to-leaf numbers*. Test cases are generated so that the answer will
fit in a **32-bit** integer.

A **leaf** node is a node with no children.


**Example 1:**

**Input:** root = [1,2,3]
**Output:** 25
**Explanation:**
The root-to-leaf path `1->2` represents the number `12`.
The root-to-leaf path `1->3` represents the number `13`.
Therefore, sum = 12 + 13 = `25`.

**Example 2:**

**Input:** root = [4,9,0,5,1]
**Output:** 1026
**Explanation:**
The root-to-leaf path `4->9->5` represents the number 495.
The root-to-leaf path `4->9->1` represents the number 491.
The root-to-leaf path `4->0` represents the number 40.
Therefore, sum = 495 + 491 + 40 = `1026`.


**Constraints:**

* The number of nodes in the tree is in the range `[1, 1000]`.
* `0 <= Node.val <= 9`
* The depth of the tree will not exceed `10`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int vecToInt(vector<int> &digits) {
        int n = digits.size();
        int num = 0;
        for (int i = 0; i < n; ++i) {
            num = num * 10 + digits[i];
        }
        return num;
    }

    void dfs(TreeNode *root, vector<int> &digits, int &sum) {
        if (root == nullptr)
            return;

        digits.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            sum += vecToInt(digits);
        } else {
            dfs(root->left, digits, sum);
            dfs(root->right, digits, sum);
        }

        digits.pop_back();
    }

  public:
    int sumNumbers(TreeNode *root) {
        int sum = 0;
        vector<int> digits;
        dfs(root, digits, sum);
        return sum;
    }
};

int main() {
    Solution sol;

    TreeNode *root_1 = new TreeNode(1);
    root_1->left = new TreeNode(2);
    root_1->right = new TreeNode(3);
    int expected_1 = 25;
    int output_1 = sol.sumNumbers(root_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    TreeNode *root_2 = new TreeNode(4);
    root_2->right = new TreeNode(0);
    root_2->left = new TreeNode(9);
    root_2->left->left = new TreeNode(5);
    root_2->left->right = new TreeNode(1);
    int expected_2 = 1026;
    int output_2 = sol.sumNumbers(root_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}