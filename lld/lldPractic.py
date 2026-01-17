# rate limiter
# requirements: design a rate limiter with a configurable number of requests
# choose the most optimal algo that you think is possible to implement
# also think of anotheroptimal algo

# try and implement the sliding window log and the tocken bucket algo rate limiters 
# import time
# from collections import deque

# class RateLimiter:
#     def __init__(self, limit: int, interval: int) -> None:
#         self._limit = limit # this is the maximum number of requests (what is the time in which this limit is applicable?)
#         self._requestMap = {} # the request key and the queue of request timestamps. 
#         self._interval = interval
        
#     def allow(self, key: str) -> bool:
#         if self._limit == 0:
#             return False
#         requestTime = time.time()
#         if key in self._requestMap:
#             dq = self._requestMap[key]
#             while dq and requestTime - dq[0] > self._interval:
#                 dq.popleft()
#             if len(self._requestMap[key]) == self._limit:
#                 return False
#             self._requestMap[key].append(requestTime)
#             return True
        
#         self._requestMap[key] = deque()
#         self._requestMap[key].append(requestTime)
#         return True
        
#     @property
#     def getLimit(self) -> int:
#         return self._limit
    
#     @getLimit.setter
#     def setLimit(self, newLimit: int) -> None:
#         self._limit = newLimit

    

# let us consider that we are designing a rate limiter where each user can also have
# different thresholds or limits based on the tier that they are on

# we will have the rate limiting class, which will have the limit, the queue of requests, and the allow function. 

from collections import deque
import time

class RateLimiter:
    def __init__(self, limit: int, interval: int) -> None:
        self._limit = limit # this limit is different for each user. 
        self._queue = deque()
        self._interval = interval

    def _update_queue(self, requestTime: float) -> None:
        while self._queue and self._queue[0] < requestTime - self._interval:
            self._queue.popleft()

    def updateLimit(self, newLimit: int) -> None:
        self._limit = newLimit

    def allow(self) -> bool:
        # since this will be accessed using the class object, we will be able
        # to use the queue corresponding to this particular user. 
        requestTime = time.time()
        self._update_queue(requestTime)
        if self._limit <= len(self._queue):
            return False
        self._queue.append(requestTime)
        return True
    
class RequestProcessor:
    def __init__(self, freeTierLimit: int, premTierLimit: int, interval: int) -> None:
        self._userReqMap = {} # this will be a mapping of a userID key and a RateLimiter Object. 
        self._premUserList = set()
        self._premTierLimit = premTierLimit
        self._freeTierLimit = freeTierLimit
        self._interval = interval
        
    def _userLimit(self, userID: str) -> int:
        if userID in self._premUserList:
            return self._premTierLimit
        return self._freeTierLimit
    
    def allow(self, userID: str) -> bool:
        if userID not in self._userReqMap:
            self._userReqMap[userID] = RateLimiter(self._userLimit(userID), self._interval)
        
        return self._userReqMap[userID].allow()
    
    def addToPremList(self, userID: str) -> None:
        self._premUserList.add(userID)
        if userID in self._userReqMap:
            self._userReqMap[userID].updateLimit(self._premTierLimit)