"""

Concurrent request queue with back pressure logic : limiting the cap, block/drop. 

1. Producers and subscribers will enqueu or dequeu async
2. Max capacity for thw queue, choose block/drop. 

Main Queue -> Subscribers

Pending Queue -> Jobs > max capacity


"""

import deque
from threading import Lock


class ConcurrentReqQueue:
    def __init__(self, maxCapacity):
        self.maxCapacity = maxCapacity
        self.queue = deque()
        self.queueLock = Lock()
        self.enqLock = Lock()


    def enqueJob(self, message):
        if self._isQueueFull():
            with self.queueLock:
                self.queue.append(message)


    def dequeJob(self):
        with self.queueLock:
            return self.queue.popleft()
            

    def _isQueueFull(self):
        return len(self.queue) == self.maxCapacity