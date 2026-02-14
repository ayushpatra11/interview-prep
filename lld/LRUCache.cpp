/*

Task: Design an LRU Cache:

Init with a particular capacity 

get(int key) -> return the associated value // -1 if not avail

put(int key, value) -> insert a key, value pair // evict the LRU element in case the data structure is full. 

Time constraints -> all have to be running in linear time - O(1)

*/


/*
Node -> an element

- key
- value
- Node* prev
- Node* next


LRU Cache 

- Node* head,*tail;
- Hashmap
- maxCapacity



Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

head - tail 

Node* ->

1 -key
1 - value



head - newNode - tail

head - newNode2 - newNode - tail

head - newNode - newNode2 - tail

head - newNode3- newNode -tail

*/

#include<iostream>
#include<unordered_map>


class Node{
public:
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(): key(0), value(0){
        prev =nullptr;
        next = nullptr;
    }

    Node(int key, int value) : key(key), value(value){
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache{
    // data members:
    int maxCapacity;
    Node* head; 
    Node* tail;
    unordered_map<int, Node*> hashMap;

    // private functions: 

    void removeFromList(Node* node){
        Node* prevElement = node->prev;
        Node* nextElement = node->next;
        prevElement->next = nextElement;
        nextElement->prev = prevElement;
    }
    void addToFront(Node* node){
        Node* currentFirstElement = head->next;
        head->next = node;
        node->prev = head;
        node->next = currentFirstElement;
        currentFirstElement->prev = node;
    }
/*


Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

*/



public:
    //public functions:

    LRUCache(int maxCapacity) : maxCapacity(maxCapacity){
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key){
        if(hashMap.find(key) == hashMap.end())
            return -1;

        Node* node = hashMap[key];
        int nodeValue = node->value;
        removeFromList(node);
        addToFront(node);
        return nodeValue;
    }

    void put(int key, int value){
        // the key is not present
        if(hashMap.find(key) == hashMap.end()){
            if(hashMap.size() == maxCapacity){
                hashMap.erase(tail->prev->key);
                removeFromList(tail->prev);
            }
            Node* newNode = new Node(key, value);
            addToFront(newNode);
            hashMap[key] = newNode;
        }
        else{
            // the key is present 
            Node* node = hashMap[key];
            removeFromList(node);
            node->value = value;
            addToFront(node);
        }
    }

};