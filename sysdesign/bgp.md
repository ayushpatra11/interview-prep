# BGP

## what is BGP
- Border Gateway Protocol
- path-vector routing protocol (not link-state)
- used between Autonomous Systems (AS)
- each AS has an ASN (Autonomous System Number)
- internet is a graph of ASes connected via BGP peering

## BGP message types
- OPEN: establish BGP session
- UPDATE: announce or withdraw routes
- KEEPALIVE: heartbeat
- NOTIFICATION: error

## route attributes
- AS_PATH: list of ASNs route has traversed (loop prevention + metric)
- NEXT_HOP: IP to forward packets to
- LOCAL_PREF: internal preference (higher = preferred), only iBGP
- MED (Multi-Exit Discriminator): hint to external AS for which path to use
- ORIGIN: how route was learned (IGP, EGP, incomplete)
- COMMUNITY: tags for policy, grouping

## BGP route selection order
1. highest LOCAL_PREF
2. shortest AS_PATH length
3. lowest ORIGIN code (IGP < EGP < incomplete)
4. lowest MED
5. eBGP preferred over iBGP
6. lowest IGP metric to next hop
7. lowest router ID (tiebreaker)

## AS_PATH prepending
- deliberately add your own ASN multiple times to AS_PATH
- makes your route look longer -> less preferred
- use case: ingress traffic engineering
  - if Tokyo PoP is congested, prepend Tokyo's ASN
  - other ASes start routing to London or Singapore instead
  - reference: cloudflare blog on prepending

## iBGP vs eBGP
- eBGP: between different ASes (direct peering)
- iBGP: within the same AS
- iBGP doesn't re-advertise to other iBGP peers by default (split horizon)
  -> needs full mesh OR route reflectors

## route reflectors
- eliminates full-mesh requirement for iBGP
- RR reflects routes to clients
- clients don't need to peer with each other

## anycast and BGP
- same IP prefix announced from multiple geographic locations
- BGP routes traffic to "nearest" PoP based on AS_PATH length / policy
- cloudflare uses this for 1.1.1.1, CF edge

## BGP security
- BGP hijacking: AS announces someone else's prefix
  - classic example: Pakistan Telecom (2008) taking down YouTube
- RPKI (Resource Public Key Infrastructure)
  - ROA (Route Origin Authorization): cryptographically binds prefix to ASN
  - Cloudflare is major RPKI operator
- BGP filtering, prefix lists, IRR databases also used

## OSPF / IS-IS (interior routing)
- used within an AS (IGP = Interior Gateway Protocol)
- OSPF: link-state, more common in enterprise
- IS-IS: link-state, preferred in large ISPs and CDNs (Cloudflare uses IS-IS)
- both flood link state info to build full topology map
- Dijkstra for shortest path calculation

## notes
- BGP converges slowly: seconds to minutes on failure
- IS-IS converges faster than OSPF for large networks
- SDN control planes can speed up route distribution
