/*
https://leetcode.com/problems/serialize-and-deserialize-binary-tree

Serialization is the process of converting a data structure or object into a sequence of bits so
that it can be stored in a file or memory buffer, or transmitted across a network connection link to
be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your
serialization/deserialization algorithm should work. You just need to ensure that a binary tree can
be serialized to a string and this string can be deserialized to the original tree structure.

**Clarification:** The input/output format is the same as [how LeetCode serializes a binary
tree][1]. You do not necessarily need to follow this format, so please be creative and come up with
different approaches yourself.


**Example 1:**

**Input:** root = [1,2,3,null,null,4,5]
**Output:** [1,2,3,null,null,4,5]

**Example 2:**

**Input:** root = []
**Output:** []


**Constraints:**

* The number of nodes in the tree is in the range `[0, 10⁴]`.
* `-1000 <= Node.val <= 1000`

[1]:
https://support.leetcode.com/hc/en-us/articles/360011883654-What-does-1-null-2-3-mean-in-binary-tree-representation
-
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

class Codec {
  private:
    vector<string> split(string s, char sep) {
        vector<string> parts;

        string curr = "";
        for (char c : s) {
            if (c == sep) {
                parts.push_back(curr);
                curr = "";
            } else {
                curr.push_back(c);
            }
        }
        parts.push_back(curr);
        return parts;
    }

    int getMaxLevels(TreeNode *node, int curr) {
        if (node == NULL)
            return curr;
        else {
            return max(getMaxLevels(node->left, curr + 1), getMaxLevels(node->right, curr + 1));
        }
    }

    TreeNode *dfsCreateTree(vector<vector<string>> &nodes, vector<int> &next, int curr_level) {
        if (curr_level >= nodes.size())
            return NULL;
        if (next[curr_level] >= nodes[curr_level].size())
            return NULL;

        string val = nodes[curr_level][next[curr_level]];
        next[curr_level]++;

        if (val == "null") {
            return NULL;
        }

        TreeNode *curr = new TreeNode(stoi(val));
        curr->left = dfsCreateTree(nodes, next, curr_level + 1);
        curr->right = dfsCreateTree(nodes, next, curr_level + 1);

        return curr;
    }

  public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        if (root == NULL)
            return "[]";

        int max_levels = getMaxLevels(root, 0);

        string res = "[{";
        res += to_string(root->val);

        int curr_level = 0;
        queue<pair<TreeNode *, int>> bfs_q;
        bfs_q.push({root->left, 1});
        bfs_q.push({root->right, 1});

        while (!bfs_q.empty()) {
            pair<TreeNode *, int> curr = bfs_q.front();
            bfs_q.pop();

            if (curr.second >= max_levels)
                continue;

            if (curr.second > curr_level) {
                if (res[res.length() - 1] == ',')
                    res.pop_back();

                res += "};{";
                curr_level = curr.second;
            }

            TreeNode *node = curr.first;
            if (node == NULL) {
                res += "null,";
            } else {
                res += to_string(node->val);
                res.push_back(',');

                bfs_q.push({node->left, curr.second + 1});
                bfs_q.push({node->right, curr.second + 1});
            }
        }

        if (res[res.length() - 1] == ',')
            res.pop_back();

        res += "}]";
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        if (data == "[]")
            return NULL;

        data = data.substr(1, data.length() - 2);
        vector<vector<string>> nodes;
        vector<string> levels = split(data, ';');
        for (string level : levels) {
            level = level.substr(1, level.length() - 2);
            vector<string> level_nodes = split(level, ',');
            nodes.push_back(level_nodes);
        }

        vector<int> next(nodes.size(), 0);
        return dfsCreateTree(nodes, next, 0);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main() {
    Codec ser, deser;

    TreeNode *root1_1 = new TreeNode(1);
    root1_1->left = new TreeNode(2);
    root1_1->right = new TreeNode(3);
    root1_1->right->left = new TreeNode(4);
    root1_1->right->right = new TreeNode(5);
    root1_1->right->right->right = new TreeNode(6);
    cout << ser.serialize(root1_1) << endl;

    TreeNode *root1_2 = deser.deserialize("[{1};{2,3};{null,null,4,5};{null,null,null,6}]");
    cout << ser.serialize(root1_2) << endl;

    TreeNode *root2_1 = new TreeNode(1);
    root2_1->left = new TreeNode(2);
    root2_1->right = new TreeNode(3);
    root2_1->left->left = new TreeNode(4);
    root2_1->left->right = new TreeNode(5);
    root2_1->right->left = new TreeNode(6);
    root2_1->right->right = new TreeNode(7);
    root2_1->left->left->left = new TreeNode(8);
    root2_1->left->left->right = new TreeNode(9);
    root2_1->left->right->left = new TreeNode(10);
    root2_1->left->right->right = new TreeNode(11);
    root2_1->right->left->left = new TreeNode(12);
    root2_1->right->left->right = new TreeNode(13);
    root2_1->right->right->left = new TreeNode(14);
    root2_1->right->right->right = new TreeNode(15);
    cout << ser.serialize(root2_1) << endl;

    TreeNode *root2_2 = deser.deserialize("[{1};{2,3};{4,5,6,7},{8,9,10,11,12,13,14,15}]");
    cout << ser.serialize(root2_2) << endl;

    return 0;
}