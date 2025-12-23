#
#
#       Mock 2 - 26/12
#
#
# addServer ->  
# removeServer ->   
# next ->   return next server that has to be utilised

class LoadBalancer:
    def __init__(self):
        self.__serverList = []
        self.__lastUsedServer = -1
        self.__serverListLen = 0

    def addServer(self, ipAddress):
        self.__serverList.append(ipAddress)
        self.__serverListLen += 1
    
    def removeServer(self, ipAddress):
        i = 0
        for ipAddr in self.__serverList:
            if ipAddr == ipAddress:
                if i <= self.__lastUsedServer:
                    self.__serverListLen = len(self.__serverList)-1
                    self.__lastUsedServer = ((self.__lastUsedServer - 1) + self.__serverListLen) % self.__serverListLen
                del self.__serverList[i]
                break
            i += 1

    def next(self):
        self.__lastUsedServer = (self.__lastUsedServer+1)%self.__serverListLen
        return self.__serverList[self.__lastUsedServer] # return IP. 

    