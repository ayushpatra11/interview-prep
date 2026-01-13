# Rate Limiting - System Design

## algorithms
1. token bucket
   - fixed capacity bucket, tokens added at refill rate
   - request consumes 1 token, denied if empty
   - allows short bursts up to bucket capacity
2. leaky bucket
   - fixed output rate regardless of input
   - smooth traffic, no bursts
3. sliding window log
   - store timestamps of all requests in sorted set
   - count requests in last N seconds
   - most accurate, but memory-intensive (stores all timestamps)
4. sliding window counter
   - divide time into buckets (e.g., per second)
   - current window count = current bucket + fraction of previous
   - trade-off: slight inaccuracy, but O(1) memory

## single server
- in-process rate limiter (fast, no network)
- works fine for single-node deployments

## distributed
- problem: user can hit different nodes, each with partial view
- option 1: centralized store (Redis)
  - all nodes check same Redis instance
  - atomic INCR + EXPIRE
  - pros: accurate, consistent
  - cons: latency (+1-2ms per request), Redis becomes bottleneck
- option 2: sticky sessions
  - route same user to same node
  - pros: no coordination needed
  - cons: uneven load, fails if node goes down
- option 3: local rate limiting (per node)
  - each node has its own limit = total_limit / num_nodes
  - pros: fast
  - cons: imprecise, needs to know num_nodes upfront

## Redis implementation
- token bucket: ZADD (sorted set) with timestamps + ZREMRANGEBYSCORE + ZCARD
- counter: INCR key + EXPIRE (sliding window approximation)

## design considerations
- what to rate limit on? IP, user ID, API key, endpoint
- what happens on limit? 429 response, queue request, drop silently
- should limits be configurable per user tier?
- clock sync in distributed systems (NTP skew)

## API design
```
RateLimiter
  allow(key: str) -> bool
  getRemainingTokens(key: str) -> int
```
or as middleware (inject into request pipeline, transparent to business logic)
