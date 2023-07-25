/*
https://leetcode.com/problems/peak-index-in-a-mountain-array

An array arr is a mountain if the following properties hold:

    arr.length >= 3
    There exists some i with 0 < i < arr.length - 1 such that:
        arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
        arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Given a mountain array arr, return the index i such that arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
> arr[i + 1] > ... > arr[arr.length - 1].

You must solve it in O(log(arr.length)) time complexity.


Example 1:

Input: arr = [0,1,0]
Output: 1

Example 2:

Input: arr = [0,2,1,0]
Output: 1

Example 3:

Input: arr = [0,10,5,2]
Output: 1


Constraints:

    3 <= arr.length <= 105
    0 <= arr[i] <= 106
    arr is guaranteed to be a mountain array.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    int peakIdx(vector<int> &arr, int start, int end) {
        if (start == end) {
            return -1;
        }

        int n = arr.size();
        int mid = start + ((end - start) / 2);
        if (mid > 0 && arr[mid] > arr[mid - 1] && mid < n - 1 && arr[mid] > arr[mid + 1]) {
            return mid;
        }

        int left = peakIdx(arr, start, mid);
        int right = peakIdx(arr, mid + 1, end);

        if (left == -1 && right == -1) {
            return -1;
        } else if (left == -1) {
            return right;
        } else {
            return left;
        }
    }

  public:
    int peakIndexInMountainArrayRecursive(vector<int> &arr) {
        int n = arr.size();
        return peakIdx(arr, 0, n - 1);
    }

    int peakIndexInMountainArray(vector<int> &arr) {
        int n = arr.size();
        int start = 0;
        int end = n - 1;
        int mid;

        while (start < end) {
            mid = start + ((end - start) / 2);
            if (mid > 0 && arr[mid] > arr[mid - 1] && mid < n - 1 && arr[mid] > arr[mid + 1]) {
                break;
            } else if (mid > 0 && arr[mid - 1] < arr[mid] && mid < n - 1 &&
                       arr[mid] < arr[mid + 1]) {
                start = mid;
            } else {
                end = mid;
            }
        }

        return mid;
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> nums1 = {0, 1, 0};
    res = sol.peakIndexInMountainArray(nums1);
    cout << res << endl;
    assert(res == 1);

    vector<int> nums2 = {0, 2, 1, 0};
    res = sol.peakIndexInMountainArray(nums2);
    cout << res << endl;
    assert(res == 1);

    vector<int> nums3 = {0, 10, 5, 2};
    res = sol.peakIndexInMountainArray(nums3);
    cout << res << endl;
    assert(res == 1);

    return 0;
}