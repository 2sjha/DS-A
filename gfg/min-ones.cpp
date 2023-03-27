#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    int minOnes(int n) {
        vector<int> minO(n + 1, 100000);
        minO[0] = 0;
        minO[1] = 1;
        for (int k = 2; k <= n; ++k) {
            minO[k] = minO[1] + minO[k - 1];
            for (int i = 2; i < (k / 2 + 1); ++i) {
                int minFromAdd = minO[i] + minO[k - i];
                int minFromMult = 100000;
                if (k % i == 0) {
                    minFromAdd = minO[i] + minO[k / i];
                }
                minO[k] = min(minO[k], min(minFromAdd, minFromMult));
            }
        }

        return minO[n];
    }
};

int main() {

    Solution sol;
    auto res = sol.minOnes(14);
    cout << res << endl;
    return 0;
}