/*
https://leetcode.com/problems/palindrome-linked-list

Given the `head` of a singly linked list, return `true`* if it is a **palindrome** or *`false`*
otherwise*.


**Example 1:**

**Input:** head = [1,2,2,1]
**Output:** true

**Example 2:**

**Input:** head = [1,2]
**Output:** false


**Constraints:**

* The number of nodes in the list is in the range `[1, 10⁵]`.
* `0 <= Node.val <= 9`


**Follow up:** Could you do it in `O(n)` time and `O(1)` space?
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    pair<ListNode *, ListNode *> equalSplit(ListNode *head, int count) {
        ListNode *tmp = head;
        if (count % 2 == 0) {
            for (int i = 0; i < count / 2; ++i) {
                tmp = tmp->next;
            }
        } else {
            for (int i = 0; i < (count + 1) / 2; ++i) {
                tmp = tmp->next;
            }
        }

        return {head, tmp};
    }

    ListNode *reverse(ListNode *head) {
        ListNode *next = nullptr;
        ListNode *prev = nullptr;

        while (head != nullptr) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }

  public:
    bool isPalindrome(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        ListNode *tmp = head;
        int count = 0;
        while (tmp != nullptr) {
            count++;
            tmp = tmp->next;
        }

        pair<ListNode *, ListNode *> split = equalSplit(head, count);
        ListNode *reversed = reverse(split.second);

        while (reversed != nullptr && head != nullptr) {
            if (reversed->val != head->val)
                return false;
            reversed = reversed->next;
            head = head->next;
        }
        return true;
    }
};

int main() {
    Solution sol;

    ListNode *head_1 = new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(1))));
    bool expected_1 = true;
    bool output_1 = sol.isPalindrome(head_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    ListNode *head_2 = new ListNode(1, new ListNode(2));
    bool expected_2 = false;
    bool output_2 = sol.isPalindrome(head_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}