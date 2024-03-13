/*
https://leetcode.com/problems/ones-and-zeroes

You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.


Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.

Example 2:

Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.


Constraints:

    1 <= strs.length <= 600
    1 <= strs[i].length <= 100
    strs[i] consists only of digits '0' and '1'.
    1 <= m, n <= 100
*/

class Solution {
public:
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> dpMap;

    int dp(vector<vector<int>>& zeroOnes, int z, int o, int m, int n, int i) {
        if(i >= zeroOnes.size()) {
            return 0;
        }

        if(dpMap.count(i) && dpMap[i].count(z) && dpMap[i][z].count(o)) {
            return dpMap[i][z][o];
        }


        if(z + zeroOnes[i][0] > m || o + zeroOnes[i][1] > n) {
            dpMap[i][z][o] = dp(zeroOnes, z, o, m, n, i+1);
        } else {
            dpMap[i][z][o] = max(1 + dp(zeroOnes, z + zeroOnes[i][0], o + zeroOnes[i][1], m, n, i+1),
                        dp(zeroOnes, z, o, m, n, i+1)
                    );
        }

        return dpMap[i][z][o];
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int s = strs.size();
        vector<vector<int>> zeroOnes(s, vector<int>(2, 0));
        for(int i=0; i < s; ++i) {
            int zeros = 0, ones = 0;
            for(char k: strs[i]) {
                if(k == '1') ones++;
                else zeros++;
            }
            zeroOnes[i][0] = zeros;
            zeroOnes[i][1] = ones;
        }

        return dp(zeroOnes, 0, 0, m, n, 0);
    }
};
