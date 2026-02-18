/* 
Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) 
principle, and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a normal queue, once the queue becomes full, 
we cannot insert the next element even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.

Implement the MyCircularQueue class:

MyCircularQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return -1.
int Rear() Gets the last item from the queue. If the queue is empty, return -1.
boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
boolean isEmpty() Checks whether the circular queue is empty or not.
boolean isFull() Checks whether the circular queue is full or not.
You must solve the problem without using the built-in queue data structure in your programming language. 
*/
#include<iostream>
#include<vector>

using namespace std;

class MyCircularQueue {
    int maxCapacity;
    int start;
    int end;
    int currentCapacity;
    vector<int> circularQueue;
public:
    MyCircularQueue(int k) : maxCapacity(k), currentCapacity(0), start(0), end(-1) {
        circularQueue = vector<int>(k);
    }
    
    bool enQueue(int value) {
        if(isFull())
            return false;
        
        end = (end+1)%maxCapacity;
        circularQueue[end] = value;
        currentCapacity++;
        return true;
    }
    
    bool deQueue() {
        if(isEmpty())
            return false;
        start = (start+1)%maxCapacity;
        currentCapacity--;
        return true;
    }
    
    int Front() {
        if(isEmpty())
            return -1;
        return circularQueue[start];
    }
    
    int Rear() {
        if(isEmpty())
            return -1;
        return circularQueue[end];
    }
    
    bool isEmpty() {
        return currentCapacity == 0;
    }
    
    bool isFull() {
        return currentCapacity == maxCapacity;
    }
};


int main(){
	MyCircularQueue myCircularQueue(3);
    cout<<endl<<myCircularQueue.enQueue(1); // return True
    cout<<endl<<myCircularQueue.enQueue(2); // return True
    cout<<endl<<myCircularQueue.enQueue(3); // return True
    cout<<endl<<myCircularQueue.enQueue(4); // return False
    cout<<endl<<myCircularQueue.Rear();     // return 3
    cout<<endl<<myCircularQueue.isFull();   // return True
    cout<<endl<<myCircularQueue.deQueue();  // return True
    cout<<endl<<myCircularQueue.enQueue(4); // return True
    cout<<endl<<myCircularQueue.Rear();     // return 4
	return 0;
}