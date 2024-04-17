#ifndef PRINTUTILS_H
#define PRINTUTILS_H

#include <cstddef>
#include <iostream>
#include <vector>

template <typename T> void print2Dmatrix(std::vector<std::vector<T>> matrix);
template <typename T> void print2Dmatrix(std::vector<std::vector<T>> matrix) {
    if (matrix.empty()) {
        std::cout << "Matrix Empty!" << std::endl;
        return;
    }

    for (std::vector<T> row : matrix) {
        if (row.empty()) {
            std::cout << "Empty!" << std::endl;
            continue;
        }

        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

template <typename T> void printArray(std::vector<T> arr);
template <typename T> void printArray(std::vector<T> arr) {
    if (arr.empty()) {
        std::cout << "Empty!" << std::endl << std::endl;
        return;
    }

    for (auto i : arr)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;
};

template <typename T> void printPairArray(std::vector<std::pair<T, T>> arr);
template <typename T> void printPairArray(std::vector<std::pair<T, T>> arr) {
    if (arr.empty()) {
        std::cout << "Empty!" << std::endl << std::endl;
        return;
    }

    for (auto i : arr)
        std::cout << i.first << "," << i.second << " ";
    std::cout << std::endl << std::endl;
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printLinkedList(ListNode *head);
void printLinkedList(ListNode *head) {
    if (head == nullptr) {
        std::cout << "Empty!" << std::endl << std::endl;
        return;
    }

    ListNode *tmp = head;
    while (tmp != nullptr) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl << std::endl;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Code taken from this stackoverflow post
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
void printBT(const std::string &prefix, const TreeNode *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->val << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBinaryTree(const TreeNode *node);
void printBinaryTree(const TreeNode *node) { printBT("", node, false); }

#endif /* PRINTUTILS_H */
