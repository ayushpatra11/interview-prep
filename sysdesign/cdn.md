# CDN

## basics
- cache static content at edge servers
- reduces latency, reduces origin load
- popular content served from nearby PoP

## tiered CDN
- L1 edge (city level) -> L2 regional -> origin
- L1 miss -> goes to L2, not directly to origin
- L2 miss -> origin, and caches on the way back

## request collapsing
- at each tier, only 1 upstream request for a cache miss
- other concurrent requests wait for that 1 to complete
- avoids thundering herd on origin

## cache invalidation
- TTL: simplest, but stale data until expiry
- event driven: push purge commands to all PoPs (faster, more complex)
- pull: let TTL expire (lazy)

## push vs pull CDN
- push: origin proactively pushes content to CDN
  - good for small, predictable content
- pull: CDN fetches on first request
  - good for dynamic / unpredictable traffic

## control plane
- need a way to push configs (routing rules, TTL, headers) to all CDN nodes
- control plane service that talks to each PoP
- PoPs poll or use pub-sub to get config updates

## consistency
- purge propagation delay is seconds to minutes
- during this time, different PoPs may serve different content versions
- acceptable for most use cases

## cloudflare specific
- anycast: same /22 prefix announced from all PoPs via BGP
- user traffic goes to closest PoP by BGP route selection
- see anycast notes for more detail
