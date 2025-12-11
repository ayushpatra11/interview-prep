
# two sum
# given an array and a target, return indices of the two numbers that add up to target

class Solution:
    def twoSum(self, nums, target):
        seen = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in seen:
                return [seen[complement], i]
            seen[num] = i
        return []


# contains duplicate
# given integer array, return true if any value appears at least twice

    def containsDuplicate(self, nums):
        seen = set()
        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        return False


s = Solution()
print(s.twoSum([3, 12, 4, 2, 1, 5], 4))
