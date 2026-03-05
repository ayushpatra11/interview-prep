/*

Seat allotment tool. 

bookSeat -> won't take any input -> returns seat number
leaveSeat -> vacate a seat (seat number) -> returns ? 

5

 x x x x x x x x x
   .   . . .   . .

*/
#include<iostream>
#include<set>

using namespace std;

class FindSeat{
    set<int> seats;
    int numOfSeats;

public:

    FindSeat(){}
    FindSeat(int capacity) : numOfSeats(capacity){
    }

    int bookSeat(){
        
    }   
};