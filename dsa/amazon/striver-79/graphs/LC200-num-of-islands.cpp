/*
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and
 * '0's (water), return the number of islands.
 *
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically. You may assume all four edges of the grid are all
 * surrounded by water.
 *
 * Example 1:
 * Input: grid = [
 *   ["1","1","1","1","0"],
 *   ["1","1","0","1","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","0","0","0"]
 * ]
 * Output: 1
 * Example 2:
 *
 * Input: grid = [
 *   ["1","1","0","0","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","1","0","0"],
 *   ["0","0","0","1","1"]
 * ]
 * Output: 3
 *
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 300
 * grid[i][j] is '0' or '1'.
 */

class Solution {
 public:
  int numIslands(vector<vector<char>> &grid) {
    queue<pair<int, int>> q;
    int ans = 0, numrows = grid.size(), numcol = grid[0].size();
    int delr[] = {-1, 0, 1, 0};
    int delc[] = {0, -1, 0, 1};
    for (int i = 0; i < numrows; i++) {
      for (int j = 0; j < numcol; j++) {
        if (grid[i][j] == '1') {
          q.push({i, j});
          ans++;
          grid[i][j] = '0';
          while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for (int k = 0; k < 4; k++) {
              int nr = r + delr[k];
              int nc = c + delc[k];

              // Check bounds and if it's land ('1')
              if (nr >= 0 && nr < numrows && nc >= 0 && nc < numcol &&
                  grid[nr][nc] == '1') {
                q.push({nr, nc});
                grid[nr][nc] = '0';  // Mark as visited
              }
            }
          }
        }
      }
    }
    return ans;
  }
};
