"""
Requirements: 

1. We wil be rate limiting based on a user id
2. Single threaded for now, extensible to multithreaded
3. Rules are not configurable 

"""

from abc import ABC, abstractmethod
from collections import deque
import time
from threading import Lock


class RateLimitingAlgorithm(ABC):
    @abstractmethod
    def allow(self, userID, timestamp):
        pass


class SlidingWindowAlgo(RateLimitingAlgorithm):
    def __init__(self, maxCapacity, timeRange):
        self.maxCapacity = maxCapacity
        self.timeRange = timeRange
        self.hashMap = {}       # user id -> queue[timestamps]
        self.userLocks = {}
        self.globalLock = Lock()

    def allow(self, userID, timestamp):
        with self.globalLock:
            if userID not in self.userLocks:
                self.userLocks[userID] = Lock()
                self.hashMap[userID] = deque()
        
        with self.userLocks[userID]:
        # check if userID is present already
            if userID in self.hashMap:
                # update queue if needed and check if insertion possible
                while self.hashMap[userID] and self.hashMap[userID][0] < timestamp-self.timeRange:
                    self.hashMap[userID].popleft()
                
                if len(self.hashMap[userID]) == self.maxCapacity:
                    return False
                
            self.hashMap[userID].append(timestamp)

            return True
    
class RateLimitingService:
    def __init__(self, rateLimitAlgo):
        self.rateLimiter = rateLimitAlgo

    def allow(self, userID):
        return self.rateLimiter.allow(userID, time.time())
    


