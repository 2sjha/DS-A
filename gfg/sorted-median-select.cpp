#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int sortedMedianSelect(vector<int> &A, int a_begin, int a_end, vector<int> &B, int b_begin,
                       int b_end) {
    int n = a_end - a_begin + 1;
    int k = n / 2;
    if (n == 1) {
        return min(A[a_begin], B[b_begin]);
    }
    if (A[k] < B[k]) {
        return sortedMedianSelect(A, k, a_end, B, b_begin, k);
    } else {
        return sortedMedianSelect(A, a_begin, k, B, k, b_end);
    }
}

int main() {
    vector<int> A = {1, 3, 5, 7};
    vector<int> B = {2, 4, 6, 8};

    int res = sortedMedianSelect(A, 0, A.size() - 1, B, 0, B.size() - 1);
    cout << res;
    return 0;
}