# Do not make assumptions
# which ID, limit should be variable, single or multithreaded, what are we limiting on (fqdn? user? fqdn+user?)


################ 31/12/2025 #################

# token bucket
# a string key is provided
# max capacity of each bucket is given
# a refill rate is given / minute
# checkBucket(key) -> bool : essentially allow
import time

# class TokenBucket:
#     def __init__(self, maxCapacity, refillRate):
#         self._maxCapacity = maxCapacity
#         self._refillRate = refillRate
#         self._tokens = refillRate
#         self._timeOfLastRefill = time.time()

#     def checkBucket(self, reqTime):
#         # reqTime - tlastrefill = 0 minutes
#         # tokens = min(maxcapacity, 3*refillrate+tokens)
#         timeDiff = (reqTime - self._timeOfLastRefill)/60000
        
#         if timeDiff > 0:
#             self._tokens = min(self._maxCapacity, timeDiff*self._refillRate+self._tokens)
#             self._timeOfLastRefill = reqTime
        
#         if self._tokens > 0:
#             self._tokens -= 1
#             return True
        
#         return False



class RateLimiter:
    class TokenBucket:
        def __init__(self, maxCapacity, refillRate):
            self._maxCapacity = maxCapacity
            self._refillRate = refillRate
            self._tokens = refillRate
            self._timeOfLastRefill = time.time()

        def checkBucket(self, reqTime):
            # reqTime - tlastrefill = 0 minutes
            # tokens = min(maxcapacity, 3*refillrate+tokens)
            timeDiff = (reqTime - self._timeOfLastRefill)/60000
            
            if timeDiff > 0:
                self._tokens = min(self._maxCapacity, timeDiff*self._refillRate+self._tokens)
                self._timeOfLastRefill = reqTime
            
            if self._tokens > 0:
                self._tokens -= 1
                return True
            
            return False
        
    def __init__(self, maxCapacity, refillRate):
        self._maxCapacity = maxCapacity
        self._refillRate = refillRate
        self._reqMap = {} # key -> object of TokenBucket

    def checkBucket(self, key):
        reqTime = time.time()
        if key not in self._reqMap:
            self._reqMap[key] = self.TokenBucket(self._maxCapacity, self._refillRate)
        
        return self._reqMap[key].checkBucket(reqTime)
    

# Feedback: 
#   Take breaks, time : variable names - mention the unit of time. 
#   Some things are straightforward, do not explain in detail. 
#   Focus on the core concept, and not the smaller ones. 
#   without data types is fine  
#   then use // for floor -> MAJOR