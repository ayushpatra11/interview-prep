# Review - Jan 22

## topics covered
- [x] CDN design (tiered, request collapsing, control plane)
- [x] rate limiting (token bucket, sliding window, distributed)
- [x] distributed caching (consistent hashing, LRU, eviction)
- [x] load balancing (round robin, weighted, least connections)
- [x] DNS resolver design
- [ ] notification system
- [ ] URL shortener

## interview format reminders
- start: clarify functional + non-functional requirements
- capacity estimation if asked (usually not for CF)
- draw diagram first before going deep
- explain data flow top to bottom
- deep dive on 1-2 key components
- scale discussion at the end

## CF1 specific context
- zero trust networking / cloudflare one
- ZTNA: users access internal apps without VPN
- identity + device posture checks + network policy
- magic WAN: SD-WAN replacement using CF network

## common pitfalls in mocks
- went too deep too fast on caching before establishing requirements
- need to explicitly state trade-offs, not just pick one approach
- keep coming back to requirements to justify decisions

## LLD readiness
- DNS resolver: done (2 versions, with threading)
- rate limiter: done (token bucket, sliding window, configurable)
- load balancer: done (round robin, with abstractions)
- concurrent queue: done
- feel good about these

## potential weak spots
- not clear on ZTNA internals (just surface level)
- need to brush up on websockets vs SSE for notification systems
