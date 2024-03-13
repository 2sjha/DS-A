/*
https://leetcode.com/problems/merge-k-sorted-lists/description/

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.


Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:

Input: lists = []
Output: []

Example 3:

Input: lists = [[]]
Output: []


Constraints:

    k == lists.length
    0 <= k <= 10^4
    0 <= lists[i].length <= 500
    -10^4 <= lists[i][j] <= 10^4
    lists[i] is sorted in ascending order.
    The sum of lists[i].length will not exceed 10^4.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    ListNode *findSmallest(vector<ListNode *> &lists) {
        int n = lists.size();
        int min_idx = 0, min_val = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (lists[i] != NULL && min_val > lists[i]->val) {
                min_val = lists[i]->val;
                min_idx = i;
            }
        }

        lists[min_idx] = lists[min_idx]->next;
        return new ListNode(min_val);
    }

    bool all_empty(vector<ListNode *> &lists) {
        int n = lists.size();
        for (int i = 0; i < n; ++i) {
            if (lists[i] != NULL)
                return false;
        }

        return true;
    }

  public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int n = lists.size();
        ListNode *head = NULL;
        ListNode *tail = NULL;
        while (!all_empty(lists)) {
            ListNode *node = findSmallest(lists);
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }

        return head;
    }
};

int main() {
    Solution sol;
    ListNode *res;

    ListNode *list1 = new ListNode(1);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(5);

    ListNode *list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ListNode *list3 = new ListNode(2);
    list1->next = new ListNode(6);

    vector<ListNode *> lists1 = {list1, list2, list3};
    res = sol.mergeKLists(lists1);
    printLinkedList(res);

    vector<ListNode *> lists2 = {};
    res = sol.mergeKLists(lists2);
    printLinkedList(res);

    vector<ListNode *> lists3 = {NULL};
    res = sol.mergeKLists(lists3);
    printLinkedList(res);

    return 0;
}