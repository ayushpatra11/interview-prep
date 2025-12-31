# building a rate limiter service
# be configurable: user can change the algorithm
# user can configure between - toekn bucket & sliding window

"""

RateLimiterAlgorithm -> abstract class
allow -> abstract method

TokenBucketAlgorithm -> subclass to abstract class
SlidingWindowAlgorithm -> ''

RateLimiterClass

Rate limiting based on userID

- ask more questions. 
- think about what is different about the product. 
- missed the userID, how to refill? etc. semantics of the algo have to be 
- clarified. 



"""

from abc import ABC, abstractmethod
import time
import enum

# class AlgorithmTypes(Enum):
#     TokenBucket = "TokenBucket"
#     SlidingWindow = "SlidingWindow"

class RateLimiterAlgorithm(ABC):
    @abstractmethod
    def allow(self):
        pass

class TokenBucketAlgorithm(RateLimiterAlgorithm):
    def __init__(self, refillRate, refillInterval, maxCapacity):
        self.maxCapacity = maxCapacity
        self.refillInterval = refillInterval
        self.refillRate = refillRate
        self.buckets = {} # userID -> tokens
        self.lastRefillTime = {} # userId-> last time of refill

    def __createNewBucket(self, userID):
        self.buckets[userID] = self.maxCapacity
        self.lastRefillTime[userID] = time.time()

    def __updateBucket(self, userID):
        timeOfReq = time.time()
        timeDiff = timeOfReq - self.lastRefillTime[userID]
        newTokens = (timeDiff // self.refillInterval) * self.refillRate
        self.buckets[userID] = min(self.buckets[userID]+newTokens, self.maxCapacity)
        self.lastRefillTime[userID] = timeOfReq

    def allow(self, userID):
        if userID not in self.buckets:
            self.__createNewBucket(userID)
            self.buckets[userID] -= 1
            return True

        self.__updateBucket(userID)
        if self.buckets[userID] > 0:
            self.buckets[userID] -= 1
            return True
        
        return False

class SlidingWindowAlgorithm(RateLimiterAlgorithm):
    def __init__(self, limit):
        pass

    def allow(self, userID):
        pass

class RateLimiterClass:
    def __init__(self, rateLimitAlgo):
        self.rateLimitAlgo = rateLimitAlgo

    def allow(self, userID):
        self.rateLimitAlgo.allow(userID)

    def changeAlgorithm(self, newRateLimitAlgo):
        self.rateLimitAlgo = newRateLimitAlgo

# read about enum of objects