# #
# #DNS resolver class
# # get(fqdn) -> list of IP addresses
# # cacheIP(fqdn, ip)


import time

class DNSResolver:
    def __init__(self):
        self.__cache = {}          # fqdn -> list of IPs
        self.__ttl = {}            # fqdn -> expiry time
        self.__permitted_expiry = 30000
        self.__rootLevel = {}

    def __setTtl(self, fqdn):
        self.__ttl[fqdn] = time.time() + self.__permitted_expiry

    def __remove_expired_fqdn(self, fqdn):
        del self.__cache[fqdn]
        del self.__ttl[fqdn]

    def get(self, fqdn: str):
        if fqdn in self.__cache:
            expiry_time = self.__ttl[fqdn]
            if time.time() <= expiry_time:
                return self.__cache[fqdn]
            else:
                self.__remove_expired_fqdn(fqdn)

        ips = self.__queryServers(fqdn)
        self.__cacheIP(fqdn, ips)
        return self.__cache[fqdn]

    def __cacheIP(self, fqdn: str, ipaddr):
        if fqdn not in self.__cache:
            self.__cache[fqdn] = []

        for ip in ipaddr:
            self.__cache[fqdn].append(ip)

        self.__setTtl(fqdn)

    def getFromServer(self, server_ip, query):
        return []

    def __queryServers(self, fqdn):
        rootLevelQuery = "." + fqdn.split(".")[-1]
        tldLevelQuery = fqdn.split(".")[-2]
        authLevelQuery = fqdn

        tldIpSet = set()
        authIpSet = set()
        finalIPSet = set()

        if rootLevelQuery in self.__rootLevel:
            for ip in self.__rootLevel[rootLevelQuery]:
                for tldIp in self.getFromServer(ip, rootLevelQuery):
                    tldIpSet.add(tldIp)

        if not tldIpSet:
            return []

        for tldIp in tldIpSet:
            for authIp in self.getFromServer(tldIp, tldLevelQuery):
                authIpSet.add(authIp)

        if not authIpSet:
            return []

        for authIp in authIpSet:
            for finalIp in self.getFromServer(authIp, authLevelQuery):
                finalIPSet.add(finalIp)

        return list(finalIPSet)