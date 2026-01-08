# Distributed Caching

## why distributed
- single cache server has memory limits
- need availability/replication
- need to scale horizontally

## consistent hashing
- nodes on a ring
- key hashed to position on ring, assigned to nearest node clockwise
- adding/removing nodes only remaps keys adjacent to that node
- virtual nodes: each physical node gets multiple positions on ring
  - more uniform distribution

## replication
- write to quorum W, read from quorum R, total nodes N
- W + R > N => strong consistency
- W=1, R=N: fast writes, slow reads
- W=N, R=1: slow writes, fast reads
- W=quorum, R=quorum: balanced

## eviction
- LRU: evict least recently used
- LFU: evict least frequently used (better for skewed access)
- FIFO: simplest, not great for caching
- TTL: time based, can combine with LRU

## LRU implementation
- doubly linked list + hashmap
- hashmap: O(1) key lookup -> node
- DLL: O(1) move to front (MRU position), remove from back (LRU position)

## cache aside pattern
1. check cache
2. on miss: fetch from DB
3. write to cache, return to caller

## write through
- write to cache + DB simultaneously
- consistent but slower writes

## write back (write behind)
- write to cache only, async flush to DB
- fast writes, risk losing data on crash

## common problems
- cache stampede / thundering herd: many requests hit DB simultaneously on expiry
  - solutions: mutex on cache miss, request coalescing, staggered TTLs
- hot keys: single key gets disproportionate traffic
  - local in-process cache in front of distributed cache
  - key splitting / replication
