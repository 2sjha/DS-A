/*
https://leetcode.com/problems/merge-in-between-linked-lists

You are given two linked lists: `list1` and `list2` of sizes `n` and `m` respectively.

Remove `list1`'s nodes from the `a^{th}` node to the `b^{th}` node, and put `list2` in their place.

The blue edges and nodes in the following figure indicate the result:

*Build the result list and return its head.*


**Example 1:**

**Input:** list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
**Output:** [10,1,13,1000000,1000001,1000002,5]
**Explanation:** We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges
and nodes in the ab ove figure indicate the result.

**Example 2:**

**Input:** list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
**Output:** [0,1,1000000,1000001,1000002,1000003,1000004,6]
**Explanation:** The blue edges and nodes in the above figure indicate the result.


**Constraints:**

* `3 <= list1.length <= 10⁴`
* `1 <= a <= b < list1.length - 1`
* `1 <= list2.length <= 10⁴`
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2) {
        int count = 0;
        ListNode *res = list1;
        ListNode *nodeA = list1;
        ListNode *tail2 = list2;
        ListNode *nodeB;

        while (count < a - 1) {
            nodeA = nodeA->next;
            count++;
        }

        nodeB = nodeA;
        while (count < b + 1) {
            nodeB = nodeB->next;
            count++;
        }

        while (tail2->next != nullptr) {
            tail2 = tail2->next;
        }

        nodeA->next = list2;
        tail2->next = nodeB;

        return res;
    }
};

int main() {
    Solution sol;

    ListNode *list1_1 = new ListNode(10);
    list1_1->next = new ListNode(1);
    list1_1->next->next = new ListNode(13);
    list1_1->next->next->next = new ListNode(6);
    list1_1->next->next->next->next = new ListNode(9);
    list1_1->next->next->next->next->next = new ListNode(5);
    int a_1 = 3;
    int b_1 = 4;
    ListNode *list2_1 = new ListNode(1000000);
    list2_1->next = new ListNode(1000001);
    list2_1->next->next = new ListNode(1000002);
    printLinkedList(sol.mergeInBetween(list1_1, a_1, b_1, list2_1));

    ListNode *list1_2 = new ListNode(0);
    list1_2->next = new ListNode(1);
    list1_2->next->next = new ListNode(2);
    list1_2->next->next->next = new ListNode(3);
    list1_2->next->next->next->next = new ListNode(4);
    list1_2->next->next->next->next->next = new ListNode(5);
    list1_2->next->next->next->next->next->next = new ListNode(6);
    int a_2 = 2;
    int b_2 = 5;
    ListNode *list2_2 = new ListNode(1000000);
    list2_2->next = new ListNode(1000001);
    list2_2->next->next = new ListNode(1000002);
    list2_2->next->next->next = new ListNode(10000003);
    list2_2->next->next->next->next = new ListNode(1000004);
    printLinkedList(sol.mergeInBetween(list1_2, a_2, b_2, list2_2));

    return 0;
}