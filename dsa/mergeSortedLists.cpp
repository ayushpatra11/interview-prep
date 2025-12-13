#include<iostream>

using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int val):val(val), next(NULL){}
};

Node* mergeSortedList(Node* listA, Node* listB){
    Node* tempA = listA;
    Node* tempB = listB;
    Node* ans = new Node(0);
    Node* tempAns = ans;
    //BF approach is to create a vector, then create a new list using this vector. SC will be O(N)
    // the other is to use a while loop and add elements directly to the list by comparison
    while(tempA || tempB){
        if(tempA && tempB){
            if(tempA->val <= tempB->val){
                Node* temp = new Node(tempA->val);
                tempAns->next = temp;
                tempAns = tempAns->next;
                tempA = tempA->next;
            }
            else{
                Node* temp = new Node(tempB->val);
                tempAns->next = temp;
                tempAns = tempAns->next;
                tempB = tempB->next;
            }
        }
        else if(tempA){
            Node* temp = new Node(tempA->val);
            tempAns->next = temp;
            tempAns = tempAns->next;
            tempA = tempA->next;
        }
        else{
            Node* temp = new Node(tempB->val);
            tempAns->next = temp;
            tempAns = tempAns->next;
            tempB = tempB->next;
        }
    }

    return ans->next;
}

int main(){
    Node* listA = new Node(0);
    Node* listB = new Node(0);
    Node* tempA = listA, *tempB =listB;
    int sizeA, sizeB;
    cin>>sizeA>>sizeB;
    for(int i =0; i< sizeA; i++){
        int val;
        cin>>val;
        Node* temp = new Node(val);
        tempA->next = temp;
        tempA = tempA->next;
    } 
    
    for(int i = 0; i<sizeB; i++){
        int val;
        cin>>val;
        Node* temp = new Node(val);
        tempB->next = temp;
        tempB = tempB->next;
    } 

    Node* ans = mergeSortedList(listA->next, listB->next);

    Node* temp = ans;

    while(temp){
        cout<<temp->val<<endl;
        temp = temp->next;
    }

    return 0;
}