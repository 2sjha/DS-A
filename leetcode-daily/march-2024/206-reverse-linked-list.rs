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


**Follow up:** A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

fn print_linked_list(head: Option<Box<ListNode>>) {
    let mut tmp: Option<Box<ListNode>> = head.clone();
    loop {
        if tmp.is_none() {
            break;
        }
        print!("{} ", tmp.as_ref().unwrap().val);
        tmp = tmp.as_mut().unwrap().next.take();
    }
    println!()
}

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution;
impl Solution {
    pub fn reverse_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if head.is_none() || head.as_ref().unwrap().next.is_none() {
            return head;
        }

        let mut head: Option<Box<ListNode>> = head;
        let mut prev: Option<Box<ListNode>> = None;
        let mut next: Option<Box<ListNode>>;
        while !head.is_none() {
            next = head.as_mut().unwrap().next.take();
            head.as_mut().unwrap().next = prev.take();
            prev = head;
            head = next;
        }

        prev
    }
}

fn main() {
    let head_1: Option<Box<ListNode>> = Some(Box::new(ListNode {
        val: 1,
        next: Some(Box::new(ListNode {
            val: 2,
            next: Some(Box::new(ListNode {
                val: 3,
                next: Some(Box::new(ListNode {
                    val: 4,
                    next: Some(Box::new(ListNode::new(5))),
                })),
            })),
        })),
    }));
    let output_1: Option<Box<ListNode>> = Solution::reverse_list(head_1);
    print_linked_list(output_1);

    let head_2: Option<Box<ListNode>> = Some(Box::new(ListNode {
        val: 1,
        next: Some(Box::new(ListNode::new(2))),
    }));
    let output_2: Option<Box<ListNode>> = Solution::reverse_list(head_2);
    print_linked_list(output_2);

    let head_3: Option<Box<ListNode>> = None;
    let output_3: Option<Box<ListNode>> = Solution::reverse_list(head_3);
    print_linked_list(output_3);
}
