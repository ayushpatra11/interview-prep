"""
Design a load balancer

n servers ; handle requests on each server. 

5 servers: 7 requests 

[ X   X   X   X   X]
  1.  2.  3.  4.  5
  6.  7. 


"""

from abc import ABC, abstractmethod

# will be the base for all algos
class LoadBalancerAlgo(ABC):
    @abstractmethod
    def route(self, requestId):
        pass

# Round Robbin Algo

class RoundRobbinAlgo(LoadBalancerAlgo):
    def __init__(self, numOfServers):
        self.numOfServers = numOfServers
        self.listOfServers = {i : [] for i in range(numOfServers)} # key -> serverID , value -> list of requestIDs
        self.currentServer = 0

    def route(self, requestID):
        self.listOfServers[self.currentServer].append(requestID)
        self.currentServer = (self.currentServer + 1)%self.numOfServers

    def exposeConnections(self):
        return dict(self.listOfServers)

class LoadBalancer:
    def __init__(self, routingAlgo):
        self.routingAlgo = routingAlgo

    def route(self, requestID):
        self.routingAlgo.route(requestID)

    def exposeConnections(self):
        print(self.routingAlgo.exposeConnections())



def main():
    rra = RoundRobbinAlgo(5)
    lb = LoadBalancer(rra)
    lb.route(1)
    lb.route(2)
    lb.route(3)
    lb.route(4)
    lb.route(5)
    lb.route(6)
    lb.route(7)   

    lb.exposeConnections()


main()