#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        vector<vector<int>> res;
        int m = mat.size();
        int n = mat[0].size();

        for (int i = 0; i < m; ++i) {
            vector<int> empty(n, INT_MAX - 10000);
            res.push_back(empty);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    res[i][j] = 0;
                } else if ((i - 1 >= 0 and mat[i - 1][j] == 0) or
                           (i + 1 <= m - 1 and mat[i + 1][j] == 0) or
                           (j - 1 >= 0 and mat[i][j - 1] == 0) or
                           (j + 1 <= n - 1 and mat[i][j + 1] == 0)) {
                    res[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int l = INT_MAX - 10000, u = INT_MAX - 10000;

                if (i - 1 >= 0) {
                    u = res[i - 1][j];
                }
                if (j - 1 >= 0) {
                    l = res[i][j - 1];
                }

                res[i][j] = min(res[i][j], 1 + min(l, u));
            }
        }

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int r = INT_MAX - 10000, d = INT_MAX - 10000;

                if (i + 1 <= m - 1) {
                    d = res[i + 1][j];
                }

                if (j + 1 <= n - 1) {
                    r = res[i][j + 1];
                }

                res[i][j] = min(res[i][j], 1 + min(r, d));
            }
        }

        return res;
    }
};

int main() {
    // vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    // vector<vector<int>> mat = {{0},{0},{0},{0},{0}};

    Solution sol;
    auto res = sol.updateMatrix(mat);

    for (auto r : mat) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (auto r : res) {
        for (auto val : r) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}