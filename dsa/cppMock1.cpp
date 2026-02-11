/*

Design an algorithm that accepts a stream of integers and retrieves the product of the last k integers of the stream.

Implement the ProductOfNumbers class:

ProductOfNumbers() Initializes the object with an empty stream.
void add(int num) Appends the integer num to the stream.
int getProduct(int k) Returns the product of the last k numbers in the current list. You can assume that always the current list has at least k numbers.
The test cases are generated so that, at any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.


Input
["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
[[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]

list -> 3 0 2 5 4

prod - 3

datastruct

1, 0
2, 2
3, 10
4, 20



Output
[null,null,null,null,null,null,20,40,0,null,32]

*/



class ProductOfNumbers {
    int numberOfElements;
    vector<int> intervals;
public:
    ProductOfNumbers() {
        
    }
    
    void add(int num) {
        if(num == 0){
            numberOfElements = 0;
            intervals.clear();
        }
        else{
            numberOfElements++;
            intervals.push(intervals.back() * num);
        }
    }
    
    int getProduct(int k) {
        if(k > numberOfElements)
            return 0;

        int prodLast = intervals.back();

        return prodLast/intervals[intervals.size() - k-1];
    }
};
