/*
https://leetcode.com/problems/reverse-linked-list

Given the `head` of a singly linked list, reverse the list, and return *the reversed list*.


**Example 1:**

**Input:** head = [1,2,3,4,5]
**Output:** [5,4,3,2,1]

**Example 2:**

**Input:** head = [1,2]
**Output:** [2,1]

**Example 3:**

**Input:** head = []
**Output:** []


**Constraints:**

* The number of nodes in the list is the range `[0, 5000]`.
* `-5000 <= Node.val <= 5000`


**Follow up:** A linked list can be reversed either iteratively or recursively. Could you implement
both?
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr)
            return head;

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
};

int main() {
    Solution sol;

    ListNode *head_1 = new ListNode(1);
    head_1->next = new ListNode(2);
    head_1->next->next = new ListNode(3);
    head_1->next->next->next = new ListNode(4);
    head_1->next->next->next->next = new ListNode(5);
    ListNode *output_1 = sol.reverseList(head_1);
    printLinkedList(output_1);

    ListNode *head_2 = new ListNode(1);
    head_2->next = new ListNode(2);
    ListNode *output_2 = sol.reverseList(head_2);
    printLinkedList(output_2);

    ListNode *head_3 = nullptr;
    ListNode *output_3 = sol.reverseList(head_3);
    printLinkedList(output_3);

    return 0;
}