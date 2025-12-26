
# lld mock 3 - 28/12
# rate limiter - simple sliding window, first pass

import time

class RateLimiter:
    def __init__(self, maxRequests, windowSecs):
        self.maxRequests = maxRequests
        self.windowSecs = windowSecs
        self.reqMap = {}  # key -> list of timestamps

    def allow(self, key):
        now = time.time()
        if key not in self.reqMap:
            self.reqMap[key] = []

        # drop timestamps outside window
        self.reqMap[key] = [t for t in self.reqMap[key] if now - t < self.windowSecs]

        if len(self.reqMap[key]) < self.maxRequests:
            self.reqMap[key].append(now)
            return True

        return False

# feedback: should use deque for O(1) removal from front
# list comprehension for cleanup is O(n)
# also: variable naming - maxRequests, windowSecs - better with units in name
