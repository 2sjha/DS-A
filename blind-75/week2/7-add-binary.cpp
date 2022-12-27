/*
https://leetcode.com/problems/add-binary/

Given two binary strings a and b, return their sum as a binary string.


Example 1:

Input: a = "11", b = "1"
Output: "100"

Example 2:

Input: a = "1010", b = "1011"
Output: "10101"


Constraints:

    1 <= a.length, b.length <= 104
    a and b consist only of '0' or '1' characters.
    Each string does not contain leading zeros except for the zero itself.
*/

#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Solution {
  private:
    string prefix0(string s, int final_size) {
        while (s.size() != final_size) {
            s = '0' + s;
        }
        return s;
    }

    pair<char, bool> addBinaryDigits(bool digit_1, bool digit_2, bool carry) {
        pair<char, bool> res;
        if (!carry) {
            if (digit_1 && digit_2) {
                res.first = '0';
                res.second = true;
            } else if (!digit_1 && !digit_2) {
                res.first = '0';
                res.second = false;
            } else {
                res.first = '1';
                res.second = false;
            }
        } else {
            if (digit_1 && digit_2) {
                res.first = '1';
                res.second = true;
            } else if (!digit_1 && !digit_2) {
                res.first = '1';
                res.second = false;
            } else {
                res.first = '0';
                res.second = true;
            }
        }
        return res;
    }

  public:
    string addBinary(string a, string b) {
        int size_a = a.length();
        int size_b = b.length();
        int size;

        if (size_a < size_b) {
            a = prefix0(a, size_b);
            size = size_b;
        } else if (size_b < size_a) {
            b = prefix0(b, size_a);
            size = size_a;
        }

        cout << a << " " << b << endl;
        int i = size - 1;
        bool carry = false;
        string res;

        while (i >= 0) {
            pair<char, bool> curr_res = addBinaryDigits(a[i] == '1', b[i] == '1', carry);
            res = curr_res.first + res;
            carry = curr_res.second;
            i--;
        }

        if (carry) {
            res = '1' + res;
        }
        return res;
    }
};

int main() {
    string a = "1";
    string b = "111";
    Solution s;
    string res = s.addBinary(a, b);
    cout << res << endl;
    return 0;
}