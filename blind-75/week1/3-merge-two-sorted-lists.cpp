/*
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of
the first two lists.

Return the head of the merged linked list.



Example 1:

Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:

Input: list1 = [], list2 = []
Output: []

Example 3:

Input: list1 = [], list2 = [0]
Output: [0]



Constraints:

    The number of nodes in both lists is in the range [0, 50].
    -100 <= Node.val <= 100
    Both list1 and list2 are sorted in non-decreasing order.
*/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) {
            return list2;
        } else if (list2 == nullptr) {
            return list1;
        }

        ListNode* mergedList;
        ListNode* curr1 = list1;
        ListNode* curr2 = list2;
        ListNode* curr;
        ListNode* temp;

        if (curr1->val > curr2->val) {
            curr = curr2;
            curr2 = curr2->next;
        } else {
            curr = curr1;
            curr1 = curr1->next;
        }
        mergedList = curr;

        while (curr1 != nullptr || curr2 != nullptr) {
            temp = curr;
            if (curr1 == nullptr) {
                curr = curr2;
                temp->next = curr;
                break;
            } else if (curr2 == nullptr) {
                curr = curr1;
                temp->next = curr;
                break;
            } else if (curr1->val > curr2->val) {
                curr = curr2;
                curr2 = curr2->next;
            } else {
                curr = curr1;
                curr1 = curr1->next;
            }
            temp->next = curr;
        }

        return mergedList;
    }
};

void inputList(int n, ListNode*& list) {
    ListNode* temp;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        if (i == 0) {
            list = new ListNode(k);
            temp = list;
        } else {
            ListNode* curr = new ListNode(k);
            temp->next = curr;
            temp = curr;
        }
    }
}

void printList(ListNode*& list) {
    ListNode* curr = list;
    while (curr != nullptr) {
        cout << curr->val << " ";
        curr = curr->next;
    }
}

int main() {
    Solution sol;
    int n;
    ListNode* list1;
    ListNode* list2;

    cout << "Enter number of elements in first list" << endl;
    cin >> n;
    cout << "Enter first list elements space separated" << endl;
    inputList(n, list1);

    cout << "Enter number of elements in second list" << endl;
    cin >> n;
    cout << "Enter second list elements space separated" << endl;
    inputList(n, list2);

    // printList(list1);
    // printList(list2);

    ListNode* mergedList = sol.mergeTwoLists(list1, list2);
    printList(mergedList);

    return 0;
}