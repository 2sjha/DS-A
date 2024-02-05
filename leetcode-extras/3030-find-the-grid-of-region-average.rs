/*
https://leetcode.com/problems/find-the-grid-of-region-average/

You are given a 0-indexed m x n grid image which represents a grayscale image, where image[i][j] represents a pixel with intensity in the range[0..255]. You are also given a non-negative integer threshold.

Two pixels image[a][b] and image[c][d] are said to be adjacent if |a - c| + |b - d| == 1.

A region is a 3 x 3 subgrid where the absolute difference in intensity between any two adjacent pixels is less than or equal to threshold.

All pixels in a region belong to that region, note that a pixel can belong to multiple regions.

You need to calculate a 0-indexed m x n grid result, where result[i][j] is the average intensity of the region to which image[i][j] belongs, rounded down to the nearest integer. If image[i][j] belongs to multiple regions, result[i][j] is the average of the rounded down average intensities of these regions, rounded down to the nearest integer. If image[i][j] does not belong to any region, result[i][j] is equal to image[i][j].

Return the grid result.


Example 1:

Input: image = [[5,6,7,10],[8,9,10,10],[11,12,13,10]], threshold = 3
Output: [[9,9,9,9],[9,9,9,9],[9,9,9,9]]
Explanation: There exist two regions in the image, which are shown as the shaded areas in the picture. The average intensity of the first region is 9, while the average intensity of the second region is 9.67 which is rounded down to 9. The average intensity of both of the regions is (9 + 9) / 2 = 9. As all the pixels belong to either region 1, region 2, or both of them, the intensity of every pixel in the result is 9.
Please note that the rounded-down values are used when calculating the average of multiple regions, hence the calculation is done using 9 as the average intensity of region 2, not 9.67.

Example 2:

Input: image = [[10,20,30],[15,25,35],[20,30,40],[25,35,45]], threshold = 12
Output: [[25,25,25],[27,27,27],[27,27,27],[30,30,30]]
Explanation: There exist two regions in the image, which are shown as the shaded areas in the picture. The average intensity of the first region is 25, while the average intensity of the second region is 30. The average intensity of both of the regions is (25 + 30) / 2 = 27.5 which is rounded down to 27. All the pixels in row 0 of the image belong to region 1, hence all the pixels in row 0 in the result are 25. Similarly, all the pixels in row 3 in the result are 30. The pixels in rows 1 and 2 of the image belong to region 1 and region 2, hence their assigned value is 27 in the result.

Example 3:

Input: image = [[5,6,7],[8,9,10],[11,12,13]], threshold = 1
Output: [[5,6,7],[8,9,10],[11,12,13]]
Explanation: There does not exist any region in image, hence result[i][j] == image[i][j] for all the pixels.


Constraints:

    3 <= n, m <= 500
    0 <= image[i][j] <= 255
    0 <= threshold <= 255
*/

struct Solution;
impl Solution {
    fn is_region_valid(
        image: &Vec<Vec<i32>>,
        threshold: i32,
        row: usize,
        col: usize,
    ) -> bool {
        let m = image.len();
        let n = image[0].len();

        if row + 2 >= m || col + 2 >= n {
            return false;
        }

        let directions: Vec<Vec<i32>> =
            vec![vec![0, 1], vec![0, -1], vec![1, 0], vec![-1, 0]];
        for i in row..row + 3 {
            for j in col..col + 3 {
                for dir in &directions {
                    let ni: usize = (i as i32 + dir[0]) as usize;
                    let nj: usize = (j as i32 + dir[1]) as usize;
                    if ni >= row && ni <= row + 2 && nj >= col && nj <= col + 2
                    {
                        if (image[ni][nj] - image[i][j]).abs() > threshold {
                            return false;
                        }
                    }
                }
            }
        }

        true
    }

    pub fn result_grid(image: Vec<Vec<i32>>, threshold: i32) -> Vec<Vec<i32>> {
        let m: usize = image.len();
        let n: usize = image[0].len();
        let mut res: Vec<Vec<i32>> = vec![vec![0; n]; m];
        let mut belongs: Vec<Vec<Vec<usize>>> = vec![vec![vec![]; n]; m];
        let mut region_avgs: Vec<i32> = Vec::new();
        let mut regs: usize = 0;
        let mut sum: i32;

        for row in 0..m {
            for col in 0..n {
                if Self::is_region_valid(&image, threshold, row, col) {
                    sum = 0;
                    for i in row..row + 3 {
                        for j in col..col + 3 {
                            belongs[i][j].push(regs);
                            sum += image[i][j];
                        }
                    }
                    region_avgs.push(sum / 9);
                    regs += 1;
                }
            }
        }

        for i in 0..m {
            for j in 0..n {
                if !belongs[i][j].is_empty() {
                    sum = 0;
                    for reg_idx in &belongs[i][j] {
                        sum += region_avgs[*reg_idx];
                    }
                    res[i][j] = sum / belongs[i][j].len() as i32;
                } else {
                    res[i][j] = image[i][j];
                }
            }
        }

        res
    }
}

fn main() {
    let image1: Vec<Vec<i32>> =
        vec![vec![5, 6, 7, 10], vec![8, 9, 10, 10], vec![11, 12, 13, 10]];
    let threshold1: i32 = 3;
    let res1: Vec<Vec<i32>> = Solution::result_grid(image1, threshold1);
    println!("{:?}", res1);

    let image2: Vec<Vec<i32>> = vec![
        vec![10, 20, 30],
        vec![15, 25, 35],
        vec![20, 30, 40],
        vec![25, 35, 45],
    ];
    let threshold2: i32 = 12;
    let res2: Vec<Vec<i32>> = Solution::result_grid(image2, threshold2);
    println!("{:?}", res2);

    let image3: Vec<Vec<i32>> =
        vec![vec![5, 6, 7], vec![8, 9, 10], vec![11, 12, 13]];
    let threshold3: i32 = 1;
    let res3: Vec<Vec<i32>> = Solution::result_grid(image3, threshold3);
    println!("{:?}", res3);
}
