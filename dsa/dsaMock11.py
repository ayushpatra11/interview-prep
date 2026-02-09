"""
Date: 9/2/2026

Circular Queue : FIFO approach, Ring Buffer. 

Init : given size
Front - returns front item, else -1 if empty
Rear - gives rear of the queue else -1 if empty
enqueue - add the element, if no space return false, else return true. 
dequeue - from the front, remove. Return true if possible or false if not possible. 
isempty
isfull
"""
"""
Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]

Output
[null, true, true, true, false, 3, true, true, true, 4]
"""

class RingBuffer:
    def __init__(self, maxSize):
        self.queue = [0] * maxSize
        self.maxCapacity = maxSize
        self.capacity = 0
        self.front = 0
        self.rear = 0
    
    def returnFront(self):
        if self.isEmpty():
            return -1
        
        return self.queue[self.front]

    def returnRear(self):
        if self.isEmpty():
            return -1
        
        return self.queue[self.rear-1]

    def enqueue(self, item):
        if self.isFull():
            return False
        
        self.queue[self.rear] = item
        self.rear = (self.rear+1) % self.maxCapacity
        self.capacity += 1
        return True

    def dequeue(self):
        if self.isEmpty():
            return False
        
        self.front = (self.front+1) % self.maxCapacity
        self.capacity -= 1
        return True

    def isFull(self):
        return self.capacity == self.maxCapacity

    def isEmpty(self):
        return self.capacity == 0
    
    def printQueue(self):
        return list(self.queue)



def main():
    rb = RingBuffer(3)
    print(rb.enqueue(1))
    print(rb.enqueue(2))
    print(rb.enqueue(3))
    print(rb.enqueue(4))
    print(rb.returnRear())
    print(rb.isFull())
    print(rb.printQueue())
    print(rb.dequeue())
    print(rb.enqueue(4))
    print(rb.returnRear())
    print(rb.printQueue())

main()
    
