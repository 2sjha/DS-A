/*
https://leetcode.com/problems/snapshot-array/description/

Implement a SnapshotArray that supports the following interface:

    SnapshotArray(int length) initializes an array-like data structure with the given length.
Initially, each element equals 0. void set(index, val) sets the element at the given index to be
equal to val. int snap() takes a snapshot of the array and returns the snap_id: the total number of
times we called snap() minus 1. int get(index, snap_id) returns the value at the given index, at the
time we took the snapshot with the given snap_id


Example 1:

Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
Explanation:
SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
snapshotArr.set(0,5);  // Set array[0] = 5
snapshotArr.snap();  // Take a snapshot, return snap_id = 0
snapshotArr.set(0,6);
snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5


Constraints:

    1 <= length <= 5 * 10^4
    0 <= index < length
    0 <= val <= 10^9
    0 <= snap_id < (the total number of times we call snap())
    At most 5 * 10^4 calls will be made to set, snap, and get.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class SnapshotArray {
    vector<map<int, int>> arr;
    int snap_count;

  public:
    SnapshotArray(int length) {
        arr = vector<map<int, int>>();
        snap_count = 0;

        map<int, int> mp;
        mp[0] = 0;
        for (int i = 0; i < length; ++i) {
            arr.push_back(mp);
        }
    }

    void set(int index, int val) { arr[index][snap_count] = val; }

    int snap() {
        snap_count++;
        return snap_count - 1;
    }

    int get(int index, int snap_id) {
        int snap = snap_id;
        if (arr[index].find(snap_id) == arr[index].end()) {
            snap = (--arr[index].lower_bound(snap_id))->first;
        }

        return arr[index][snap];
    }
};

int main() {
    SnapshotArray *sa = new SnapshotArray(3);
    sa->set(0, 5);
    cout << sa->snap() << endl;
    sa->set(0, 6);
    cout << sa->get(0, 0) << endl;
    assert(sa->get(0, 0) == 5);

    SnapshotArray *sa1 = new SnapshotArray(4);
    cout << sa1->snap() << endl;
    cout << sa1->snap() << endl;
    cout << sa1->get(3, 1) << endl;
    assert(sa1->get(3, 1) == 0);
    sa1->set(2, 4);
    cout << sa1->snap() << endl;
    sa1->set(1, 4);

    SnapshotArray *sa2 = new SnapshotArray(1);
    sa2->set(0, 15);
    cout << sa2->snap() << endl;
    cout << sa2->snap() << endl;
    cout << sa2->snap() << endl;
    cout << sa2->get(0, 2) << endl;
    assert(sa2->get(0, 2) == 15);
    cout << sa2->snap() << endl;
    cout << sa2->snap() << endl;
    cout << sa2->get(0, 0) << endl;
    assert(sa2->get(0, 2) == 15);

    SnapshotArray *sa3 = new SnapshotArray(1);
    cout << sa3->snap() << endl;
    cout << sa3->snap() << endl;
    sa3->set(0, 4);
    cout << sa3->snap() << endl;
    cout << sa3->get(0, 1) << endl;
    assert(sa3->get(0, 1) == 0);
    sa3->set(0, 12);
    cout << sa3->get(0, 1) << endl;
    assert(sa3->get(0, 1) == 0);
    cout << sa3->snap() << endl;
    cout << sa3->get(0, 3) << endl;
    assert(sa3->get(0, 3) == 12);

    SnapshotArray *sa4 = new SnapshotArray(2);
    cout << sa4->snap() << endl;
    cout << sa4->get(1, 0) << endl;
    cout << sa4->get(0, 0) << endl;
    sa4->set(1, 8);
    cout << sa4->get(1, 0) << endl;
    sa4->set(0, 20);
    cout << sa4->get(0, 0) << endl;
    sa4->set(0, 7);

    SnapshotArray *sa5 = new SnapshotArray(1);
    cout << sa5->snap() << endl;
    cout << sa5->snap() << endl;
    sa5->set(0, 4);
    cout << sa5->snap() << endl;
    cout << sa5->get(0, 1) << endl;
    sa5->set(0, 12);
    cout << sa5->get(0, 1) << endl;
    cout << sa5->snap() << endl;
    cout << sa5->get(0, 3) << endl;

    SnapshotArray *sa6 = new SnapshotArray(4);
    cout << sa6->snap() << endl;
    sa6->set(0, 15);
    sa6->set(3, 0);
    sa6->set(3, 18);
    cout << sa6->snap() << endl;
    sa6->set(0, 2);
    sa6->set(1, 1);
    cout << sa6->snap() << endl;
    cout << sa6->get(1, 2) << endl;
    cout << sa6->snap() << endl;
    cout << sa6->snap() << endl;
    cout << sa6->get(3, 2) << endl;
    cout << sa6->snap() << endl;
    cout << sa6->get(0, 3) << endl;

    return 0;
}