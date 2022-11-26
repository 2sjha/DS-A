/*
https://leetcode.com/problems/flood-fill

An image is represented by an m x n integer grid image where image[i][j] represents the pixel value
of the image.

You are also given three integers sr, sc, and color. You should perform a flood fill on the image
starting from the pixel image[sr][sc].

To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to
the starting pixel of the same color as the starting pixel, plus any pixels connected
4-directionally to those pixels (also with the same color), and so on. Replace the color of all of
the aforementioned pixels with color.

Return the modified image after performing the flood fill.



Example 1:

Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all
pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are
colored with the new color. Note the bottom corner is not colored 2, because it is not
4-directionally connected to the starting pixel.

Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
Output: [[0,0,0],[0,0,0]]
Explanation: The starting pixel is already colored 0, so no changes are made to the image.



Constraints:

    m == image.length
    n == image[i].length
    1 <= m, n <= 50
    0 <= image[i][j], color < 216
    0 <= sr < m
    0 <= sc < n
*/

#include "bits/stdc++.h"
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int rows = image.size();
        int columns = image[0].size();
        int original_color = image[sr][sc];
        vector<vector<bool>> visited;

        for (int i = 0; i < rows; i++) {
            vector<bool> row;
            visited.push_back(row);
            for (int j = 0; j < columns; j++) {
                visited[i].push_back(false);
            }
        }

        floodFill(image, sr, sc, original_color, color, visited);
        return image;
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int original_color, int color, vector<vector<bool>>& visited) {
        int rows = image.size();
        int columns = image[0].size();
        if (sc < 0 || sr < 0 || sr >= rows || sc >= columns || image[sr][sc] != original_color ||
            visited[sr][sc] == true) {
            return image;
        }

        image[sr][sc] = color;
        visited[sr][sc] = true;
        // display_image(image);
        // cout << "sr=" << sr << ", sc=" << sc << ", original_color= " << original_color << ", color= " << color << endl;

        floodFill(image, sr - 1, sc, original_color, color, visited);
        floodFill(image, sr + 1, sc, original_color, color, visited);
        floodFill(image, sr, sc - 1, original_color, color, visited);
        floodFill(image, sr, sc + 1, original_color, color, visited);

        return image;
    }

  private:
    void display_image(vector<vector<int>>& image) {
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                cout << image[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector<vector<int>> image;
    int m, n, sr, sc, color;
    cout << "Enter no. of rows" << endl;
    cin >> m;
    cout << "Enter no. of columns" << endl;
    cin >> n;

    cout << "Enter array" << endl;
    for (int i = 0; i < m; i++) {
        vector<int> row;
        image.push_back(row);
        for (int j = 0; j < n; j++) {
            int temp;
            cin >> temp;
            image[i].push_back(temp);
        }
    }

    cout << "Enter sr, sc, color" << endl;
    cin >> sr >> sc >> color;
    Solution sol;
    sol.floodFill(image, sr, sc, color);
    sol.display_image(image);
    return 0;
}