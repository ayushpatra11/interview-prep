
# graph problems - bfs/dfs

from collections import deque

class Solution:
    def countComponents(self, n, edges):
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        visited = set()
        count = 0

        for i in range(n):
            if i not in visited:
                count += 1
                q = deque([i])
                visited.add(i)
                while q:
                    node = q.popleft()
                    for nei in adj[node]:
                        if nei not in visited:
                            visited.add(nei)
                            q.append(nei)

        return count

    # union-find for cycle detection
    def hasCycleUF(self, n, edges):
        parent = list(range(n))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        for u, v in edges:
            pu, pv = find(u), find(v)
            if pu == pv:
                return True
            parent[pu] = pv

        return False

    def numIslands(self, grid):
        if not grid:
            return 0
        rows, cols = len(grid), len(grid[0])
        count = 0
        dirs = [(0,1),(0,-1),(1,0),(-1,0)]

        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == '1':
                    count += 1
                    q = deque([(i, j)])
                    grid[i][j] = '0'
                    while q:
                        r, c = q.popleft()
                        for dr, dc in dirs:
                            nr, nc = r + dr, c + dc
                            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '1':
                                grid[nr][nc] = '0'
                                q.append((nr, nc))

        return count
