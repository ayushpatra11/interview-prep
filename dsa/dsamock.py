
class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        queue = deque() # the O cells on the border
        rows = len(board)
        cols = len(board[0])

        for row in range(rows):
            if board[row][0] == 'O':
                queue.append([row, 0])

            if board[row][cols-1] == 'O':
                queue.append([row, cols-1])

        for col in range(cols):
            if board[0][col] == 'O':
                queue.append([0, col])
            if board[rows-1][col] == 'O':
                queue.append([rows-1, col])

        #       X-1, Y
        # X, Y-1       X,Y       X, Y+1
        #        X+1, Y
        #

        rx = [0, -1, 0, 1]
        cx = [-1, 0, 1, 0]

        while len(queue) > 0:
            rowCoord = queue[0][0]
            colCoord = queue[0][1]
            queue.popleft()

            for i in range(4):
                newRow = rowCoord + rx[i]
                newCol = colCoord + cx[i]

                if newRow >= 0 and newRow < rows and newCol >=0 and newCol < cols and board[newRow][newCol] == 'O':
                    # B
                    board[newRow][newCol] = 'B'
                    queue.append([newRow, newCol])

        
        for row in range(rows):
            for col in range(cols):
                if board[row][col] == 'B':
                    board[row][col] = 'O'
                elif board[row][col] == 'O':
                    board[row][col] = 'X'



