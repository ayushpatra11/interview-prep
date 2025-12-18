# Caching system 
# LRU

# insert in cache -> 
# limit of K items 
# each item should also have a ttl
import time

class Node:
    def __init__(self, key, value, ttl):
        # internal classes
        self.next = None
        self.prev = None
        self.key = key
        self.value = value
        self.ttl = ttl
        self.time_inserted = time.time()

class LRUCache:
    def __init__(self, k):
        self.left = Node(None, None, None)
        self.right = Node(None, None, None)
        self.left.next = self.right
        self.right.prev = self.left
        self.hashMap = {} # key, node
        self.limit = k
        self.numItems = 0
        # TODO : Declare heap to track timestamp with node

    def _removeFromCache(self, key):
        if key in self.hashMap:
            nextNode = self.hashMap[key].next
            prevNode = self.hashMap[key].prev
            nextNode.prev = prevNode
            prevNode.next = nextNode
            del self.hashMap[key]
            self.numItems -= 1
    
    def _addToCache(self, key, value, ttl):
        newNode =  Node(key, value, ttl)
        self.right.prev.next = newNode
        newNode.prev = self.right.prev
        self.right.prev = newNode
        newNode.next = self.right
        self.hashMap[key] = newNode
        self.numItems += 1

    def get(self, key):
        if key in self.hashMap:
            oldNode = self.hashMap[key]
            ttl = oldNode.ttl
            time_inserted = oldNode.time_inserted
            if ttl+time_inserted >= time.time():
                self._removeFromCache(key)
                self._addToCache(key, oldNode.value, ttl)
                return oldNode.value
        return None

    def put(self, key, value, ttl):
        if key in self.hashMap:
            self._removeFromCache(key)
        self._addToCache(key, value, ttl)     
        if self.limit < self.numItems:
            deletedNode = self.left.next
            self._removeFromCache(deletedNode.value)

