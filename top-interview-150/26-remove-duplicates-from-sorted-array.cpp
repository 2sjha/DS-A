/*
https://leetcode.com/problems/remove-duplicates-from-sorted-array

Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates
[**in-place**][1] such that each unique element appears only **once**. The **relative order** of the
elements should be kept the **same**. Then return *the number of unique elements in *`nums`.

Consider the number of unique elements of `nums` to be `k`, to get accepted, you need to do the
following things:

* Change the array `nums` such that the first `k` elements of `nums` contain the unique elements in
the order they were present in `nums` initially. The remaining elements of `nums` are not important
as well as the size of `nums`.
* Return `k`.

**Custom Judge:**

The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}

If all assertions pass, then your solution will be **accepted**.


**Example 1:**

**Input:** nums = [1,1,2]
**Output:** 2, nums = [1,2,_]
**Explanation:** Your function should return k = 2, with the first two elements of nums being 1 and
2 respectively. It does not matter what you leave beyond the returned k (hence they are
underscores).

**Example 2:**

**Input:** nums = [0,0,1,1,1,2,2,3,3,4]
**Output:** 5, nums = [0,1,2,3,4,_,_,_,_,_]
**Explanation:** Your function should return k = 5, with the first five elements of nums being 0, 1,
2, 3, and 4 respect ively. It does not matter what you leave beyond the returned k (hence they are
underscores).


**Constraints:**

* `1 <= nums.length <= 3 * 10⁴`
* `-100 <= nums[i] <= 100`
* `nums` is sorted in **non-decreasing** order.

[1]: https://en.wikipedia.org/wiki/In-place_algorithm
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 1;

        int curr = 0;
        int next = 1;
        int unique = 0;
        while(next < n) {
            while(next < n && nums[next] == nums[curr]) {
                next++;
            }
            if(curr < n - 1 && next < n) {
                curr++;
                nums[curr] = nums[next];
            }
            unique++;
        }
        return unique; 
    }
};

int main() {
    Solution sol;

    vector<int> nums_1 = {1, 1, 2};
    int expected_1 = 2;
    int output_1 = sol.removeDuplicates(nums_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    vector<int> nums_2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int expected_2 = 5;
    int output_2 = sol.removeDuplicates(nums_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    return 0;
}