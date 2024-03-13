/*
https://leetcode.com/problems/find-median-from-data-stream/

The median is the middle value in an ordered integer list. If the size of the list is even, there is
no middle value, and the median is the mean of the two middle values.

    For example, for arr = [2,3,4], the median is 3.
    For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.

Implement the MedianFinder class:

    MedianFinder() initializes the MedianFinder object.
    void addNum(int num) adds the integer num from the data stream to the data structure.
    double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual
answer will be accepted.


Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0


Constraints:

    -105 <= num <= 105
    There will be at least one element in the data structure before calling findMedian.
    At most 5 * 104 calls will be made to addNum and findMedian.


Follow up:

    If all integer numbers from the stream are in the range [0, 100], how would you optimize your
solution? If 99% of all integer numbers from the stream are in the range [0, 100], how would you
optimize your solution?

*/

/*

*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class MedianFinder {
    multiset<int> s1, s2;
    int size;
    double median;

  public:
    MedianFinder() {
        s1 = multiset<int>();
        s2 = multiset<int>();
        size = 0;
        median = -1;
    }

    void addNum(int num) {
        if (size == 0) {
            s1.insert(num);
        } else if (size == 1) {
            auto iter_a = s1.end();
            iter_a--;
            int a = *iter_a;

            if (num >= a) {
                s2.insert(num);
            } else {
                s1.erase(iter_a);
                s1.insert(num);
                s2.insert(a);
            }
        } else if (size % 2 == 0) {
            auto iter_b = s2.begin();
            int b = *iter_b;

            if (num < b) {
                s1.insert(num);
            } else {
                s2.erase(iter_b);
                s2.insert(num);
                s1.insert(b);
            }
        } else {
            auto iter_a = s1.end();
            iter_a--;
            int a = *iter_a;

            if (num >= a) {
                s2.insert(num);
            } else {
                s1.erase(iter_a);
                s1.insert(num);
                s2.insert(a);
            }
        }

        median = -1;
        size++;
    }

    double findMedian() {
        if (median != -1) {
            return median;
        }

        if (size % 2 == 0) {
            int a = *s1.rbegin();
            int b = *s2.begin();
            median = (double)a + b;
            median = median / 2.0;
        } else {
            median = (double)*s1.rbegin();
        }

        return median;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {

    MedianFinder *mf_1 = new MedianFinder();
    mf_1->addNum(1);
    mf_1->addNum(2);
    cout << mf_1->findMedian() << endl;
    assert(1.5 == mf_1->findMedian());
    mf_1->addNum(3);
    cout << mf_1->findMedian() << endl;
    assert(2.0 == mf_1->findMedian());

    MedianFinder *mf_2 = new MedianFinder();
    mf_2->addNum(-1);
    cout << mf_2->findMedian() << endl;
    assert(-1.0 == mf_2->findMedian());
    mf_2->addNum(-2);
    cout << mf_2->findMedian() << endl;
    assert(-1.5 == mf_2->findMedian());
    mf_2->addNum(-3);
    cout << mf_2->findMedian() << endl;
    assert(-2.0 == mf_2->findMedian());
    mf_2->addNum(-4);
    cout << mf_2->findMedian() << endl;
    assert(-2.5 == mf_2->findMedian());
    mf_2->addNum(-5);
    cout << mf_2->findMedian() << endl;
    assert(-3.0 == mf_2->findMedian());

    return 0;
}