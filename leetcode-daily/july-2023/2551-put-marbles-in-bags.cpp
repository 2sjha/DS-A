/*
You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight of
the ith marble. You are also given the integer k.

Divide the marbles into the k bags according to the following rules:

    No bag is empty.
    If the ith marble and jth marble are in a bag, then all marbles with an index between the ith
and jth indices should also be in that same bag. If a bag consists of all the marbles with an index
from i to j inclusively, then the cost of the bag is weights[i] + weights[j].

The score after distributing the marbles is the sum of the costs of all the k bags.

Return the difference between the maximum and minimum scores among marble distributions.


Example 1:

Input: weights = [1,3,5,1], k = 2
Output: 4
Explanation:
The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
Thus, we return their difference 10 - 6 = 4.

Example 2:

Input: weights = [1, 3], k = 2
Output: 0
Explanation: The only distribution possible is [1],[3].
Since both the maximal and minimal score are the same, we return 0.


Constraints:

    1 <= k <= weights.length <= 10^5
    1 <= weights[i] <= 10^9
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Idea is that if we're separating marbels into buckets where only the first and last marble's
// weights matter, then we can just take all n-1 adjacent sums where these numbers would have been
// end and start of some buckets. The first and last marble's weight is added in any distribution.
// So out of those n-1 adjacent sums, we take k-1 coz we're dividing into k buckets.
// To get the max and minm we take k-1 from left and from the right.
class Solution {
  private:
    long long getMaxScore(vector<int> &weights, vector<int> &adjWeights, int k) {
        int n = weights.size();
        long long score = weights[0] + weights[n - 1];
        for (int i = 0; i < k - 1; ++i) {
            score += adjWeights[n - 2 - i];
        }

        return score;
    }

    long long getMinScore(vector<int> &weights, vector<int> &adjWeights, int k) {
        int n = weights.size();
        long long score = weights[0] + weights[n - 1];
        for (int i = 0; i < k - 1; ++i) {
            score += adjWeights[i];
        }

        return score;
    }

  public:
    long long putMarbles(vector<int> &weights, int k) {
        int n = weights.size();
        vector<int> adjWeights(n - 1);

        for (int i = 1; i < n; ++i) {
            adjWeights[i - 1] = weights[i - 1] + weights[i];
        }
        sort(adjWeights.begin(), adjWeights.end());

        long long score = getMaxScore(weights, adjWeights, k);
        score -= getMinScore(weights, adjWeights, k);

        return score;
    }
};

int main() {
    Solution sol;
    long long res;

    vector<int> weights1 = {1, 3, 5, 1};
    int k1 = 2;
    res = sol.putMarbles(weights1, k1);
    cout << res << endl;
    assert(res == 4);

    vector<int> weights2 = {1, 3};
    int k2 = 2;
    res = sol.putMarbles(weights2, k2);
    cout << res << endl;
    assert(res == 0);

    return 0;
}