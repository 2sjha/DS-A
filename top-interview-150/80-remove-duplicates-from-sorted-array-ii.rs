/*
https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

Given an integer array `nums` sorted in **non-decreasing order**, remove some duplicates [**in-place**][1] such that
each unique element appears **at most twice**. The **relative order** of the elements should be kept the **same**.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed
in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then
the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k`
elements.

Return `k`* after placing the final result in the first *`k`* slots of *`nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place][2]** with
O(1) extra memory.

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

**Input:** nums = [1,1,1,2,2,3]
**Output:** 5, nums = [1,1,2,2,3,_]
**Explanation:** Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respecti
vely.
It does not matter what you leave beyond the returned k (hence they are underscores).

**Example 2:**

**Input:** nums = [0,0,1,1,1,1,2,3,3]
**Output:** 7, nums = [0,0,1,1,2,3,3,_,_]
**Explanation:** Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 r
espectively.
It does not matter what you leave beyond the returned k (hence they are underscores).


**Constraints:**

* `1 <= nums.length <= 3 * 10⁴`
* `-10⁴ <= nums[i] <= 10⁴`
* `nums` is sorted in **non-decreasing** order.

[1]: https://en.wikipedia.org/wiki/In-place_algorithm
[2]: https://en.wikipedia.org/wiki/In-place_algorithm
*/

struct Solution;
impl Solution {
    fn swap(nums: &mut Vec<i32>, i: usize, j: usize) {
        let t: i32 = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }

    pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        let n: usize = nums.len();
        let mut res: usize = 0;
        let mut prev: usize;
        let mut next: usize;
        let mut i: usize = 0;
        let tmp: i32 = 10001;

        while i < n {
            if i == n - 1
                || nums[i] == tmp
                || (i < n - 1 && nums[i] != nums[i + 1])
            {
                i += 1;
                continue;
            } else {
                next = i + 2;
                while next < n && nums[next] == nums[i] {
                    nums[next] = tmp;
                    next += 1;
                }
                i = next;
            }
        }

        for j in 0..n {
            if nums[j] != tmp {
                res += 1;
            }
        }

        prev = 0;
        i = 0;
        while i < n {
            if nums[i] != tmp {
                i += 1;
                prev += 1;
                continue;
            }

            while i < n && nums[i] == nums[prev] {
                i += 1;
            }
			if i >= n {
				break;
			}

            if i < n - 1 && nums[i] == nums[i + 1] {
                Self::swap(nums, prev, i);
                prev += 1;
                Self::swap(nums, prev, i+1);
                prev += 1;
                i += 1;
            } else {
                Self::swap(nums, prev, i);
                prev += 1;
            }
        }

        res as i32
    }
}

fn main() {
    let mut nums_1: Vec<i32> = vec![1,1,1,2,2,3];
    let expected_1: i32 = 5;
    let output_1: i32 = Solution::remove_duplicates(&mut nums_1);
    println!("{:?}", output_1);
    println!("{:?}", nums_1);
    assert!(output_1 == expected_1);

    let mut nums_2: Vec<i32> = vec![0, 0, 1, 1, 1, 1, 2, 3, 3];
    let expected_2: i32 = 7;
    let output_2: i32 = Solution::remove_duplicates(&mut nums_2);
    println!("{:?}", output_2);
    println!("{:?}", nums_2);
    assert!(output_2 == expected_2);

	let mut nums_3: Vec<i32> = vec![1, 1, 1, 1];
    let expected_3: i32 = 2;
    let output_3: i32 = Solution::remove_duplicates(&mut nums_3);
    println!("{:?}", output_3);
    println!("{:?}", nums_3);
	assert!(output_3 == expected_3);
}
