/*
https://leetcode.com/problems/reverse-linked-list/

Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:

Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:

Input: head = [1,2]
Output: [2,1]

Example 3:

Input: head = []
Output: []


Constraints:

    The number of nodes in the list is the range [0, 5000].
    -5000 <= Node.val <= 5000
*/

#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *next = head->next;
        head->next = nullptr;
        ListNode *tmp = nullptr;
        while (next != nullptr) {
            tmp = next->next;
            next->next = head;

            head = next;
            next = tmp;
        }
        return head;
    }
};

int main() {

    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    Solution s;
    head = s.reverseList(head);
    cout << head->val << head->next->val << head->next->next->val;

    return 0;
}