/*
https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1

Given an array of integers. Find the Inversion Count in the array.

Inversion Count: For an array, inversion count indicates how far (or close) the array is from being
sorted. If array is already sorted then the inversion count is 0. If an array is sorted in the
reverse order then the inversion count is the maximum. Formally, two elements a[i] and a[j] form an
inversion if a[i] > a[j] and i < j.


Example 1:

Input: N = 5, arr[] = {2, 4, 1, 3, 5}
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5
has three inversions (2, 1), (4, 1), (4, 3).

Example 2:

Input: N = 5
arr[] = {2, 3, 4, 5, 6}
Output: 0
Explanation: As the sequence is already
sorted so there is no inversion count.

Example 3:

Input: N = 3, arr[] = {10, 10, 10}
Output: 0
Explanation: As all the elements of array
are same, so there is no inversion count.

Your Task:
You don't need to read input or print anything. Your task is to complete the function
inversionCount() which takes the array arr[] and the size of the array as inputs and returns the
inversion count of the given array.

Expected Time Complexity: O(NLogN).
Expected Auxiliary Space: O(N).

Constraints:
1 ≤ N ≤ 5*105
1 ≤ arr[i] ≤ 1018
*/

#include <bits/stdc++.h>
using namespace std;

// CS6363: DAA - Homework 1
class Solution {
  private:
    long long int inversionCountMerge(long long arr[], long long start, long long mid,
                                      long long end) {
        long long size = end - start + 1;
        vector<long long> tmp = vector<long long>(size, -1);

        long long inv = 0;
        long long i = start;
        long long j = mid + 1;

        for (long long k = 0; k < size; ++k) {
            if (i > mid) {
                tmp[k] = arr[j];
                ++j;
            } else if (j > end) {
                tmp[k] = arr[i];
                ++i;
            } else if (arr[i] < arr[j]) {
                tmp[k] = arr[i];
                ++i;
            } else if (arr[i] > arr[j]) {
                tmp[k] = arr[j];
                ++j;
                inv += mid - i + 1;
            } else {
                tmp[k] = arr[i];
                ++i;
            }
        }

        for (int k = start; k <= end; ++k) {
            arr[k] = tmp[k - start];
        }

        return inv;
    }

    long long int inversionCountSort(long long arr[], long long start, long long end) {
        if (end - start < 1) {
            return 0;
        }

        long long gInv = 0;
        long long mid = start + ((end - start) / 2);
        gInv += inversionCountSort(arr, start, mid);
        gInv += inversionCountSort(arr, mid + 1, end);
        gInv += inversionCountMerge(arr, start, mid, end);
        return gInv;
    }

  public:
    // arr[]: Input Array
    // N : Size of the Array arr[]
    // Function to count inversions in the array.
    long long int inversionCount(long long arr[], long long N) {
        return inversionCountSort(arr, 0, N - 1);
    }
};

int main() {
    long long N1 = 5;
    long long A1[] = {2, 4, 1, 3, 5};
    long long N2 = 5;
    long long A2[] = {2, 3, 4, 5, 6};
    long long N3 = 3;
    long long A3[] = {10, 10, 10};
    long long N4 = 42;
    long long A4[] = {468, 335, 1,   170, 225, 479, 359, 463, 465, 206, 146, 282, 328, 462,
                      492, 496, 443, 328, 437, 392, 105, 403, 154, 293, 383, 422, 217, 219,
                      396, 448, 227, 272, 39,  370, 413, 168, 300, 36,  395, 204, 312, 323};

    Solution obj;
    cout << obj.inversionCount(A1, N1) << endl;
    cout << obj.inversionCount(A2, N2) << endl;
    cout << obj.inversionCount(A3, N3) << endl;
    cout << obj.inversionCount(A4, N4) << endl;
    return 0;
}