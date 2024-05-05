/*
https://leetcode.com/problems/freedom-trail

In the video game Fallout 4, the quest **"Road to Freedom"** requires players to reach a metal dial
called the
**"Freedom Trail Ring"** and use the dial to spell a specific keyword to open the door.

Given a string `ring` that represents the code engraved on the outer ring and another string `key`
that represents the keyword that needs to be spelled, return *the minimum number of steps to spell
all the characters in the keyword*.

Initially, the first character of the ring is aligned at the `"12:00"` direction. You should spell
all the characters in `key` one by one by rotating `ring` clockwise or anticlockwise to make each
character of the string key aligned at the
`"12:00"` direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character `key[i]`:

1. You can rotate the ring clockwise or anticlockwise by one place, which counts as **one step**.
The final purpose of the rotation is to align one of `ring`'s characters at the `"12:00"` direction,
where this character must equal `key[i]`.
2. If the character `key[i]` has been aligned at the `"12:00"` direction, press the center button to
spell, which also counts as **one step**. After the pressing, you could begin to spell the next
character in the key (next stage). Otherwise, you have finished all the spelling.


**Example 1:**

**Input:** ring = "godding", key = "gd"
**Output:** 4
**Explanation:**
For the first key character 'g', since it is already in place, we just need 1 step to spell this
character. For the second key character 'd', we need to rotate the ring "godding" anticlockwise by
two steps to make it become "ddi nggo". Also, we need 1 more step for spelling. So the final output
is 4.

**Example 2:**

**Input:** ring = "godding", key = "godding"
**Output:** 13


**Constraints:**

* `1 <= ring.length, key.length <= 100`
* `ring` and `key` consist of only lower case English letters.
* It is guaranteed that `key` could always be spelled by rotating `ring`.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
  private:
    pair<int, int> clockWiseSteps(string ring, int ringIdxOnTop, char desiredCharOnTop) {
        int first = -1, second = -1;
        for (int i = ringIdxOnTop; i < ring.length(); ++i) {
            if (ring[i] == desiredCharOnTop) {
                first = i - ringIdxOnTop;
                second = i;
                return {first, second};
            }
        }

        for (int i = 0; i < ringIdxOnTop; ++i) {
            if (ring[i] == desiredCharOnTop) {
                first = ring.length() - ringIdxOnTop + i;
                second = i;
                return {first, second};
            }
        }

        return {first, second};
    }

    pair<int, int> antiClockWiseSteps(string ring, int ringIdxOnTop, char desiredCharOnTop) {
        int first = -1, second = -1;
        for (int i = ringIdxOnTop; i >= 0; --i) {
            if (ring[i] == desiredCharOnTop) {
                first = ringIdxOnTop - i;
                second = i;
                return {first, second};
            }
        }

        for (int i = ring.length() - 1; i > ringIdxOnTop; --i) {
            if (ring[i] == desiredCharOnTop) {
                first = ring.length() - i + ringIdxOnTop;
                second = i;
                return {first, second};
            }
        }

        return {first, second};
    }

    int rotateSteps(vector<vector<int>> &dp, string ring, string key, int keyIdx,
                    int ringIdxOnTop) {
        if (keyIdx == key.length())
            return 0;
        if (dp[keyIdx][ringIdxOnTop] != 0)
            return dp[keyIdx][ringIdxOnTop];

        if (key[keyIdx] == ring[ringIdxOnTop]) {
            dp[keyIdx][ringIdxOnTop] = 1 + rotateSteps(dp, ring, key, keyIdx + 1, ringIdxOnTop);
        } else {
            pair<int, int> clockwise = clockWiseSteps(ring, ringIdxOnTop, key[keyIdx]);
            pair<int, int> antiClockwise = antiClockWiseSteps(ring, ringIdxOnTop, key[keyIdx]);

            dp[keyIdx][ringIdxOnTop] =
                min(clockwise.first + 1 + rotateSteps(dp, ring, key, keyIdx + 1, clockwise.second),
                    antiClockwise.first + 1 +
                        rotateSteps(dp, ring, key, keyIdx + 1, antiClockwise.second));
        }
        return dp[keyIdx][ringIdxOnTop];
    }

  public:
    int findRotateSteps(string ring, string key) {
        vector<vector<int>> dp = vector<vector<int>>(key.length(), vector<int>(ring.length(), 0));
        return rotateSteps(dp, ring, key, 0, 0);
    }
};

int main() {
    Solution sol;

    string ring_1 = "godding";
    string key_1 = "gd";
    int expected_1 = 4;
    int output_1 = sol.findRotateSteps(ring_1, key_1);
    cout << output_1 << endl;
    assert(output_1 == expected_1);

    string ring_2 = "godding";
    string key_2 = "godding";
    int expected_2 = 13;
    int output_2 = sol.findRotateSteps(ring_2, key_2);
    cout << output_2 << endl;
    assert(output_2 == expected_2);

    string ring_3 = "abcde";
    string key_3 = "ade";
    int expected_3 = 6;
    int output_3 = sol.findRotateSteps(ring_3, key_3);
    cout << output_3 << endl;
    assert(output_3 == expected_3);

    return 0;
}