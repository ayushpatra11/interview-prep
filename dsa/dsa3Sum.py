"""
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
"""

# There should not be any duplicates, so I will check whether the previous index also
# had the same value. 

class returnSum:
    def __init__(self, numList):
        self.numList = numList.sort()
        self.sumList = []
        self.listSize = len(numList)

    def threeSum(self):
        # three pointers, i, j, k
        # all these pointers will track the potential correct indexes. 
        # we have to ensure that the input is in sorted manner. 
        for i in range(0, self.listSize-2):
            if i > 0 and self.numList[i] == self.numList[i-1]:
                continue

            j, k = i+1, self.listSize-1

            while j<k:
                currentSum = self.numList[i] + self.numList[j] + self.numList[k]
                if currentSum > 0:
                    k -= 1
                elif currentSum < 0:
                    j += 1
                elif currentSum == 0:
                    self.sumList.append([self.numList[i], self.numList[j], self.numList[k]])
                    j += 1
                    k -= 1
                    while j < k and self.numList[j] == self.numList[j-1]:
                        j += 1
                    while k > j and self.numList[k] == self.numList[k+1]:
                        k -= 1

            
        return self.sumList
    


rS3Sum = returnSum([-1,0,1,2,-1,-4])

print(rS3Sum.threeSum())