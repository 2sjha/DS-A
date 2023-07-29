/*
https://leetcode.com/problems/predict-the-winner/

You are given an integer array nums. Two players are playing a game with this array: player 1 and
player 2.

Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a
score of 0. At each turn, the player takes one of the numbers from either end of the array (i.e.,
nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1. The player adds the
chosen number to their score. The game ends when there are no more elements in the array.

Return true if Player 1 can win the game. If the scores of both players are equal, then player 1 is
still the winner, and you should also return true. You may assume that both players are playing
optimally.


Example 1:

Input: nums = [1,5,2]
Output: false
Explanation: Initially, player 1 can choose between 1 and 2.
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then
player 1 will be left with 1 (or 2). So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
Hence, player 1 will never be the winner and you need to return false.

Example 2:

Input: nums = [1,5,233,7]
Output: true
Explanation: Player 1 first chooses 1. Then player 2 has to choose between 5 and 7. No matter which
number player 2 choose, player 1 can choose 233. Finally, player 1 has more score (234) than player
2 (12), so you need to return True representing player1 can win.


Constraints:

    1 <= nums.length <= 20
    0 <= nums[i] <= 10^7
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Recursive Definition
// p1Win(p1Score, p2Score, start, end, turn)
//
//  if(no more elements) {
//      true if p1Score >= p2Score
//      false otherwise
//  }

//  if(p1's turn) {
//      p1Win(p1Score + nums[start], p2Score, p2) || p1Win(p1Score + nums[end], p2Score, p2)
//  }

//  if(p2's turn) {
//      p1Win(p1Score, p2Score + nums[start], p1) && p1Win(p1Score, p2Score + nums[end], p1)
//  }
// }

class Solution {
    bool playGame(vector<int> &nums, int start, int end, long long p1Score, long long p2Score,
                  bool p1Turn) {

        if (start > end) {
            return (p1Score >= p2Score);
        }

        bool res = false;
        if (p1Turn) {
            p1Score += nums[start];
            res = playGame(nums, start + 1, end, p1Score, p2Score, false);
            if (res)
                return res;

            p1Score -= nums[start];
            p1Score += nums[end];
            res = playGame(nums, start, end - 1, p1Score, p2Score, false);
        } else {
            p2Score += nums[start];
            res = playGame(nums, start + 1, end, p1Score, p2Score, true);
            if (res) {
                p2Score -= nums[start];
                p2Score += nums[end];
                res = playGame(nums, start, end - 1, p1Score, p2Score, true);
            }
        }

        return res;
    }

  public:
    bool PredictTheWinner(vector<int> &nums) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;
        long long p1Score = 0ll;
        long long p2Score = 0ll;

        return playGame(nums, start, end, p1Score, p2Score, true);
    }
};

int main() {
    Solution sol;
    int res;

    vector<int> nums1 = {1, 5, 2};
    res = sol.PredictTheWinner(nums1);
    cout << res << endl;
    assert(res == 0);

    vector<int> nums2 = {1, 5, 233, 7};
    res = sol.PredictTheWinner(nums2);
    cout << res << endl;
    assert(res == 1);

    vector<int> nums3 = {1, 3, 1};
    res = sol.PredictTheWinner(nums3);
    cout << res << endl;
    assert(res == 0);

    return 0;
}