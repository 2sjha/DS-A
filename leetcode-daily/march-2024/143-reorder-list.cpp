/*
https://leetcode.com/problems/reorder-list

You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln

*Reorder the list to be on the following form:*

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …

You may not modify the values in the list's nodes. Only nodes themselves may be changed.


**Example 1:**

**Input:** head = [1,2,3,4]
**Output:** [1,4,2,3]

**Example 2:**

**Input:** head = [1,2,3,4,5]
**Output:** [1,5,2,4,3]


**Constraints:**

* The number of nodes in the list is in the range `[1, 5 * 10⁴]`.
* `1 <= Node.val <= 1000`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int getSize(ListNode *head) {
        ListNode *tmp = head;
        int sz = 0;
        while (tmp != nullptr) {
            tmp = tmp->next;
            sz++;
        }
        return sz;
    }

    ListNode *reverse(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *next = nullptr;
        while (head != nullptr) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }

    pair<ListNode *, ListNode *> splitList(ListNode *head) {
        int size = getSize(head);
        if (size <= 1)
            return {head, nullptr};

        ListNode *first = head;
        ListNode *tmp = head;
        for (int i = 0; i < size / 2 - 1; ++i) {
            tmp = tmp->next;
        }
        ListNode *second = tmp->next;
        tmp->next = nullptr;

        return {first, second};
    }

  public:
    void reorderList(ListNode *head) {
        pair<ListNode *, ListNode *> split = splitList(head);
        ListNode *first = split.first;
        ListNode *second = reverse(split.second);

        ListNode *next1 = nullptr;
        ListNode *next2 = nullptr;
        while (first != nullptr && second != nullptr) {
            next1 = first->next;
            next2 = second->next;

            first->next = second;
            if (next1 != nullptr) {
                second->next = next1;
            }

            first = next1;
            second = next2;
        }
    }
};

int main() {
    Solution sol;

    ListNode *head_1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    sol.reorderList(head_1);
    printLinkedList(head_1);

    ListNode *head_2 =
        new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    sol.reorderList(head_2);
    printLinkedList(head_2);

    return 0;
}