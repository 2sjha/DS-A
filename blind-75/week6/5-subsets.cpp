/*

*/

#include "./../../printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    void get_subsets_length(vector<int> &nums, int end, vector<vector<int>> &powerset) {
        int n = powerset.size();

        vector<int> new_set;
        for (int i = 0; i < n; ++i) {
            new_set = powerset[i];
            new_set.push_back(nums[end]);
            powerset.push_back(new_set);
        }
    }

  public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> powerset;
        powerset.push_back({});

        for (int i = 0; i < nums.size(); ++i) {
            get_subsets_length(nums, i, powerset);
        }

        return powerset;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> res;

    vector<int> nums1 = {1, 2, 3};
    res = sol.subsets(nums1);
    print2Dmatrix(res);

    vector<int> nums2 = {0};
    res = sol.subsets(nums2);
    print2Dmatrix(res);

    return 0;
}