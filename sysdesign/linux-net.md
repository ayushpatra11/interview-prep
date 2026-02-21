# Linux Networking

## packet ingress flow
1. NIC receives packet, DMA into ring buffer
2. NIC raises hardware IRQ
3. kernel enters NAPI: disables IRQ, polls driver in softirq context
4. sk_buff allocated, packet data copied/referenced
5. netif_receive_skb -> protocol handlers
6. IP layer: routing, forwarding decision
7. TCP layer: reassembly, socket buffer
8. application: recv() system call

## key structures
- sk_buff: represents a packet, contains data + metadata pointers
  - avoid copying: pointer arithmetic to add/remove headers
- net_device: represents a network interface (eth0, lo, etc.)
- socket: endpoint for application communication
- dst_entry: routing cache entry

## netfilter hooks
- points in the kernel where iptables/nftables/eBPF can intercept
- PREROUTING: before routing decision
- INPUT: destined for local socket
- FORWARD: being routed
- OUTPUT: from local socket
- POSTROUTING: after routing, before NIC
- used for: firewall, NAT, packet mangling

## tc (traffic control)
- qdiscs (queuing disciplines) on each interface
- ingress + egress
- pfifo, fq_codel, HTB (hierarchical token bucket)
- BPF programs can attach at tc ingress/egress
  - runs on sk_buff (packet already allocated)

## XDP (eXpress Data Path)
- runs eBPF code at the NIC driver level
- before sk_buff allocation -> very low overhead
- return codes: XDP_PASS, XDP_DROP, XDP_TX, XDP_REDIRECT
- use cases: DDoS mitigation (drop early), fast forwarding
- cloudflare uses XDP heavily for DDoS protection

## eBPF
- sandboxed programs that run in kernel context
- verified by kernel verifier (safety: no unbounded loops, valid memory access)
- attach points: XDP, TC, kprobes, tracepoints, sockets, etc.
- BPF maps: kernel-userspace shared data (hash, array, ring buffer, etc.)
- compiled to eBPF bytecode (from C via LLVM/clang), JIT-compiled at load time

## DPDK
- userspace networking: driver in userspace, bypasses kernel entirely
- polling mode driver (PMD) - no interrupts
- much lower latency than kernel path
- tradeoff: CPU busy-polling, not integrated with kernel

## I/O multiplexing
- select/poll: O(n) scan of all fds - not great for high connection count
- epoll: O(1) event detection using kernel-managed event queue
  - edge-triggered vs level-triggered
  - most servers use epoll

## important syscalls
- socket(), bind(), listen(), accept(), connect()
- send(), recv(), sendmsg(), recvmsg()
- epoll_create(), epoll_ctl(), epoll_wait()
- setsockopt() (socket options: TCP_NODELAY, SO_REUSEPORT, etc.)

## SO_REUSEPORT
- multiple sockets can bind to same address:port
- kernel load-balances incoming connections across sockets
- allows multi-threaded accept() without lock contention

## TCP internals worth knowing
- 3-way handshake: SYN, SYN-ACK, ACK
- congestion control: slow start, congestion avoidance, fast retransmit/recovery
- window scaling: for high BDP links
- TIME_WAIT: 2*MSL after connection close (prevents stale packets)
- TCP_NODELAY: disables Nagle algorithm (good for low-latency apps)
