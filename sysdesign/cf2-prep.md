# CF Network Platform - Interview Prep

## interview format
- system design: 60 min, no API design needed, focus on data flow + architecture
- coding: C++/Go, LLD style, may include systems concepts (ring buffer, queues)

## system design topics to hit
- BGP: AS_PATH, route selection, prepending, anycast
- CDN: tiered, request collapsing, control plane push, failure handling
- linux networking: eBPF, XDP, tc, netfilter, socket internals
- TCP/IP: packet flow, congestion control, TIME_WAIT

## feedback from baseline interview (march 7 mock)
- no API endpoints needed
- hierarchy of CDNs is key: L1 -> L2 -> origin shield -> origin
- control plane service for config push - important component
- request collapsing at each PoP tier
- AS_PATH prepending for traffic engineering (tokyo/london example)
- recalibrate: don't go too deep without prompting

## system design flow that worked
1. requirements: functional (cache content, serve low latency) + non-functional (high availability, global)
2. high-level diagram: user -> anycast DNS -> PoP -> cache -> origin
3. components: DNS, edge PoP, regional hub, origin shield, origin, control plane
4. deep dive: cache logic, request collapsing, invalidation
5. scale + failure: PoP failure = BGP withdrawal, thundering herd = collapsing

## coding topics to nail
- ring buffer / circular queue: can implement cleanly, O(1) enqueue/dequeue
- LRU cache: DLL + hashmap, O(1) all ops
- course schedule: topological sort via BFS (Kahn's), detect cycle
- rate limiter: token bucket with mutex for thread safety

## things that came up in CF1 + CF3
- circular queue got asked in both CF1 and CF3 (with modifications)
- be ready for: make it thread-safe, support blocking enqueue/dequeue

## weak spots to fix before March 12
- OSPF/IS-IS internals: more detail on LSA flooding, SPF computation
- eBPF maps: hash map, ring buffer, how to use from userspace
- SR-MPLS: surface level is enough, just know what it is

## final day checklist
- review BGP notes
- review linux networking notes  
- review CDN notes (cf2 version)
- check circular queue + LRU implementations
- get enough sleep
