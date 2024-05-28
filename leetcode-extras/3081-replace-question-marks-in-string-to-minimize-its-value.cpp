/*
https://leetcode.com/problems/replace-question-marks-in-string-to-minimize-its-value

You are given a string `s`. `s[i]` is either a lowercase English letter or `'?'`.

For a string `t` having length `m` containing **only** lowercase English letters, we define the function `cost(i)` for
an index `i` as the number of characters **equal** to `t[i]` that appeared before it, i.e. in the range `[0, i - 1]`.

The **value** of `t` is the **sum** of `cost(i)` for all indices `i`.

For example, for the string `t = "aab"`:

* `cost(0) = 0`
* `cost(1) = 1`
* `cost(2) = 0`
* Hence, the value of `"aab"` is `0 + 1 + 0 = 1`.

Your task is to **replace all** occurrences of `'?'` in `s` with any lowercase English letter so that the **value** of
`s` is **minimized**.

Return *a string denoting the modified string with replaced occurrences of *`'?'`*. If there are multiple strings
resulting in the **minimum value**, return the lexicographically smallest one.*


**Example 1:**

**Input: ** s = "???"

**Output: ** "abc"

**Explanation: ** In this example, we can replace the occurrences of `'?'` to make `s` equal to `"abc"`.

For `"abc"`, `cost(0) = 0`, `cost(1) = 0`, and `cost(2) = 0`.

The value of `"abc"` is `0`.

Some other modifications of `s` that have a value of `0` are `"cba"`, `"abz"`, and, `"hey"`.

Among all of them, we choose the lexicographically smallest.

**Example 2:**

**Input: ** s = "a?a?"

**Output: ** "abac"

**Explanation: ** In this example, the occurrences of `'?'` can be replaced to make `s` equal to `"abac"`.

For `"abac"`, `cost(0) = 0`, `cost(1) = 0`, `cost(2) = 1`, and `cost(3) = 0`.

The value of `"abac"` is `1`.


**Constraints:**

* `1 <= s.length <= 10⁵`
* `s[i]` is either a lowercase English letter or `'?'`.
*/

#include "./../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

// Looked at Solution https://leetcode.com/problems/replace-question-marks-in-string-to-minimize-its-value/solutions/4885329/solution-through-observation-and-pictorial-representation/

class Solution {
public:
    string minimizeStringValue(string s) {
        int n = s.length();
        vector<int> freq(26, 0);
        vector<pair<int, char>> sorted_freq(26, {0, 'a'});
        for(int i=0; i < n; ++i) {
            if(s[i] != '?') {
                freq[s[i] - 'a']++;
            }
        }

        for(int i = 0; i < 26; ++i) {
            sorted_freq[i] = {freq[i], 'a' + i};
        }
        sort(sorted_freq.begin(), sorted_freq.end());

		// Use the least frequently used chars overall
        vector<char> filled_chars;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '?') {
				// Push the filled char in a different array
                filled_chars.push_back(sorted_freq[0].second);
                sorted_freq[0].first++;
                sort(sorted_freq.begin(), sorted_freq.end());
            }
        }

		// Use the filled char array to create the lexicographically smallest string
        sort(filled_chars.begin(), filled_chars.end());
        for(int i = 0, j = 0; i < n; ++i) {
            if(s[i] == '?') {
                s[i] = filled_chars[j++];
            }
        }

        return s;
    }
};

int main() {
	Solution sol;

	string s_1 = "???";
	string expected_1 = "abc";
	string output_1 = sol.minimizeStringValue(s_1);
	cout << output_1 << endl;
	assert(output_1 == expected_1);

	string s_2 = "a?a?";
	string expected_2 = "abac";
	string output_2 = sol.minimizeStringValue(s_2);
	cout << output_2 << endl;
	assert(output_2 == expected_2);

	return 0;
}