/*
https://leetcode.com/problems/detonate-the-maximum-bombs/

You are given a list of bombs. The range of a bomb is defined as the area where its effect can be
felt. This area is in the shape of a circle with the center as the location of the bomb.

The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi
and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes
the radius of its range.

You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that
lie in its range. These bombs will further detonate the bombs that lie in their ranges.

Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed
to detonate only one bomb.


Example 1:

Input: bombs = [[2,1,3],[6,1,4]]
Output: 2
Explanation:
The above figure shows the positions and ranges of the 2 bombs.
If we detonate the left bomb, the right bomb will not be affected.
But if we detonate the right bomb, both bombs will be detonated.
So the maximum bombs that can be detonated is max(1, 2) = 2.

Example 2:

Input: bombs = [[1,1,5],[10,10,5]]
Output: 1
Explanation:
Detonating either bomb will not detonate the other bomb, so the maximum number of bombs that can be
detonated is 1.

Example 3:

Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
Output: 5
Explanation:
The best bomb to detonate is bomb 0 because:
- Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb 0.
- Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
- Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.
Thus all 5 bombs are detonated.


Constraints:

    1 <= bombs.length <= 100
    bombs[i].length == 3
    1 <= xi, yi, ri <= 105
*/

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    vector<vector<int>> edge_list;

  private:
    void can_detonate(int i, vector<int> &bomb_i, int j, vector<int> &bomb_j) {
        float dist = sqrt(pow(abs(bomb_i[0] - bomb_j[0]), 2) + pow(abs(bomb_i[1] - bomb_j[1]), 2));
        if (dist <= bomb_i[2]) {
            edge_list[i].push_back(j);
        }
        if (dist <= bomb_j[2]) {
            edge_list[j].push_back(i);
        }
    }

    void build_graph(vector<vector<int>> &bombs) {
        edge_list = vector<vector<int>>();
        for (int i = 0; i < bombs.size(); ++i) {
            edge_list.push_back(vector<int>());
        }

        for (int i = 0; i < bombs.size(); ++i) {
            for (int j = i + 1; j < bombs.size(); ++j) {
                can_detonate(i, bombs[i], j, bombs[j]);
            }
        }
    }

    int bfs(int bomb_start) {
        vector<bool> visited(edge_list.size(), false);
        int det_count = 0;
        queue<int> bfs_q;
        bfs_q.push(bomb_start);

        while (!bfs_q.empty()) {
            int curr = bfs_q.front();
            bfs_q.pop();

            if (visited[curr]) {
                continue;
            }

            visited[curr] = true;
            det_count++;

            for (int reachable_bomb : edge_list[curr]) {
                if (!visited[reachable_bomb]) {
                    bfs_q.push(reachable_bomb);
                }
            }
        }

        return det_count;
    }

  public:
    int maximumDetonation(vector<vector<int>> &bombs) {
        build_graph(bombs);

        int max_det = -1;
        for (int i = 0; i < bombs.size(); ++i) {
            int det = bfs(i);
            max_det = max(det, max_det);
        }
        return max_det;
    }
};

int main() {
    Solution sol;
    int res;

    vector<vector<int>> bombs1 = {{2, 1, 3}, {6, 1, 4}};
    res = sol.maximumDetonation(bombs1);
    cout << res << endl;
    assert(res == 2);

    vector<vector<int>> bombs2 = {{1, 1, 5}, {10, 10, 5}};
    res = sol.maximumDetonation(bombs2);
    cout << res << endl;
    assert(res == 1);

    vector<vector<int>> bombs3 = {{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};
    res = sol.maximumDetonation(bombs3);
    cout << res << endl;
    assert(res == 5);

    vector<vector<int>> bombs4 = {{56, 80, 2},  {55, 9, 10}, {32, 75, 2},  {87, 89, 1},
                                  {61, 94, 3},  {43, 82, 9}, {17, 100, 6}, {50, 6, 7},
                                  {9, 66, 7},   {98, 3, 6},  {67, 50, 2},  {79, 39, 5},
                                  {92, 60, 10}, {49, 9, 9},  {42, 32, 10}};
    res = sol.maximumDetonation(bombs4);
    cout << res << endl;
    assert(res == 3);

    vector<vector<int>> bombs5 = {
        {855, 82, 158},  {17, 719, 430},  {90, 756, 164}, {376, 17, 340},  {691, 636, 152},
        {565, 776, 5},   {464, 154, 271}, {53, 361, 162}, {278, 609, 82},  {202, 927, 219},
        {542, 865, 377}, {330, 402, 270}, {720, 199, 10}, {986, 697, 443}, {471, 296, 69},
        {393, 81, 404},  {127, 405, 177}};
    res = sol.maximumDetonation(bombs5);
    cout << res << endl;
    assert(res == 9);

    return 0;
}