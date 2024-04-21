/*
https://leetcode.com/problems/trapping-rain-water

Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water
it can trap after raining.


**Example 1:**

**Input:** height = [0,1,0,2,1,0,1,3,2,1,2,1]
**Output:** 6
**Explanation:** The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case
, 6 units of rain water (blue section) are being trapped.

**Example 2:**

**Input:** height = [4,2,0,3,2,5]
**Output:** 9


**Constraints:**

* `n == height.length`
* `1 <= n <= 2 * 10⁴`
* `0 <= height[i] <= 10⁵`
*/

struct Solution;
impl Solution {
    fn flow_left(height: &Vec<i32>, st: &mut Vec<i32>) -> usize {
        let mut i: usize = 0;
        let n: usize = height.len();
        st.push(height[i]);
        i += 1;

        while i < n && height[i] >= st[0] {
            st.pop();
            st.push(height[i]);
            i += 1;
        }

        i
    }

    fn collect(height: &Vec<i32>, end: bool) -> i32 {
        let mut st: Vec<i32> = Vec::new();
        let mut i = Self::flow_left(height, &mut st);
        let n: usize = height.len();
        let mut res: i32 = 0;

        while i < n {
            while i < n && height[i] < st[0] {
                st.push(height[i]);
                i += 1;
            }

            if i == n {
                if !end {
                    st.reverse();
                    res += Self::collect(&st, true);
                }
            } else {
                let m: usize = st.len();
                for j in 1..m {
                    res += st[0] - st[j];
                }
                st.clear();
                st.push(height[i]);
                i += 1;
            }
        }

        res
    }

    pub fn trap(height: Vec<i32>) -> i32 {
        Self::collect(&height, false)
    }
}

fn main() {
    let height_1: Vec<i32> = vec![0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1];
    let expected_1: i32 = 6;
    let output_1: i32 = Solution::trap(height_1);
    println!("{:?}", output_1);
    assert!(output_1 == expected_1);

    let height_2: Vec<i32> = vec![4, 2, 0, 3, 2, 5];
    let expected_2: i32 = 9;
    let output_2: i32 = Solution::trap(height_2);
    println!("{:?}", output_2);
    assert!(output_2 == expected_2);
}
