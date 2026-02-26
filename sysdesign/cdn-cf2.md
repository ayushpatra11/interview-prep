# CDN Design - CF Network Platform Context

## cloudflare's CDN architecture
- anycast: single IP prefix announced from all PoPs via BGP
- user traffic BGP-routed to closest PoP (measured in AS hops)
- PoP -> regional cache -> origin shield -> origin
- ~300+ PoPs globally

## anycast for CDN
- BGP advertises same /22 from every PoP
- if Tokyo PoP fails: withdraw BGP announcement
  - traffic automatically reroutes to next-nearest (Osaka, Seoul, etc.)
  - no explicit failover configuration needed
  - convergence: seconds to minutes depending on BGP propagation

## ingress traffic engineering
- AS_PATH prepending: make one PoP look farther away
- local pref manipulation
- purpose: shift load between PoPs, handle capacity events
- reference: cloudflare blog on prepends being harmful (overuse of prepending)

## tiering + request collapsing
- L1 PoP may not cache infrequently accessed content
- on L1 miss: goes to L2 regional hub (shield PoP) before origin
- shield PoP collapses multiple parallel L1 misses into 1 upstream req
- reduces origin hit rate significantly

## control plane / config push
- customers configure rules, TTLs, transform rules via API
- cloudflare control plane pushes these to all PoPs
- PoPs poll config store or receive push notifications
- config propagation typically within seconds

## edge compute
- workers: serverless JS/WASM running at each PoP
- R2: object storage with workers integration
- kv: key-value store, eventually consistent across PoPs

## networking at the PoP (relevant for network platform team)
- traffic enters from internet via BGP peered routers
- ECMP across multiple uplinks
- Linux host receives packets, XDP/eBPF for early processing
- tunnel from PoP to origin (Argo tunnel / cloudflared)

## warp / cloudflare one
- warp: wireguard-based tunnel from device to nearest CF PoP
- CF network acts as a hub: device <-> CF <-> destination
- zero trust: every request goes through identity/policy check at CF edge

## system design interview checklist
- clarify: public CDN or private/enterprise?
- data flow: user -> DNS (anycast) -> PoP -> cache hit/miss logic -> origin
- tiering: explain L1/L2
- control plane: how configs get to PoPs
- failure handling: PoP failure, origin failure
- scale: how many PoPs, how much traffic
- no API endpoints needed per CF interview feedback
