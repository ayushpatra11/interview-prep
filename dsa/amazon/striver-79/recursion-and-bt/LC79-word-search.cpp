/*
 * Given an m x n grid of characters board and a string word, return true if
 * word exists in the grid.
 *
 * The word can be constructed from letters of sequentially adjacent cells,
 * where adjacent cells are horizontally or vertically neighboring. The same
 * letter cell may not be used more than once.
 *
 * Example 1:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
 * word = "ABCCED"
 * Output: true
 * Example 2:
 *
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
 * word = "SEE"
 * Output: true
 * Example 3:
 *
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
 * word = "ABCB"
 * Output: false
 *
 * Constraints:
 * m == board.length
 * n = board[i].length
 * 1 <= m, n <= 6
 * 1 <= word.length <= 15
 * board and word consists of only lowercase and uppercase English letters.
 *
 * Follow up: Could you use search pruning to make your solution faster with a
 * larger board?
 */

class Solution {
 public:
  bool dfs(int row, int col, int index, string &word,
           vector<vector<int>> &visited, vector<vector<char>> &board) {
    if (word[index] != board[row][col]) return false;
    if (index == word.length() - 1) return true;

    // you either visit it or you don't
    visited[row][col] = 1;

    int rx[] = {-1, 0, 1, 0};
    int cx[] = {0, 1, 0, -1};
    int m = board.size(), n = board[0].size();

    for (int i = 0; i < 4; i++) {
      int newRow = row + rx[i], newCol = col + cx[i];
      if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
          !visited[newRow][newCol]) {
        if (dfs(newRow, newCol, index + 1, word, visited, board)) return true;
      }
    }

    visited[row][col] = 0;
    return false;
  }
  bool exist(vector<vector<char>> &board, string word) {
    // we can use a recursive approach to go to all 4
    // directions from a grid and continue the search

    // we will perform a bfs from every cell to see if it exists
    // or not

    // first we push all the grids that have the same chars as the
    // first one in the word
    if (word.length() == 0) return true;
    int m = board.size(), n = board[0].size();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j] == word[0]) {
          vector<vector<int>> visited(m, vector<int>(n, 0));
          if (dfs(i, j, 0, word, visited, board)) return true;
        }
      }
    }

    return false;
  }
};
