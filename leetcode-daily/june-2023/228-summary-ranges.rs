/*
https://leetcode.com/problems/summary-ranges

You are given a sorted unique integer array nums.

A range [a,b] is the set of all integers from a to b (inclusive).

Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.

Each range [a,b] in the list should be output as:

    "a->b" if a != b
    "a" if a == b


Example 1:

Input: nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: The ranges are:
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"

Example 2:

Input: nums = [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: The ranges are:
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"


Constraints:

    0 <= nums.length <= 20
    -231 <= nums[i] <= 231 - 1
    All the values of nums are unique.
    nums is sorted in ascending order.
*/

struct Solution;
impl Solution {
    pub fn summary_ranges(nums: Vec<i32>) -> Vec<String> {
        let sz: usize = nums.len();
        let mut res: Vec<String> = Vec::new();

        if sz == 0 {
            return res;
        }

        let mut r_st: usize = 0;
        let mut r_en: usize = 0;
        let mut put: String;

        for i in 1..sz {
            if nums[i] == nums[i - 1] + 1 {
                r_en += 1;
            } else {
                if r_st == r_en {
                    res.push(nums[r_st].to_string());
                } else {
                    put = nums[r_st].to_string();
                    put += "->";
                    put += &nums[r_en].to_string();
                    res.push(put);
                }

                r_st = i;
                r_en = i;
            }
        }

        if r_st == r_en {
            res.push(nums[r_st].to_string());
        } else {
            put = nums[r_st].to_string();
            put += "->";
            put += &nums[r_en].to_string();
            res.push(put);
        }

        return res;
    }
}

fn main() {
    let mut res: Vec<String>;

    let nums1: Vec<i32> = vec![0, 1, 2, 4, 5, 7];
    res = Solution::summary_ranges(nums1);
    println!("{:?}", res);

    let nums2: Vec<i32> = vec![0, 2, 3, 4, 6, 8, 9];
    res = Solution::summary_ranges(nums2);
    println!("{:?}", res);
}
