# DNS Cache-Resolver

"""

FQDN -> passed as a string
If cache miss -> None


1. FQDN as input
2. Internal Cache -> FQDN to IP address
3. Cache miss -> None
4. Cache hit -> IP
5. It should be able to handle concurrency. 
6. Store metrics for cache hit and cache miss. 
7. Public APIs -> get IP, get metrics

data members:

1. HashMap -> FQDN : IP Address
2. cacheHitCount
3. cacheMissCount


1000

A -> 1
B -> 2

Lock 

A -> 1
B -> 2
C -> 3


100

Read A: 
Write D: 
Read D -> Write D
Read A
Read A





Read Lock -> RLock + counters 
Write Lock -> Lock 



"""

from threading import Lock, RLock

class ReadWriteLock:
    def __init__(self):
        self.readLock = Lock()
        self.readCounter = 0
        self.writeLock = Lock()

    def readLockAcquire(self):
        with self.readLock:
            self.readCounter += 1
            if self.readCounter == 1:
                self.writeLock.acquire()
        

    def readLockRelease(self):
        with self.readLock:
            self.readCounter -= 1
            if self.readCounter == 0:
                self.writeLock.release()

    def writeLockAcquire(self):
        self.writeLock.acquire()

    def writeLockRelease(self):
        self.writeLock.release()


        

class DNSCacheResolver:
    def __init__(self):
        self.fqdnMap = {} # -> FQDN : IP
        self.cacheHitCount = 0
        self.cacheMissCount = 0
        self.fqdnReadWriteLock = ReadWriteLock()


    def getIP(self, fqdn):
        self.fqdnReadWriteLock.readLockAcquire()
        if fqdn in self.fqdnMap:
            self.cacheHitCount += 1
        else:
            self.cacheMissCount += 1
            self.fqdnReadWriteLock.readLockRelease()
            self._checkUpstream(fqdn)

        return self.fqdnMap[fqdn]          
            
    
    def _checkUpstream(self, fqdn):
        self.fqdnReadWriteLock.writeLockAcquire()
        self.fqdnMap[fqdn] = "test_val"
        self.fqdnReadWriteLock.writeLockRelease()

    def getMetrics(self):
        return {"cacheHitCount": self.cacheHitCount, "cacheMissCount": self.cacheMissCount}
    