"""
2 Binary trees - tell if they are the same tree or not. 

Roots are given, the nodes will have - Value, left and right
"""

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class CompareTrees:
    def compareTrees(self, p, q):
        if p == None and q == None:
            return True
        elif p == None or q == None:
            return False
        
        return (p.value == q.value) and self.compareTrees(p.left, q.left) and self.compareTrees(p.right, q.right)
    
    def mirrorCheck(self, p, q):
        """
                1               1  

            2       3       3       2

        4     5   6   7    7 6      5      4
        """
        if p == None and q == None:
            return True
        elif p == None or q == None:
            return False
        
        return (p.value == q.value) and self.mirrorCheck(p.left, q.right) and self.mirrorCheck(p.right, q.left)
        
