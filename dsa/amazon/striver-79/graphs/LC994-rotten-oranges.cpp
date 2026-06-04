/*
 * You are given an m x n grid where each cell can have one of three values:
 *
 * 0 representing an empty cell,
 * 1 representing a fresh orange, or
 * 2 representing a rotten orange.
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten
 * orange becomes rotten.
 *
 * Return the minimum number of minutes that must elapse until no cell has a
 * fresh orange. If this is impossible, return -1.
 *
 * Example 1:
 * Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 * Example 2:
 *
 * Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 * Output: -1
 * Explanation: The orange in the bottom left corner (row 2, column 0) is never
 * rotten, because rotting only happens 4-directionally.
 * Example 3:
 *
 * Input: grid = [[0,2]]
 * Output: 0
 * Explanation: Since there are already no fresh oranges at minute 0, the answer
 * is just 0.
 *
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 10
 * grid[i][j] is 0, 1, or 2.
 */

class Solution {
 public:
  int orangesRotting(vector<vector<int>> &grid) {
    // let us first store the positions of all the rotten oranges.
    queue<pair<pair<int, int>, int>>
        currentRottenOranges;  // this will store co and minute
    int m = grid.size(), n = grid[0].size(),
        freshOranges = 0;  // provided that this is a valid grid (guaranteed)
    int minutes = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 2)
          currentRottenOranges.push(
              {{i, j}, minutes});  // since this is the 0th minute
        if (grid[i][j] == 1) freshOranges++;
      }
    }

    // TODO: the row and col offsets.
    int rx[] = {-1, 0, 1, 0};
    int cx[] = {0, 1, 0, -1};  // down, right, top, left
    // now we perform BFS for those oranges that are already in the queue
    while (!currentRottenOranges.empty()) {
      pair<pair<int, int>, int> currentRottenOrange =
          currentRottenOranges.front();
      currentRottenOranges.pop();
      int orangeRow = currentRottenOrange.first.first;
      int orangeCol = currentRottenOrange.first.second;
      int time = currentRottenOrange.second;

      minutes = max(minutes, time);

      for (int i = 0; i < 4; i++) {
        // perform BFS
        int newRow = orangeRow + rx[i];
        int newCol = orangeCol + cx[i];
        if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
          if (grid[newRow][newCol] == 1) {
            freshOranges--;
            currentRottenOranges.push({{newRow, newCol}, time + 1});
            grid[newRow][newCol] = 2;
          }
        }
      }
    }
    return freshOranges == 0 ? minutes : -1;
  }
};
