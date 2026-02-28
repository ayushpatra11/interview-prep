"""
Feb 28

binary tree - level order traversal
"""

from collections import deque

class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

class Solution:
    def levelOrder(self, root):
        if not root:
            return []

        result = []
        q = deque([root])

        while q:
            level = []
            for _ in range(len(q)):
                node = q.popleft()
                level.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            result.append(level)

        return result

    def zigzagLevelOrder(self, root):
        if not root:
            return []

        result = []
        q = deque([root])
        left_to_right = True

        while q:
            level = []
            for _ in range(len(q)):
                node = q.popleft()
                level.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            result.append(level if left_to_right else level[::-1])
            left_to_right = not left_to_right

        return result
