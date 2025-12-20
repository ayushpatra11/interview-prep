# merge 2 sorted lists
# 

class Solution:
    def merge2SortedLists(self, list1, list2):
        res = []
        i = 0
        j = 0
        while i < len(list1) or j < len(list2):
            if i < len(list1) and j < len(list2):  
                if list1[i] <= list2[j]:
                    res.append(list1[i])
                    i += 1
                else:
                    res.append(list2[j])
                    j += 1
            elif i < len(list1):
                res.append(list1[i])
                i += 1
            elif j < len(list2):
                res.append(list2[j])
                j += 1
        
        return res
    
    def mergeKSortedLists(self, listOfLists):
        # res = []
        # list1 , list2 ...
        # res = res, list1 
        # res = res, list2
        # O (k*max(len(list2), len(list2))  -> O (k * n)
        # 1, 2, 3, 4, 5
        # (1, 2), (3, 4), 5
        # (1, 2, 3, 4), 5
        # (1, 2, 3, 4, 5)

        

        # return res