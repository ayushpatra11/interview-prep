
# sliding window max
# given array and window size k, return max in each window

# brute force O(n*k), monotonic deque O(n)

from collections import deque

class Solution:
    def maxSlidingWindow(self, nums, k):
        result = []
        dq = deque()  # stores indices, front is always the max for current window

        for i, num in enumerate(nums):
            # remove elements outside window
            while dq and dq[0] < i - k + 1:
                dq.popleft()

            # remove smaller elements from back (they can never be max)
            while dq and nums[dq[-1]] < num:
                dq.pop()

            dq.append(i)

            if i >= k - 1:
                result.append(nums[dq[0]])

        return result
